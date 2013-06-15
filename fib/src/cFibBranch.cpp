/**
 * @class cFibBranch
 * file name: cFibBranch.cpp
 * @author Betti Oesterholz
 * @date 11.08.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib element, which are branches.
 * Copyright (C) @c LGPL3 2009 Betti Oesterholz
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
 * This file contains the basisclass of all Fib elements, which are
 * branches. Branches can have more than one underobject. It's not
 * possible to create instances from this class.
 * The Fib elements are the elements of the Fib multimedialanguage.
 * The class cFibElement defines methods to change the structur of an
 * Fib object/-tree.
 *
 * If the structur of the Fib object is changed just set the underobjects
 * and call updateAllValues() from a position wher the highest Fib element
 * can be reached. The updateAllValues()  method will make the conections.
 * If you remove conections you have to be more carefull.
 */
/*
History:
17.04.2009  Oesterholz  created
06.01.2010  Oesterholz  getAllFibElements() uses now getAllFibElementsFromPosition()
02.09.2010  Oesterholz  the destructor cuts the conections from the
	underobjects to this object
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
21.08.2011  Oesterholz  syncUnderobjects() renamed to syncSubobjects();
	cExtObject added
07.10.2010  Oesterholz  Bugfix: getAllFibElementsFromPosition() now works
	also with empty subobject list
09.10.2010  Oesterholz  Bugfix: removeObject() call syncUnderobjects() for remaining branch
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
07.11.2011  Oesterholz  cExtSubobject added to evalueCountersForObject()
15.12.2011  Oesterholz  cFibSet and cFibmatrix added to evalueCountersForObject()
18.01.2012  Oesterholz  Bugfix: in insertElement() check variables above
	the to replace element
19.05.2013  Oesterholz  SWITCH_JUST_STORE_AND_EVALUE implemented
*/

//TODO weg
//#define DEBUG


#include "cFibBranch.h"
#include "cFibLimb.h"
#include "cRoot.h"
#include "cIf.h"
#include "cList.h"
#include "cExtObject.h"

#include <utility>


using namespace fib;

using namespace std;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

#ifdef FEATURE_FAST_UPDATE

/**
 * parameterconstructor
 *
 * @param liFibUnderObjects the underobjects of this Fib branchelement
 * @param pInSuperiorElement the Fib Element in which this Fib element
 * 	is the underobject
 */
cFibBranch::cFibBranch( list<cFibElement*> liFibUnderObjects,
		cFibElement * pInSuperiorElement ):
		cFibElement( pInSuperiorElement ),
		fibUnderObjects( liFibUnderObjects )
		,fibObjectCounts(){
	
	//set the superior Fib element of the underobject to this Fib element
	for ( list<cFibElement*>::iterator itrUnderobject = fibUnderObjects.begin();
			itrUnderobject != fibUnderObjects.end(); ){
		
		if ( *itrUnderobject ){
			if ( (*itrUnderobject)->pSuperiorElement != NULL ){
				(*itrUnderobject)->pSuperiorElement->cutConnectionsTo(
					(*itrUnderobject) );
			}
			(*itrUnderobject)->pSuperiorElement = this;
			itrUnderobject++;
		}else{// (*itrUnderobject) == NULL
			itrUnderobject = fibUnderObjects.erase( itrUnderobject );
		}
	}
}

#else //FEATURE_FAST_UPDATE

/**
 * parameterconstructor
 *
 * @param liFibUnderObjects the underobjects of this Fib branchelement
 * @param pInSuperiorElement the Fib Element in which this Fib element
 * 	is the underobject
 */
cFibBranch::cFibBranch( list<cFibElement*> liFibUnderObjects,
		cFibElement * pInSuperiorElement ):
		cFibElement( pInSuperiorElement ),
		fibUnderObjects( liFibUnderObjects ){
	//nothing to do
}

#endif //FEATURE_FAST_UPDATE

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorElement the Fib Element in which this Fib element
 * 	is the underobject
 * @param pInPreviousFibElement the Fib Element which stands in th order
 * 	of Fib elements befor this Fib element
 * @param pInNextFibElement the Fib Element which stands in th order
 * 	of Fib elements behind this Fib element
 * @param liFibUnderObjects the underobjects of this Fib branchelement
 */
cFibBranch::cFibBranch( cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement,
		cFibElement * pInNextFibElement,
		list<cFibElement*> liFibUnderObjects ):
		cFibElement( pInSuperiorElement, pInPreviousFibElement, pInNextFibElement ),
		fibUnderObjects( liFibUnderObjects )
#ifdef FEATURE_FAST_UPDATE
		,fibObjectCounts()
#endif //FEATURE_FAST_UPDATE
		{
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of this Fib Element.
 * It dosn't copy other Fib elements than this, even if ther are in this
 * Fib element.
 *
 * @param fibBranchElement the Fib element to copy
 */
cFibBranch::cFibBranch( const cFibBranch &fibBranchElement ):
		cFibElement( fibBranchElement )
#ifdef FEATURE_FAST_UPDATE
		,fibObjectCounts()
#endif //FEATURE_FAST_UPDATE
		{
	//nothing to do
}


/**
 * destructor
 */
cFibBranch::~cFibBranch(){
	
	//remove the superior Fib element of the underobjects
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			//incorrect underobject
			(*actualUnderObject)->cutConnectionsTo( this );
		}
	}
}



#ifdef FEATURE_FAST_UPDATE

/**
 * This method checks, if this Fib element is an valid Fib element.
 *
 * @return true if this Fib element is an valid Fib element, else false
 */
bool cFibBranch::isValidFibElement() const{
	
	if ( fibUnderObjects.empty() ){
		//no underobjects
		return false;
	}
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) == NULL ){
			//incorrect underobject
			return false;
		}
	}
	//everything is ok
	return true;
}


/**
 * This method returns the next Fib element in the order of Fib elements.
 *
 * @return a pointer to the next Fib element in the order of Fib elements
 * 	or the NULL pointer if non such exists
 */
cFibElement * cFibBranch::getNextFibElement(){
	
	//return the next (not null) underobject
	for (list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			//next Fib element
			return (*actualUnderObject);
		}
	}
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this );
	}//else
	return NULL;
}


/**
 * This method returns the next Fib element in the order of
 * Fib elements which is above the given fib element.
 * This method is used, if the method @see getNextFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getNextFibElement()
 * @param pLastFibElement the Fib element relativ to which the next
 * 	Fib element should lay
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibBranch::getNextFibElementUp( const cFibElement * pLastFibElement ){
	
	//return the next underobject to the given underobject pLastFibelement
	bool bLastFibElementFound = false;
	for (list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			if ( bLastFibElementFound ){
				//next Fib element
				return (*actualUnderObject);
			}else if ( pLastFibElement == (*actualUnderObject) ){
				bLastFibElementFound = true;
			}
		}
	}
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this );
	}//else
	return NULL;
}


/**
 * This method returns the next Fib element in the order of 
 * Fib elements with the given type cTyp.
 *
 * @param cType the type of the Fib element to return
 * @return a pointer to the next Fib element in the order of 
 * 	Fib elements with the given type or the NULL pointer if non such
 * 	exists
 */
cFibElement * cFibBranch::getNextFibElement( char cType ){
	
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return NULL;
	}
	
	const char index = cFibObjectCounts::elementTypeToIndex( cType );
	
	if ( fibObjectCounts.vecNumberOfFibElements[ index ] != 0 ){
		//return the next underobject
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
					//next Fib element
				if ( (cType == 'u') || ((*actualUnderObject)->getType() == cType) ){
					return (*actualUnderObject);
				}//else
				cFibElement * pNextElement = (*actualUnderObject)->getNextFibElement( cType );
				if ( pNextElement ){
					return pNextElement;
				}
			}
		}
	}//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this, cType );
	}//else
	return NULL;
}


/**
 * This method returns the next Fib element in the order of
 * Fib elements which is above the given fib element.
 * This method is used, if the method @see getNextFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getNextFibElement()
 * @param pLastFibElement the Fib element relativ to which the next
 * 	Fib element should lay
 * @param cType the type of the Fib element to return
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibBranch::getNextFibElementUp( const cFibElement * pLastFibElement,
		char cType ){
	
	//return the next underobject to the given underobject pLastFibelement
	if ( fibObjectCounts.vecNumberOfFibElements[
			cFibObjectCounts::elementTypeToIndex( cType ) ] != 0 ){
		bool bLastFibElementFound = false;
		for (list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				if ( bLastFibElementFound ){
					if ( ((cType == 'u') || ((*actualUnderObject)->getType() == cType)) ){
						//next Fib element
						return (*actualUnderObject);
					}
					const unsignedIntFib uiNumberOfElements =
						(*actualUnderObject)->getNumberOfElements( cType );
					if ( 1 <= uiNumberOfElements ){
						//the Fib element is in the underobject
						return (*actualUnderObject)->getNextFibElement( cType );
					}
				}else if ( pLastFibElement == (*actualUnderObject) ){
					bLastFibElementFound = true;
				}
			}
		}
	}//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this, cType );
	}//else
	return NULL;
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements.
 *
 * @param lNumber the number of the Fib Element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements or the NULL pointer if non such exists
 */
cFibElement * cFibBranch::getConstFibElement( longFib lNumber,
		bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibBranch::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	if ( lNumber == 0 ){
		//this is the correct Fib element
		DEBUG_OUT_L2(<<"cFibBranch::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done returning this"<<endl<<flush);
		return const_cast<cFibBranch*>( this );
	}//else
	if ( bAbsolute ){
		DEBUG_OUT_L2(<<"calling getMasterRoot()->getConstFibElement( "<<lNumber<<" );"<<endl<<flush);
		return getMasterRoot()->getConstFibElement( lNumber );
	}//else lNumber is an relative value
	if ( lNumber == 1 ){
		//this is the correct Fib element
		DEBUG_OUT_L2(<<"cFibBranch::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done returning this"<<endl<<flush);
		return const_cast<cFibBranch*>( this );
	}//else
	
	DEBUG_OUT_L2(<<"this is the "<<getNumberOfElement()<<" "<<getType()<<" Element;  fibObjectCounts[ 0 ]="<<fibObjectCounts.vecNumberOfFibElements[ 0 ]<<endl<<flush);
	if ( ( 0 < lNumber ) && (lNumber <= fibObjectCounts.vecNumberOfFibElements[ 0 ]) ){
		//the lNumber underobject is under this branchelement -> return the lNumber underobject
		lNumber--;//remove this Fib element from the count
		for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				//next Fib element
				const unsignedIntFib uiNumberOfElements =
					(*actualUnderObject)->getNumberOfElements();
				DEBUG_OUT_L2(<<"the actual underobject contains "<<uiNumberOfElements<<" Fib elements"<<endl<<flush);
				if ( lNumber <= uiNumberOfElements ){
					//the Fib element is in the underobject
					DEBUG_OUT_L2(<<"calling (*actualUnderObject)->getConstFibElement( lNumber="<<lNumber<<" );"<<endl<<flush);
					return (*actualUnderObject)->getConstFibElement( lNumber );
				}
				lNumber -= uiNumberOfElements;
				DEBUG_OUT_L2(<<"not in actual underobject; removing "<<uiNumberOfElements<<" elements from count, new lNumber="<<lNumber<<endl<<flush);
			}
		}//Fib element not below this branchelement -> search direction higher
		if ( pSuperiorElement ){
			DEBUG_OUT_L2(<<"calling pSuperiorElement->getConstFibElementUp( this="<<this<<", lNumber="<<lNumber<<" ); after search underobjects"<<endl<<flush);
			return pSuperiorElement->getConstFibElementUp( this, lNumber );
		}//else no such next Fib element
		DEBUG_OUT_L2(<<"cFibBranch::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done no superior after search underobjects"<<endl<<flush);
		return NULL;
	}//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		if ( 0 < lNumber ){
			//remove the Fib elements under this branch from the count
			lNumber -= fibObjectCounts.vecNumberOfFibElements[ 0 ];
			DEBUG_OUT_L2(<<"calling pSuperiorElement->getConstFibElementUp( this="<<this<<", lNumber="<<lNumber<<" );"<<endl<<flush);
			return pSuperiorElement->getConstFibElementUp( this, lNumber );
		}else{// lNumber < 0
			DEBUG_OUT_L2(<<"calling pSuperiorElement->getConstFibElementUp( this="<<this<<", lNumber="<<lNumber<<" );"<<endl<<flush);
			return pSuperiorElement->getConstFibElementUp( this, lNumber );
		}
	}//else
	
	DEBUG_OUT_L2(<<"cFibBranch::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done no superior"<<endl<<flush);
	return NULL;
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements which is above the given Fib element.
 * This method is used, if the method @see getConstFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getConstFibElementUp()
 * @param pLastFibElement the Fib element relativ to which the next
 * 	Fib element should lay
 * @param lNumber the number of the Fib Element to return
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibBranch::getConstFibElementUp( const cFibElement * pLastFibElement,
		longFib lNumber ) const{
	//return the next lNumber'th Fib element to the given Fib element /underobject pLastFibelement
	if ( 0 < lNumber ){
		bool bLastFibElementFound = false;
		for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				if ( pLastFibElement == (*actualUnderObject) ){
					bLastFibElementFound = true;
				}else if ( bLastFibElementFound ){
					//next Fib element
					const unsignedIntFib uiNumberOfElements =
						(*actualUnderObject)->getNumberOfElements();
					if ( lNumber <= uiNumberOfElements ){
						//the Fib element is in the underobject
						return (*actualUnderObject)->getConstFibElement( lNumber );
					}
					lNumber -= uiNumberOfElements;
				}
			}
		}
		if ( pSuperiorElement ){
			return pSuperiorElement->getConstFibElementUp( this, lNumber );
		}//else no such next Fib element
		return NULL;
	}//else if (lNumber < 0) -> search in direction lower from the last Fib element
	bool bLastFibElementFound = false;
	for (list<cFibElement*>::const_reverse_iterator actualUnderObject = fibUnderObjects.rbegin();
			actualUnderObject != fibUnderObjects.rend(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			if ( pLastFibElement == (*actualUnderObject) ){
				bLastFibElementFound = true;
			}else if ( bLastFibElementFound ){
				//next Fib element
				const unsignedIntFib uiNumberOfElements =
					(*actualUnderObject)->getNumberOfElements();
				lNumber += uiNumberOfElements;
				if ( 0 <= lNumber ){
					//the Fib element is in the underobject
					lNumber++;
					return (*actualUnderObject)->getConstFibElement( lNumber );
				}
			}
		}
	}
	if ( lNumber == -1 ){
		//this is the correct Fib element
		return const_cast<cFibBranch*>( this );
	}//else

	//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		lNumber++;//remove this Fib element from the count
		return pSuperiorElement->getConstFibElementUp( this, lNumber );
	}//else
	
	return NULL;
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements of the given type cTyp with the given type cTyp.
 *
 * @param cType the type of the Fib element to return
 * @param lNumber the number of the Fib element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements with the given type or the NULL pointer if non such
 * 	exists
 */
cFibElement * cFibBranch::getConstFibElement( char cType,
		longFib lNumber, bool bAbsolute ) const{
	
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return NULL;
	}
	if ( lNumber == 0 ){
		//this is the correct Fib element
		return const_cast<cFibBranch*>( this );
	}//else
	if ( bAbsolute ){
		return getMasterRoot()->getConstFibElement( cType, lNumber );
	}//else lNumber is an relative value
	if ( cType == 'u' ){
		//type is irrelevant respectivly return of every type
		return getConstFibElement( lNumber );
	}
	if ( (lNumber == 1) && ( getType() == cType ) ){
		//this is the correct Fib element
		return const_cast<cFibBranch*>( this );
	}//else
	
	if ( ( 0 < lNumber ) && (lNumber <= fibObjectCounts.vecNumberOfFibElements[
			cFibObjectCounts::elementTypeToIndex( cType ) ]) ){
		//the lNumber underobject is under this branchelement -> return the lNumber underobject
		if ( getType() == cType ){
			lNumber--;//remove this Fib element from the count
		}
		for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
					//next Fib element
				const unsignedIntFib uiNumberOfElements =
					(*actualUnderObject)->getNumberOfElements( cType );
				if ( lNumber <= uiNumberOfElements ){
					//the Fib element is in the underobject
					return (*actualUnderObject)->getConstFibElement( cType, lNumber );
				}
				lNumber -= uiNumberOfElements;
			}
		}//Fib element not below this branchelement -> search direction higher
		if ( pSuperiorElement ){
			return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
		}//else no such next Fib element
		return NULL;
	}//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		if ( 0 < lNumber ){
			//remove the Fib elements under this branch from the count
			lNumber -= fibObjectCounts.vecNumberOfFibElements[
				cFibObjectCounts::elementTypeToIndex( cType ) ];
			return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
		}else{// lNumber < 0
			return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
		}
	}//else
	
	return NULL;
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements of the given type cTyp with the given type cTyp which is
 * above the given Fib element.
 * This method is used, if the method @see getConstFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getConstFibElementUp()
 * @param pLastFibElement the Fib element relativ to which the next
 * 	Fib element should lay
 * @param cType the type of the Fib element to return
 * @param lNumber the number of the Fib Element to return
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibBranch::getConstFibElementUp( const cFibElement * pLastFibElement,
		char cType, longFib lNumber ) const{
	
	/*return the next lNumber'th Fib element to the given Fib element /
	underobject pLastFibelement of the given type*/
	if ( 0 < lNumber ){
		bool bLastFibElementFound = false;
		for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				if ( pLastFibElement == (*actualUnderObject) ){
					bLastFibElementFound = true;
				}else if ( bLastFibElementFound ){
					//next Fib element
					const unsignedIntFib uiNumberOfElements =
						(*actualUnderObject)->getNumberOfElements( cType );
					if ( lNumber <= uiNumberOfElements ){
						//the Fib element is in the underobject
						return (*actualUnderObject)->getConstFibElement( cType, lNumber );
					}
					lNumber -= uiNumberOfElements;
				}
			}
		}
		if ( pSuperiorElement ){
			return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
		}//else no such next Fib element
		return NULL;
	}//else (lNumber < 0) -> search in direction lower from the last Fib element
	bool bLastFibElementFound = false;
	for (list<cFibElement*>::const_reverse_iterator actualUnderObject = fibUnderObjects.rbegin();
			actualUnderObject != fibUnderObjects.rend(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			if ( bLastFibElementFound ){
				//next Fib element
				const unsignedIntFib uiNumberOfElements =
					(*actualUnderObject)->getNumberOfElements( cType );
				lNumber += uiNumberOfElements;
				if ( 0 <= lNumber ){
					//the Fib element is in the underobject
					lNumber++;
					return (*actualUnderObject)->getConstFibElement( cType, lNumber );
				}
			}else if ( pLastFibElement == (*actualUnderObject) ){
				bLastFibElementFound = true;
			}
		}
	}
	if ( (lNumber == -1) && ( getType() == cType ) ){
		//this is the correct Fib element
		return const_cast<cFibBranch*>( this );
	}//else
	
	//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		if ( getType() == cType ){
			lNumber++;//remove this Fib element from the count
		}
		return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
	}//else
	
	return NULL;
}


#else//FEATURE_FAST_UPDATE


/**
 * This method checks, if this Fib element is an valid Fib element.
 *
 * @return true if this Fib element is an valid Fib element, else false
 */
bool cFibBranch::isValidFibElement() const{
	
	if ( ( pSuperiorElement != NULL ) && (pPreviousFibElement == NULL) ){
		//if this is not a topmost Fib element it need a previos element
		return false;
	}

	if ( pNextFibElement == NULL ){
		/*every branch Fib element need an next Fib element
		-> Fib element incorrect*/
		return false;
	}
	if ( fibUnderObjects.empty() ){
		//no underobjects
		return false;
	}
	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) == NULL ){
			//incorrect underobject
			return false;
		}
	}
	//everything is ok
	return true;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This function compares the second element of two pairs.
 *
 * @param pairFirst the first pair of which to compare the second element
 * @param pairSecound the second pair of which to compare the second element
 * @return true if the second element of the pairFirst is lower than the
 * 	second element of pairSecound
 */
bool lower_second_pair_element( const pair<size_t, size_t> &pairFirst,
		const pair<size_t, size_t> &pairSecound ){

	return ( pairFirst.second < pairSecound.second );
}


#ifndef SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method returns a number of (lNumberOfMaxReturnedElements)
 * Fib elements beginning from the actual Fib element in the
 * given direction of the given type cType.
 * The actual Fib element will never be included in the returned list.
 *
 * @param cType the type of the Fib elements to return;
 * 	'w' stands for wrong/ not correct Fib elements
 * @param direction the direction, beginning from the reference 
 * 	Fib element, in which the to return Fib elements should stand
 * @param lNumberOfMaxReturnedElements the maximal number of 
 * 	Fib elements to return
 * @return a list with the pointers to the to returning Fib elements
 */
list<cFibElement*> cFibBranch::getAllFibElementsFromPosition(
		char cType, edDirection direction,
		unsignedLongFib lNumberOfMaxReturnedElements ){
	
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return list<cFibElement*>();
	}
#endif //FEATURE_FAST_UPDATE
	unsignedLongFib lOldNumberOfMaxReturnedElements = lNumberOfMaxReturnedElements;
	
	/*list with the founded elements for the underobjects, wher 0 is the 
	superior element*/
	vector< list<cFibElement*> > vecFoundedElementsOfUnderobjects(
		fibUnderObjects.size() + 1, list<cFibElement*>() );

	/*if the direction is ED_ALL, ED_BELOW or ED_BELOW_EQUAL add
	lNumberOfMaxReturnedElements Fib elements below to the list*/
	if ( ( ! fibUnderObjects.empty() ) && //if empty nothing is below
			( ( direction == ED_ALL ) || ( direction == ED_BELOW ) ||
				( direction == ED_BELOW_EQUAL ) ) ){
		
		//try to get the Fib elements of the underobjects
		unsignedLongFib lNumberOfEntriesToBeFoundPerObject = 0;
		if (direction == ED_ALL){
			lNumberOfEntriesToBeFoundPerObject =
				(lOldNumberOfMaxReturnedElements / (fibUnderObjects.size() + 1) ) + 1;
		}else{
			lNumberOfEntriesToBeFoundPerObject =
				(lOldNumberOfMaxReturnedElements / fibUnderObjects.size() ) + 1;
		}
		
		size_t actualUnderObject = 1;
		for ( list<cFibElement*>::const_iterator itrActualUnderobject = fibUnderObjects.begin();
				( actualUnderObject <= fibUnderObjects.size() &&
				( itrActualUnderobject != fibUnderObjects.end() ) ) ;
				actualUnderObject++, itrActualUnderobject++ ){
		
			if ( (*itrActualUnderobject) == NULL ){
				//next underobject
				continue;
			}
			//add the underobject, if it has the correct type
			bool bFindMoreFibElements = true;
			if ( (cType == 'u') || ((*itrActualUnderobject)->getType() == cType) ||
					( (cType == 'w') && (!((*itrActualUnderobject)->isValidFibElement())) ) ){
				//next element has the correct type -> it will be added
				if ( lNumberOfMaxReturnedElements != 0 ){
					//the reference element will be added
					lNumberOfMaxReturnedElements--;
					if ( lNumberOfMaxReturnedElements == 0 ){
						bFindMoreFibElements = false;
					}
				}
			}
			//find more entries
			if ( bFindMoreFibElements ){
				vecFoundedElementsOfUnderobjects[ actualUnderObject ] =
					(*itrActualUnderobject)->getAllFibElementsFromPosition(
						cType, ED_BELOW, lNumberOfMaxReturnedElements );
			}
			
			if ( lOldNumberOfMaxReturnedElements != 0 ){
				if ( vecFoundedElementsOfUnderobjects[ actualUnderObject ].size()
						< lNumberOfEntriesToBeFoundPerObject ){
					
					lNumberOfMaxReturnedElements -=
						vecFoundedElementsOfUnderobjects[ actualUnderObject ].size();
				}else{
					lNumberOfMaxReturnedElements -= lNumberOfEntriesToBeFoundPerObject;
					lNumberOfMaxReturnedElements++;
				}
				if ( lNumberOfMaxReturnedElements < lNumberOfEntriesToBeFoundPerObject ){
					lNumberOfMaxReturnedElements = lNumberOfEntriesToBeFoundPerObject;
				}
			}
			if ( (cType == 'u') || ((*itrActualUnderobject)->getType() == cType) ||
					( (cType == 'w') && (!((*itrActualUnderobject)->isValidFibElement())) ) ){
				//next element has the correct type -> it will be added
				vecFoundedElementsOfUnderobjects[ actualUnderObject ].push_front(
					(*itrActualUnderobject) );
			}
		}
	}

	if (  (direction == ED_ALL) || (direction == ED_HIGHER) ||
			(direction == ED_HIGHER_EQUAL) ){

		if ( pSuperiorElement != NULL ){
	
			/*if the direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL add
			lNumberOfMaxReturnedElements Fib elements higher to the list*/
				//add the pSuperiorElement, if it has the correct type
			bool bFindMoreFibElements = true;
			if ( (cType == 'u') || (pSuperiorElement->getType() == cType)  ||
					( (cType == 'w') && ( ! (pSuperiorElement->isValidFibElement()) ) )){
				//previous element has the correct type -> it will be added
				if ( lNumberOfMaxReturnedElements != 0 ){
					//the reference element will be added
					lNumberOfMaxReturnedElements--;
					if ( lNumberOfMaxReturnedElements == 0 ){
						bFindMoreFibElements = false;
					}
				}
			}
			
			//find more entries
			if ( bFindMoreFibElements ){
				vecFoundedElementsOfUnderobjects[0] = pSuperiorElement->getAllFibElementsFromPosition(
					cType, ED_HIGHER, lNumberOfMaxReturnedElements );
			}
		
			if ( (cType == 'u') || (pSuperiorElement->getType() == cType)  ||
					( (cType == 'w') && ( ! (pSuperiorElement->isValidFibElement()) ) )){
				//previous element has the correct type -> it will be added
				vecFoundedElementsOfUnderobjects[0].push_front( pSuperiorElement );
			}
		}
		if ( (direction == ED_HIGHER) || (direction == ED_HIGHER_EQUAL) ){
			//all elements to give back are found
			return vecFoundedElementsOfUnderobjects[0];
		}
	}
	//give back the correct number of Fib elements
	list<cFibElement*> liFoundedElements;
	if ( lOldNumberOfMaxReturnedElements == 0 ){
		//give back all entries found
		for ( size_t actualUnderobject = 0;
				actualUnderobject < vecFoundedElementsOfUnderobjects.size();
				actualUnderobject++ ){
			liFoundedElements.insert( liFoundedElements.end(),
				vecFoundedElementsOfUnderobjects[ actualUnderobject ].begin(),
				vecFoundedElementsOfUnderobjects[ actualUnderobject ].end() );
		}
		return liFoundedElements;
	}//else
	
	/*every listentry stands for one list of founded elements of 
	vecFoundedElementsOfUnderobjects, wher the first number is the number
	of the list in the vector of vecFoundedElementsOfUnderobjects and the 
	second number the number of the elements found in the list*/
	list< pair<size_t, size_t> > liOfNumberOfEntriesFoundPerObject;
	
	for ( size_t actualUnderobject = 0;
			actualUnderobject < vecFoundedElementsOfUnderobjects.size();
			actualUnderobject++ ){
		if ( ! vecFoundedElementsOfUnderobjects[ actualUnderobject ].empty() ){
			
			liOfNumberOfEntriesFoundPerObject.push_back( make_pair(actualUnderobject,
				vecFoundedElementsOfUnderobjects[ actualUnderobject ].size() ) );
		}//else ignore empty lists
	}
	liOfNumberOfEntriesFoundPerObject.sort( lower_second_pair_element );
	
	/*if the remove the elements that are to much*/
	
	unsignedLongFib ulNumberOfListsToInclude =
		liOfNumberOfEntriesFoundPerObject.size();
	
	if ( ulNumberOfListsToInclude == 0 ){
		return liFoundedElements;
	}
	
	unsignedLongFib lNumberOfEntriesToBeFoundPerObject =
			(lOldNumberOfMaxReturnedElements / ulNumberOfListsToInclude ) + 1;
	
	/*add the underobject lists beginning with the smalest, so if the
	smalest underobject lists haven't enoght elements, more elements
	can be added from bigger lists*/
	for ( list< pair<size_t, size_t> >::iterator itrActualList =
			liOfNumberOfEntriesFoundPerObject.begin();
			itrActualList != liOfNumberOfEntriesFoundPerObject.end();
			itrActualList++ ){
			
		if ( (itrActualList->second < lNumberOfEntriesToBeFoundPerObject) &&
				(itrActualList->second < lOldNumberOfMaxReturnedElements - liFoundedElements.size()) ){
			//insert all elements of the underobject list to the return list
			liFoundedElements.insert( liFoundedElements.begin(),
				vecFoundedElementsOfUnderobjects[ itrActualList->first ].begin(),
				vecFoundedElementsOfUnderobjects[ itrActualList->first ].end() );
			
			vecFoundedElementsOfUnderobjects[ itrActualList->first ].clear();
		}else{
			/*insert lNumberOfEntriesToBeFoundPerObject elements of the
			underobject list to the return list*/
			for ( unsignedLongFib ulActualElement = 0;
					ulActualElement < lNumberOfEntriesToBeFoundPerObject;
					ulActualElement++ ){
				
				if ( lOldNumberOfMaxReturnedElements <= liFoundedElements.size() ){
					//enought elements in the return list
					break;
				}
				
				liFoundedElements.push_back(
					vecFoundedElementsOfUnderobjects[ itrActualList->first ].front() );
				
				vecFoundedElementsOfUnderobjects[ itrActualList->first ].pop_front();
				
				if ( vecFoundedElementsOfUnderobjects[ itrActualList->first ].empty() ){
					break;
				}
			}
		}
		ulNumberOfListsToInclude--;
		
		if ( ( liFoundedElements.size() < lOldNumberOfMaxReturnedElements ) &&
				(ulNumberOfListsToInclude != 0) ){

			lNumberOfEntriesToBeFoundPerObject =
				((lOldNumberOfMaxReturnedElements - liFoundedElements.size()) /
				ulNumberOfListsToInclude ) + 1;
		}else{//enought elements inserted
			break;
		}
	}
	/*if still elements are missing -> insert the remaining elements, one
	from each remaining not empty sublist in every round*/
	list< pair<size_t, size_t> >::iterator itrActualList =
			liOfNumberOfEntriesFoundPerObject.begin();
	while ( ( liFoundedElements.size() < lOldNumberOfMaxReturnedElements ) &&
			( ! liOfNumberOfEntriesFoundPerObject.empty() ) ){
		
		if ( itrActualList == liOfNumberOfEntriesFoundPerObject.end() ){
			itrActualList = liOfNumberOfEntriesFoundPerObject.begin();
			continue;
		}
		if ( vecFoundedElementsOfUnderobjects[ itrActualList->first ].empty() ){
			//remove entrys for empty lists
			itrActualList = liOfNumberOfEntriesFoundPerObject.erase( itrActualList );
			continue;
		}//else list not empty
		liFoundedElements.push_back(
			vecFoundedElementsOfUnderobjects[ itrActualList->first ].front() );
		
		vecFoundedElementsOfUnderobjects[ itrActualList->first ].pop_front();
		//go to next sublist
		itrActualList++;
	}
	
	return liFoundedElements;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param variable the variable to check if it is used
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return true if the variable is used, else false
 */
bool cFibBranch::isUsedVariable( const cFibVariable *variable,
		edDirection direction ) const{
	
	if ( direction == ED_POSITION ){
		return false;
	}
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( ! fibUnderObjects.empty() ){
			//check for all underobjects
			for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject != fibUnderObjects.end(); actualUnderObject++){
	
				if ( (*actualUnderObject) != NULL ){
					if ( (*actualUnderObject)->isUsedVariable( variable, ED_BELOW_EQUAL ) ){
						return true;
					}
				}
			}
		}//else no elements to check in the direction
		if (direction != ED_ALL){
			return false;
		}//else direction==ED_ALL check other direction
	}//direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL
	
	if ( pSuperiorElement != NULL ){
		//no elements to check in the direction
		return pSuperiorElement->isUsedVariable( variable , ED_HIGHER_EQUAL );
	}//else no elements to check in the direction
	return false;
}


/**
 * This method returns all variables used in the given direction from
 * this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
set<cFibVariable*> cFibBranch::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( direction == ED_POSITION ){
		return setUsedVariables;
	}
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( ! fibUnderObjects.empty() ){
			//check for all underobjects
			for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject!=fibUnderObjects.end(); actualUnderObject++){
	
				if ( (*actualUnderObject) != NULL ){
					set<cFibVariable*> setUsedVariablesOfUnderObject =
						(*actualUnderObject)->getUsedVariables( ED_BELOW_EQUAL );
					setUsedVariables.insert( setUsedVariablesOfUnderObject.begin(),
						setUsedVariablesOfUnderObject.end() );
				}
			}
		}//else no elements to check in the direction
		if (direction != ED_ALL){
			return setUsedVariables;
		}//else direction==ED_ALL check other direction
	}//direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL
	
	if ( pSuperiorElement != NULL ){
		//elements to check in the direction
		set<cFibVariable*> setUsedVariablesOfSuperObject =
			pSuperiorElement->getUsedVariables( ED_HIGHER_EQUAL );
		
		setUsedVariables.insert( setUsedVariablesOfSuperObject.begin(),
						setUsedVariablesOfSuperObject.end() );
	}//else no elements to check in the direction
	return setUsedVariables;
}


/**
 * This method checks if the given variable is defined in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param variable the variable to check if it is defined
 * @param direction the direction from this Fib element, in which the
 * 	variable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib Element which called this method
 * @return true if the variable is used, else false
 */
bool cFibBranch::isDefinedVariableInternal( const cFibVariable *variable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( direction == ED_POSITION ){
		return false;
	}
	
	if ( (direction == ED_ALL) || (direction == ED_BELOW) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( !fibUnderObjects.empty() ){
			//check for all underobjects
			for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
	
				if ( (*actualUnderObject) != NULL ){
					if ( (*actualUnderObject)->isDefinedVariableInternal(
							variable, ED_BELOW_EQUAL, this ) ){
						return true;
					}
				}
			}
		}//else no elements to check in the direction
		if (direction != ED_ALL){
			return false;
		}//else direction==ED_ALL check other direction
	}//direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL
	
	if ( pSuperiorElement != NULL ){
		//no elements to check in the direction
		return pSuperiorElement->isDefinedVariableInternal(
			variable , ED_HIGHER_EQUAL, this );
	}//else no elements to check in the direction
	return false;
}


/**
 * This method returns all variables defined in the given direction from
 * this Fib element.
 * This is for intern use to get the correct data from
 * getDefinedVariables() without pCallingFibElement.
 *
 * @see cFibVariable
 * @see getUsedVariables()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @param pCallingFibElement the Fib Element which called this method
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
list<cFibVariable*> cFibBranch::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){
	
	list<cFibVariable*> liDefinedVariables;
	if ( direction == ED_POSITION ){
		return liDefinedVariables;
	}
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( ! fibUnderObjects.empty() ){
			//check for all underobjects
			for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject!=fibUnderObjects.end(); actualUnderObject++ ){
	
				if ( (*actualUnderObject) != NULL ){
					list<cFibVariable*> liDefinedVariablesOfUnderObject =
						(*actualUnderObject)->getDefinedVariablesInternal( ED_BELOW_EQUAL, this );
					liDefinedVariables.insert( liDefinedVariables.end() ,
						liDefinedVariablesOfUnderObject.begin(),
						liDefinedVariablesOfUnderObject.end() );
				}
			}
		}//else no elements to check in the direction
		if (direction != ED_ALL){
			return liDefinedVariables;
		}//else direction==ED_ALL check other direction
	}//direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL
	
	if ( pSuperiorElement != NULL ){
		//elements to check in the direction
		list<cFibVariable*> liDefinedVariablesOfSuperObject =
			pSuperiorElement->getDefinedVariablesInternal( ED_HIGHER_EQUAL, this );
		
		liDefinedVariables.insert( liDefinedVariables.begin(),
						 liDefinedVariablesOfSuperObject.begin(),
						liDefinedVariablesOfSuperObject.end() );
	}//else no elements to check in the direction
	return liDefinedVariables;
}

#endif //SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method replace the variable variableOld with the variable
 * variableNew in the object.
 * Don't touch variable definitions, just the uses of the varaible
 * variableOld will be changed.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @see isDefinedVariable()
 * @param variableOld the variable to replace
 * @param variableNew the variable with which the variable variableOld
 * 	is to replace
 * @return true if the variable variableOld is replaced with variableNew,
 * 	else false
 */
bool cFibBranch::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	bool bVariableReplaced = true;
	if ( !fibUnderObjects.empty() ){
		//replace the variable in all underobjects
		for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++){

			if ( (*actualUnderObject) != NULL ){
				bVariableReplaced &= (*actualUnderObject)->replaceVariable(
					variableOld, variableNew );
			}
		}
	}
	return bVariableReplaced;
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method returns the number of this Fib element in the order of
 * Fib Elements or order of Fib Elements of the same type if bOfType
 * is true.
 *
 * @see getNumberOfElements()
 * @param bOfType if true the returned number is the number the order
 * 	of Fib elements of the same type as this Fib Element, else in
 * 	the order of all Fib elements
 * @return the number of this Fib element in the order of fib
 * 	-Elements or order of Fib Elements of the same type if bOfType
 * 	is true
 */
unsignedIntFib cFibBranch::getNumberOfElement( bool bOfType ) const{
	
	if ( pSuperiorElement ){
		if ( bOfType ){
			return pSuperiorElement->getNumberOfElementUp( this, getType() ) + 1;
		}
		return pSuperiorElement->getNumberOfElementUp( this, 'u' ) + 1;
	}//else
	return 1;
}


/**
 * This method is a helpmethod for getNumberOfElement() .
 * Basicly it counts the number of Fib elements of the given type befor
 * the given Fib element pLastFibElement .
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @param pLastFibElement a pointer to the Fib element which called this
 * 	method last
 * @param cType the type of the Fib elements, for which to evalue the count,
 * 	if 'u' Fib elements of all typs are counted
 * @return the number of Fib elements of the given type cType befor the
 * 	given Fib element pLastFibElement
 */
unsignedIntFib cFibBranch::getNumberOfElementUp(
		const cFibElement * pLastFibElement, const char cType ) const{
	
	unsignedIntFib uiNumberOfElement = 0;
	
	if ( ( cType == 'u' ) || ( getType() == cType ) ){
		//count this fib element
		uiNumberOfElement++;
	}
	
	bool bLastFibElementFound = false;
	for (list<cFibElement*>::const_reverse_iterator actualUnderObject = fibUnderObjects.rbegin();
			actualUnderObject != fibUnderObjects.rend(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			if ( pLastFibElement == (*actualUnderObject) ){
				bLastFibElementFound = true;
			}else if ( bLastFibElementFound ){
				//add the Fib elements of the given type to the count
				uiNumberOfElement += (*actualUnderObject)->getNumberOfElements( cType );
			}
		}
	}
	if ( pSuperiorElement ){
		return pSuperiorElement->getNumberOfElementUp( this, cType ) +
			uiNumberOfElement;
	}//else done counting
	return uiNumberOfElement;
}


/**
 * This method returns the number of this Fib element in the order of
 * move points.
 *
 * @see getNumberOfMovePoints()
 * @return the number of this Fib element in the order of move points
 */
unsignedIntFib cFibBranch::getNumberOfMovePoint() const{
	
	//this Fib element is not movable -> it is no move point
	return 0;
}


/**
 * This method is a helpmethod for getNumberOfMovePoint() .
 * Basicly it counts the number of move points befor the given
 * Fib element pLastFibElement .
 *
 * @see getNumberOfMovePoint()
 * @see getNumberOfMovePoints()
 * @param pLastFibElement a pointer to the Fib element which called this
 * 	method last
 * @return the number of movepoints befor the given Fib element pLastFibElement
 */
unsignedIntFib cFibBranch::getNumberOfMovePointUp(
		const cFibElement * pLastFibElement ) const{
	
	unsignedIntFib uiNumberOfMovePoint = 0;
	
	bool bLastFibElementFound = false;
	for (list<cFibElement*>::const_reverse_iterator actualUnderObject = fibUnderObjects.rbegin();
			actualUnderObject != fibUnderObjects.rend(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			if ( pLastFibElement == (*actualUnderObject) ){
				bLastFibElementFound = true;
			}else if ( bLastFibElementFound ){
				//add the Fib elements of the given type to the count
				uiNumberOfMovePoint += (*actualUnderObject)->getNumberOfMovePoints();
			}
		}
	}
	if ( pSuperiorElement ){
		return pSuperiorElement->getNumberOfMovePointUp( this ) +
			uiNumberOfMovePoint;
	}//else done counting
	return uiNumberOfMovePoint;
}


/**
 * This method returns the number of Fib elements of a type in this Fib
 * -object.
 *
 * @see getType()
 * @see getNumberOfElement()
 * @param cType the character of the type ( @see getType() ), for which
 * 	the elements should be counted; u (the standartvalue) stands for
 * 	Fib Elements of any type
 * @return the number of Fib elements of a type in the Fib object
 */
unsignedIntFib cFibBranch::getNumberOfElements( char cType ) const{

	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return 0;
	}
	return fibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::elementTypeToIndex( cType ) ];
}


/**
 * This method returns the number of move points in this Fib object.
 *
 * @see getNumberOfMovePoint()
 * @return the number of move points in this Fib object
 */
unsignedIntFib cFibBranch::getNumberOfMovePoints() const{
	//add number of Fib elements which are movebel
	return fibObjectCounts.getNumberOfMovePoints();
}


/**
 * This method returns the number of object points in this Fib object.
 *
 * @see getNumberOfObjectPoint()
 * @return the number of object points in this Fib object
 */
unsignedIntFib cFibBranch::getNumberOfObjectPoints() const{

	return fibObjectCounts.uiNumberOfObjectpoints;
}


#else //FEATURE_FAST_UPDATE

/**
 * This method returns the number of Fib elements of a type in this Fib
 * -object.
 *
 * @see getType()
 * @see getNumberOfElement()
 * @param cType the character of the type ( @see getType() ), for which
 * 	the elements should be counted; u (the standartvalue) stands for
 * 	Fib Elements of any type
 * @return the number of Fib elements of a type in the Fib object
 */
unsignedIntFib cFibBranch::getNumberOfElements( char cType ) const{
	unsignedIntFib uiNumberOfElements = 0;

	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){

		if ( (*actualUnderObject) != NULL ){
			uiNumberOfElements += (*actualUnderObject)->getNumberOfElements( cType );
		}
	}

	if ( (cType == 'u') || (getType() == cType) ){
		//this element has the correct type
		uiNumberOfElements++;
	}
	return uiNumberOfElements;
}

/**
 * This method returns the number of move points in this Fib object.
 *
 * @see getNumberOfMovePoint()
 * @return the number of move points in this Fib object
 */
unsignedIntFib cFibBranch::getNumberOfMovePoints() const{

	unsignedIntFib uiNumberOfMovePoints = 0;
	
	if ( isMovable() ){
		//this Fib element is movable -> it is a move point so count it
		uiNumberOfMovePoints = 1;
	}
	

	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){

		if ( (*actualUnderObject) != NULL ){
			uiNumberOfMovePoints += (*actualUnderObject)->getNumberOfMovePoints();
		}
	}
	return uiNumberOfMovePoints;
}


/**
 * This method returns the number of object points in this Fib object.
 *
 * @see getNumberOfObjectPoint()
 * @return the number of object points in this Fib object
 */
unsignedIntFib cFibBranch::getNumberOfObjectPoints() const{

	unsignedIntFib uiNumberOfObjectPoints=0;

	for (list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){

		if ( (*actualUnderObject) != NULL ){
			uiNumberOfObjectPoints += (*actualUnderObject)->getNumberOfObjectPoints();
			uiNumberOfObjectPoints++;//add the object point for the underobject
		}
	}
	return uiNumberOfObjectPoints;
}

#endif //FEATURE_FAST_UPDATE


#ifndef SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method returns the number of the Fib element over wich the
 * objectPoint object point is defined.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @param uiObjectPoint the number of the object point for which the
 * 	definig Fib element number should be returned
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return the number of the Fib element over wich the objectPoint
 * 	object point is defined
 */
unsignedIntFib cFibBranch::objectPointToElementPoint( const unsignedIntFib 
		uiObjectPoint, bool bAbsolute ) const{

	if ( uiObjectPoint == 0 ){
		//no such objectpoint
		return 0;
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->objectPointToElementPoint( uiObjectPoint );
	}//else lNumber is an relative value

#ifdef FEATURE_FAST_UPDATE
	if ( getNumberOfObjectPoints() < uiObjectPoint ){
		//no such objectpoint
		return 0;
	}
#endif //FEATURE_FAST_UPDATE
	
	unsignedIntFib uiRemainingObjects = uiObjectPoint;
	unsignedIntFib uiNumberOfFibElements = 1;//1 for this Fib element point

	list<cFibElement*>::const_iterator actualUnderObject;
	unsignedIntFib actualNumberOfUnderObjects;
	
	for ( actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){
		/*count the underobjectpoints in all underobjects befor the
		underobject for uINumberOfStartFibElement*/
		
		if ( (*actualUnderObject) == NULL ){
			continue;
		}
		
		if ( uiRemainingObjects <= 1 ){
			//next actualUnderObject is the correct object point -> done
			return uiNumberOfFibElements + 1;
		}
		
		actualNumberOfUnderObjects = (*actualUnderObject)->getNumberOfObjectPoints();
		actualNumberOfUnderObjects++;//add the object point for the actualUnderObject
		
		if ( uiRemainingObjects <= actualNumberOfUnderObjects ){
			//actualUnderObject branch is not befor the underobject uiObjectPoint -> done
			break;
		}
		//subtract number of underobjects in the actualUnderObject
		uiRemainingObjects -= actualNumberOfUnderObjects;

		//add elmenet points of the actualUnderObject
		uiNumberOfFibElements += (*actualUnderObject)->getNumberOfElements();
	}
	
	if ( actualUnderObject == fibUnderObjects.end() ){
		//all underobjects searched, but no such underobject in this object
		return (unsignedIntFib)(0);
	}
	
	uiRemainingObjects--;//decrase the object point for actualUnderObject
	
	unsignedIntFib uiNumberOfFibElementsActualUnderObject = 0;
	
	if ( (*actualUnderObject) != NULL ){
		uiNumberOfFibElementsActualUnderObject = (*actualUnderObject)->
			objectPointToElementPoint( uiRemainingObjects );
	}//else this==referenceFibObject or no pSuperiorElement -> all object points found
	
	if ( uiNumberOfFibElementsActualUnderObject == 0 ){
		//no such underobject
		return 0;
	}
	
	return uiNumberOfFibElements + uiNumberOfFibElementsActualUnderObject;
}


/**
 * This method inserts the given Fib element pFibElement on the
 * specified position. The replaced Fib element will be the underobject
 * of the inserted Fib element pFibElement.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type of the Fib element insted of which the given
 * 	Fib element pFibElement should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, in which position the given
 * 	Fib element pFibElement should be inserted; if 0 the given
 * 	pFibElement will be inserted under this Fib element
 * @param pFibElement a pointer to the the Fib element to insert
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return true if the Fib element pFibElement was inserted, else false
 */
bool cFibBranch::insertElement( cFibElement *pFibElement, const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute, bool bCheckVariables ){
	
	if ( pFibElement == NULL ){
		//nothing to insert
		return false;
	}
	if ( (pFibElement->getType() == 'r') ||
			(pFibElement->getType() == 'l') ||
			(pFibElement->getType() == 'i') ){
		//can't insert root, list or if-elements
		return false;
	}
	if ( pFibElement->getNumberOfElements() != 1 ){
		//more then one Fib element to insert
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	
	if ( elementPoint == 0 ){
		//replace the (first) underobject of this Fib element
		if ( ( fibUnderObjects.empty() ) ||
				( fibUnderObjects.front() == NULL ) ){
			//check if the variables used in the to insert Fib element are defined higer
			if ( bCheckVariables && ( ! variablesAreDefined( pFibElement->
					getUsedVariables( ED_POSITION ) , ED_HIGHER_EQUAL ) ) ){
				return false;
			}
#ifdef FEATURE_FAST_UPDATE
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibElement );;
#endif //FEATURE_FAST_UPDATE
			if ( fibUnderObjects.empty() ){
				if ( ( pFibElement->isLeaf() ) ||
						( pFibElement->getType() == 'o' ) ||
						( getType() == 'l' ) ){
					/*insert Fib element which don't need subobjects
					or this Fib element was invalid befor
					(don't make the Fib element invalid)*/
					fibUnderObjects.push_front( pFibElement );
#ifdef FEATURE_FAST_UPDATE
					fibObjectCountsDelta.uiNumberOfObjectpoints++;
#endif //FEATURE_FAST_UPDATE
				}else{//can't insert non leaf, because a subobject for it is missing
					return false;
				}
			}else{//( fibUnderObjects.front() == NULL )
				fibUnderObjects.front() = pFibElement;
			}
#ifdef FEATURE_FAST_UPDATE
			if ( pFibElement->pSuperiorElement != NULL ){
				pFibElement->pSuperiorElement->cutConnectionsTo(
					pFibElement );
			}
			pFibElement->pSuperiorElement = this;
			//update counters
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			return true;
		}
		return insertElement( pFibElement, 'u', 2, false, bCheckVariables );
	}
	if ( bAbsolute ){
		return getMasterRoot()->insertElement( pFibElement, cType, elementPoint,
			false, bCheckVariables );
	}//else elementPoint is an relative value
//#define FEATURE_FIB_ELEMENT_LAST_INSERT
#ifdef FEATURE_FIB_ELEMENT_LAST_INSERT
//This FEATURE didn't work correct and is logical not sound

	cFibElement * pFibElementToReplace = getFibElement( cType, elementPoint );
	if ( pFibElementToReplace == NULL ){
		if ( ( ! pFibElement->isLeaf() ) && ( pFibElement->getType() != 'o' )  ){
			//no Fib element to replace
			return false;
		}
		//try to insert in the last last Fib element
		cFibElement * pLastFibElement = getFibElement( getNumberOfElements() );
		if ( pLastFibElement == this ){
			//insert leaf in this Fib element
			if ( getType() == 'r' ){
				//can't insert in a root-element
				return false;
			}
			//check if the variables used in the to insert Fib element are defined higer
			if ( bCheckVariables &&( ! variablesAreDefined( pFibElement->
					getUsedVariables( ED_POSITION ) , ED_HIGHER_EQUAL ) ) ){
				return false;
			}
			//insert the leaf element into this branchelement
			fibUnderObjects.push_back( pFibElement );
#ifdef FEATURE_FAST_UPDATE
			if ( pFibElement->pSuperiorElement != NULL ){
				pFibElement->pSuperiorElement->cutConnectionsTo(
					pFibElement );
			}
			pFibElement->pSuperiorElement = this;
			//update counters
			cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibElement );
			fibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			return true;
		}
		return pLastFibElement->insertElement( pFibElement, 'u', 0, false, bCheckVariables );
	}
	
	if ( (pFibElementToReplace != NULL) &&
			( pFibElementToReplace->getType() == 'r') ){
		//no Fib element to replace
		return false;
	}
	
#else //FEATURE_FIB_ELEMENT_LAST_INSERT

	cFibElement * pFibElementToReplace = getFibElement( cType, elementPoint );
	if ( ( (pFibElementToReplace == NULL) && ( ! pFibElement->isLeaf() ) &&
				( pFibElement->getType() != 'o' ) ) ||
			( (pFibElementToReplace != NULL) &&
				( pFibElementToReplace->getType() == 'r') ) ){
		//no Fib element to replace
		return false;
	}
#endif //FEATURE_FIB_ELEMENT_LAST_INSERT

	/*check ( if (cType=='u') ) if the pFibElement should replace a
	underobject of this object*/
	if ( cType == 'u' ){
		if ( elementPoint == 2 ){
			//insert the pFibElement in this branch -Fib element
			if ( pFibElement->isLeaf() ){
				if ( getType() == 'r' ){
					//can't insert in a root-element
					return false;
				}
				//check if the variables used in the to insert Fib element are defined higher
				if ( bCheckVariables &&( ! variablesAreDefined(
						pFibElement->getUsedVariables( ED_POSITION ) ,
						ED_HIGHER ) ) ){
					return false;
				}
				//insert the leaf element into this branchelement
				fibUnderObjects.push_front( pFibElement );
#ifdef FEATURE_FAST_UPDATE
				if ( pFibElement->pSuperiorElement != NULL ){
					pFibElement->pSuperiorElement->cutConnectionsTo(
						pFibElement );
				}
				pFibElement->pSuperiorElement = this;
				//update counters
				cFibObjectCounts fibObjectCountsDelta = evalueCountersForObject( pFibElement );
				fibObjectCountsDelta.uiNumberOfObjectpoints++;
				updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
				updateAllValues();
#endif //FEATURE_FAST_UPDATE
				return true;
			}
		}
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
#ifdef FEATURE_FAST_UPDATE
				if ( (*actualUnderObject) == pFibElementToReplace ){
#else //FEATURE_FAST_UPDATE
				if ( ((*actualUnderObject)->getNumberOfElement()) ==
						pFibElementToReplace->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
					//replace the actualUnderObject with the given pFibElement
					
					/* check if the variables used in the to insert Fib element
					 * are defined above the to replace Fib element*/
					if ( bCheckVariables ){
						
						if ( pFibElement->isLeaf() ){
							/*leaf elements are inserted as new subobjects in this object
							-> don't check the variables this branch element defines*/
							if ( ! variablesAreDefined(
									pFibElement->getUsedVariables( ED_POSITION ),
									ED_HIGHER ) ){
								return false;
							}
						}else{/*element is inserted and will contain existing
							subobject pFibElementToReplace
							-> check the variables this branch element define for
							pFibElementToReplace*/
							if ( ! pFibElementToReplace->variablesAreDefined(
									pFibElement->getUsedVariables( ED_POSITION ),
									ED_HIGHER ) ){
								return false;
							}
						}
					}
#ifdef FEATURE_FAST_UPDATE
					if ( pFibElement->isLeaf() ){
						fibUnderObjects.insert( actualUnderObject, pFibElement );
						if ( pFibElement->pSuperiorElement != NULL ){
							pFibElement->pSuperiorElement->cutConnectionsTo(
								pFibElement );
						}
						pFibElement->pSuperiorElement = this;
						//update counters
						cFibObjectCounts fibObjectCountsDelta;
						fibObjectCountsDelta.vecNumberOfFibElements[
							cFibObjectCounts::elementTypeToIndex( pFibElement->getType() ) ]++;
						fibObjectCountsDelta.vecNumberOfFibElements[ cFibObjectCounts::ALL ]++;
						fibObjectCountsDelta.uiNumberOfObjectpoints++;
						updateAllCounters( fibObjectCountsDelta );
						//done and pFibElement inserted
						return true;
					}//else not a leaf element
					//set the underobject of the pFibElement
					(*actualUnderObject)->pSuperiorElement = NULL;
					const bool bUnderObjectReplaced =
						pFibElement->insertObjectInElement( (*actualUnderObject) );
					if ( ! bUnderObjectReplaced ){
						//can't replace the underobject
						return false;
					}
					cFibObjectCounts fibObjectCountsDelta;
					fibObjectCountsDelta -= evalueCountersForObject( (*actualUnderObject) );
					//set the new underobject of this element
					(*actualUnderObject) = pFibElement;
					if ( pFibElement->pSuperiorElement != NULL ){
						pFibElement->pSuperiorElement->cutConnectionsTo(
							pFibElement );
					}
					pFibElement->pSuperiorElement = this;
					//update counters
					fibObjectCountsDelta += evalueCountersForObject( (*actualUnderObject) );
					
					updateAllCounters( fibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
					if ( pFibElement->isLeaf() ){
						fibUnderObjects.insert( actualUnderObject, pFibElement );
						updateAllValues();
						//done and pFibElement inserted
						return true;
					}
					//set the underobject of the pFibElement
					const bool bUnderObjectReplaced =
						pFibElement->insertObjectInElement( (*actualUnderObject) );
					if ( ! bUnderObjectReplaced ){
						//can't replace the underobject
						return false;
					}
					//set the new underobject of this element
					(*actualUnderObject) = pFibElement;
					updateAllValues();
#endif //FEATURE_FAST_UPDATE
					//done and pFibElement inserted
					return true;
				}
			}//end if (actualUnderObject!=NULL )
		}//end for
	}
	
	/*get the pSuperiorElement of the to replacing object and call
	insertElement of theas*/
	if ( (pFibElementToReplace != NULL) &&
			( pFibElementToReplace->pSuperiorElement != NULL ) ){
			
		return pFibElementToReplace->pSuperiorElement->insertElement(
			pFibElement, 'u', (pFibElementToReplace->getNumberOfElement()) + 1 -
			(pFibElementToReplace->pSuperiorElement->getNumberOfElement() ),
			false, bCheckVariables );
		
	}//else the to replace Fib element dosn't exists or is the topmost
	return false;
}


/**
 * This method inserts the given Fib object pFibObject on the
 * specified position. On the specified position a listelement will
 * be inserted, with the old Fib object and the given Fib object
 * pFibObject as its underobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib element, on which position the 
 * 	given Fib object pFibObject should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, on which position the given
 * 	Fib object pFibObject should be inserted
 * @param pFibObject the Fib object to insert
 * @param first if true, the inserted object will be the first
 * 	underobject of the new listelement
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return true if the Fib object pFibObject was inserted, else false
 */
bool cFibBranch::insertObjectInElement( cFibElement * pFibObject, const char cType,
		const unsignedIntFib elementPoint, bool first, bool bAbsolute ){
	
	if ( pFibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( pFibObject->getType() == 'r' ){
		//can't insert a root-element
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE

	if ( elementPoint == 0 ){
		//insert for the (first) underobject of this Fib element

		if ( fibUnderObjects.empty() ){
			//insert in this branchelement
			if ( pFibObject->pSuperiorElement != NULL ){
				pFibObject->pSuperiorElement->cutConnectionsTo(
					pFibObject );
			}
			pFibObject->pSuperiorElement = this;
			
			fibUnderObjects.push_front( pFibObject );
#ifdef FEATURE_FAST_UPDATE
			
			cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
			pFibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( pFibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			//done with inserting
			return true;
		}else{
			//check if the underobject to overwrite is NULL
			list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			
			if ( getType() != 'r' ){
				if ( ( ! first ) && ( 1 < fibUnderObjects.size() ) ){
					actualUnderObject++;
				}
			}
			if ( (*actualUnderObject) == NULL ){
				//overwrite the actualUnderObject NULL object
				
				//set the values of the pFibObject
#ifdef FEATURE_FAST_UPDATE
				if ( pFibObject->pSuperiorElement != NULL ){
					pFibObject->pSuperiorElement->cutConnectionsTo(
						pFibObject );
				}
				pFibObject->pSuperiorElement = this;
				(*actualUnderObject) = pFibObject;
				
				cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
				pFibObjectCountsDelta.uiNumberOfObjectpoints++;
				updateAllCounters( pFibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
				pFibObject->pSuperiorElement = this;
				(*actualUnderObject) = pFibObject;
				
				updateAllValues();
#endif //FEATURE_FAST_UPDATE
				//done with inserting
				return true;
			}
		}
		return insertObjectInElement( pFibObject, 'u', 2, first );
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->insertObjectInElement( pFibObject, cType, elementPoint, first );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the pFibObject should inserted as an
	neibour of an underobject of this object*/
	cFibElement *pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r')){
		//no position to insert
		return false;
	}
	if ( cType == 'u' ){
		
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
#ifdef FEATURE_FAST_UPDATE
				if ( (*actualUnderObject) == pFibElementPosition ){
#else //FEATURE_FAST_UPDATE
				if ( ((*actualUnderObject)->getNumberOfElement()) ==
						pFibElementPosition->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
					//insert the given pFibObject
					if ( getType() == 'r'  ){
						//can't replace in a root-element an sub -root-element
						return false;
					}
					
					//set the values of the pFibObject
#ifdef FEATURE_FAST_UPDATE
					if ( pFibObject->pSuperiorElement != NULL ){
						pFibObject->pSuperiorElement->cutConnectionsTo(
							pFibObject );
					}
#endif //FEATURE_FAST_UPDATE
					pFibObject->pSuperiorElement = this;
					
					if ( first ){
						//insert pFibObject instead of the actualUnderObject
						fibUnderObjects.insert( actualUnderObject, pFibObject );
					}else{
						//insert pFibObject after the actualUnderObject
						actualUnderObject++;
						fibUnderObjects.insert( actualUnderObject, pFibObject );
					}
#ifdef FEATURE_FAST_UPDATE
					cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
					pFibObjectCountsDelta.uiNumberOfObjectpoints++;
					updateAllCounters( pFibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
					updateAllValues();
#endif //FEATURE_FAST_UPDATE
					//done and fibElement inserted
					return true;
				}
			}//end if (actualUnderObject!=NULL )
		}//end for
	}
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	if ( pFibElementPosition->pSuperiorElement != NULL ){
			
			return pFibElementPosition->pSuperiorElement->insertObjectInElement(
				pFibObject, 'u',
				(pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				first );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}


/**
 * This method overwrites the Fib object on specified position with
 * the given Fib object pFibObject. The Fib object on specified
 * position will be replaced with the given Fib object pFibObject.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see insertObjectInElement()
 * @see getType()
 * @param cType the type of the Fib element, on which position the 
 * 	given Fib object pFibObject should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, on which position the given
 * 	Fib object pFibObject should be inserted
 * @param pFibObject the Fib object to insert
 * @param bDeleteOld if true, delete the old Fib object from the memory
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib object
 * @return true if the old Fib object was overwritten and the given 
 * 	Fib object pFibObject was inserted, else false
 */
bool cFibBranch::overwriteObjectWithObject( cFibElement *pFibObject,
		const char cType, const unsignedIntFib elementPoint,
		bool bDeleteOld, bool bAbsolute ){
	
	DEBUG_OUT_L2(<<"cFibBranch::overwriteObjectWithObject( pFibObject="<<pFibObject<<", cType="<<cType<<", elementPoint="<<elementPoint<<", bDeleteOld="<<(bDeleteOld?"true":"false")<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	
	if ( pFibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( pFibObject->getType() == 'r' ){
		//can't insert a root-element
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE

	if ( elementPoint == 0 ){
		if ( fibUnderObjects.empty() ){
			//nothing to overwrite
			return false;
		}
		//insert for the (first) underobject of this Fib element
		
		//check if the underobject to overwrite is NULL
		if ( fibUnderObjects.front() == NULL ){
			//overwrite the actualUnderObject NULL object
			
			//set the values of the pFibObject
#ifdef FEATURE_FAST_UPDATE
			if ( pFibObject->pSuperiorElement != NULL ){
				pFibObject->pSuperiorElement->cutConnectionsTo(
					pFibObject );
			}
#endif //FEATURE_FAST_UPDATE
			pFibObject->pSuperiorElement = this;
		
			fibUnderObjects.front() = pFibObject;

#ifdef FEATURE_FAST_UPDATE
			cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
			pFibObjectCountsDelta.uiNumberOfObjectpoints++;
			updateAllCounters( pFibObjectCountsDelta );
#else //FEATURE_FAST_UPDATE
			pFibObject->pPreviousFibElement = this;
			updateAllValues();
#endif //FEATURE_FAST_UPDATE
			//done with inserting
			return true;
		}
		return overwriteObjectWithObject( pFibObject, 'u', 2, bDeleteOld );
	}
	if ( bAbsolute ){
		return getMasterRoot()->overwriteObjectWithObject( pFibObject, cType,
			elementPoint, bDeleteOld );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the pFibObject should inserted as an
	neibour of an underobject of this object*/
	cFibElement * pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition == NULL) || (pFibElementPosition->getType() == 'r') ){
		//no Fib object to overwrite
		return false;
	}
	if ( cType == 'u' ){
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
#ifdef FEATURE_FAST_UPDATE
			if ( (*actualUnderObject) == pFibElementPosition ){
				//insert the given pFibObject
				
				//set the values of the pFibObject
				if ( pFibObject->pSuperiorElement != NULL ){
					pFibObject->pSuperiorElement->cutConnectionsTo(
						pFibObject );
				}
				pFibObject->pSuperiorElement = this;
				//insert pFibObject instead of the actualUnderObject
				(*actualUnderObject) = pFibObject;
				
				//update the Fib objectcounters
				cFibObjectCounts pFibObjectCountsDelta = evalueCountersForObject( pFibObject );
				const cFibObjectCounts pFibObjectCountsOld =
					evalueCountersForObject( pFibElementPosition );
				pFibObjectCountsDelta -= pFibObjectCountsOld;
				updateAllCounters( pFibObjectCountsDelta );
				
				//remove old underobject
				if ( pFibElementPosition->pSuperiorElement == this ){
					pFibElementPosition->pSuperiorElement = NULL;
					if ( bDeleteOld ){
						DEBUG_OUT_L3(<<"cFibBranch::overwriteObjectWithObject() deleting pFibElementPosition"<<endl<<flush);
						pFibElementPosition->deleteObject();
					}//else don't delete
				}
				//done and pFibObject inserted
				DEBUG_OUT_L3(<<"cFibBranch::overwriteObjectWithObject() done pFibObject inserted"<<endl<<flush);
				return true;
			}
#else //FEATURE_FAST_UPDATE
			if (actualUnderObject != NULL ){
				if ( ((*actualUnderObject)->getNumberOfElement()) ==
						pFibElementPosition->getNumberOfElement() ){
					//insert the given pFibObject
					
					//set the values of the pFibObject
					pFibObject->pSuperiorElement = this;
					pFibObject->pPreviousFibElement =
						pFibElementPosition->pPreviousFibElement;
					
					//insert pFibObject instead of the actualUnderObject
					(*actualUnderObject) = pFibObject;
					
					//remove connections of pOldFibObject to this Fib object
					cFibElement * pLastFibElementInOld = pFibElementPosition->getFibElement(
							pFibElementPosition->getNumberOfElements() );
					if ( pLastFibElementInOld == NULL ){
						pLastFibElementInOld = pFibElementPosition;
					}
					if ( pFibElementPosition->pPreviousFibElement ){
						pFibElementPosition->pPreviousFibElement->pNextFibElement =
							pFibObject;
					}
					if ( pLastFibElementInOld->pNextFibElement ){
						pLastFibElementInOld->pNextFibElement->pPreviousFibElement = NULL;
					}
					pFibElementPosition->cutConnections( ED_HIGHER );
					pLastFibElementInOld->cutConnections( ED_BELOW );
					if ( bDeleteOld ){
						cFibElement::deleteObject( pFibElementPosition );
					}//else don't delete
					updateAllValues();
					//done and fibElement inserted
					return true;
				}
			}//end if (actualUnderObject!=NULL )
#endif //FEATURE_FAST_UPDATE
		}//end for
	}
	
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	if ( pFibElementPosition->pSuperiorElement != NULL ){
			
			DEBUG_OUT_L2(<<"cFibBranch::overwriteObjectWithObject() done calling overwriteObjectWithObject() on pFibElementPosition->pSuperiorElement"<<endl<<flush);
			return pFibElementPosition->pSuperiorElement->overwriteObjectWithObject(
				pFibObject, 'u', (pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				bDeleteOld );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}


/**
 * This method removes the connected object with the given number in
 * the order of connected object points.
 * For this the defining underobject in an listelement will be removed.
 * If the listelement contains after the operation yust one underobject,
 * the listelement will be replaced with the underobject.
 *
 * @param objectPoint the number of the connected object to remove
 * @param bDeleteOld if true, delete the connected object from the
 * 	memory, else yust remove it's pointers
 * @param bAbsolute if the objectPoint is an absolute value for the wool
 * 	Fib object
 * @return true if the connected Fib object was removed, else false
 */
bool cFibBranch::removeObject( const unsignedIntFib objectPoint,
		bool bDeleteOld, bool bAbsolute ){
	
	DEBUG_OUT_L2(<<"cFibBranch::removeObject("<<objectPoint<<", "<<bDeleteOld<<", "<<bAbsolute<<" ) called"<<endl<<flush);
	
	if ( objectPoint == 0 ){
		//can't remove whool object
		return false;
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->removeObject( objectPoint, bDeleteOld );
	}//else elementPoint is an relative value

	DEBUG_OUT_L2(<<"calling objectPointToElementPoint( "<<objectPoint<<" )"<<endl<<flush);
	unsignedIntFib uiDefiningElementPoint = objectPointToElementPoint( objectPoint );
	if ( uiDefiningElementPoint == 0 ){
		//no defining element point
		return false;
	}
	DEBUG_OUT_L2(<<"pDefiningFibElement = getFibElement( "<<uiDefiningElementPoint<<" )"<<endl<<flush);
	cFibElement * pDefiningFibElement = getFibElement( uiDefiningElementPoint );
	if ( pDefiningFibElement == NULL ){
		//nothing to remove
		return false;
	}
	DEBUG_OUT_L2(<<"get containing Fib element"<<endl<<flush);
	cFibElement * pContainingFibElement = pDefiningFibElement->pSuperiorElement;
	if ( pContainingFibElement == NULL ){
		//nowher to remove
		return false;
	}
	DEBUG_OUT_L2(<<"check type of containing Fib element"<<endl<<flush);
	if ( ( pContainingFibElement->getType() != 'l' ) &&
			( pContainingFibElement->getType() != 'o' ) ){
		//containing element is no listelement -> can't remove
		return false;
	}
	cFibBranch * pContainingBranchElement = (cFibBranch*)pContainingFibElement;
	
	if ( pContainingBranchElement->getType() == 'i' ){
		//can't remove objects from an if-element
		DEBUG_OUT_L2(<<"can't remove objects from an if-element "<<endl<<flush);
		return false;
	}
	
	DEBUG_OUT_L2(<<"searching for underobject: "<<pDefiningFibElement<<endl<<flush);
	
	for ( list<cFibElement*>::iterator actualUnderObject =
			pContainingBranchElement->fibUnderObjects.begin();
			actualUnderObject != pContainingBranchElement->fibUnderObjects.end();
			actualUnderObject++ ){
		if ( (*actualUnderObject) != NULL ){
			if ( (*actualUnderObject) == pDefiningFibElement ){
				//remove actualUnderObject
				DEBUG_OUT_L2(<<"underobject found "<<endl<<flush);
				
#ifdef FEATURE_FAST_UPDATE
				DEBUG_OUT_L2(<<"setting superior of underobject to NULL"<<endl<<flush);
				(*actualUnderObject)->pSuperiorElement = NULL;
				if ( bDeleteOld ){
					DEBUG_OUT_L2(<<"delete underobject "<<endl<<flush);
					(*actualUnderObject)->deleteObject();
				}//else don't delete
#else //FEATURE_FAST_UPDATE
				//change connections in the Fib object
				cFibElement * pLastFibElementInOld =
					(*actualUnderObject)->getFibElement(
						(*actualUnderObject)->getNumberOfElements() );
				if ( pLastFibElementInOld == NULL ){
					pLastFibElementInOld = (*actualUnderObject);
				}
				if ( (*actualUnderObject)->pPreviousFibElement ){
					(*actualUnderObject)->pPreviousFibElement->pNextFibElement =
						pLastFibElementInOld->pNextFibElement;
				}
				if ( pLastFibElementInOld->pNextFibElement ){
					pLastFibElementInOld->pNextFibElement->pPreviousFibElement =
						(*actualUnderObject)->pPreviousFibElement;
				}
				
				DEBUG_OUT_L2(<<"cut connections from underobject "<<endl<<flush);
				//remove connections of pOldFibObject to this Fib object
				(*actualUnderObject)->cutConnections( ED_HIGHER );
				pLastFibElementInOld->cutConnections( ED_BELOW );
				
				if ( bDeleteOld ){
					DEBUG_OUT_L2(<<"delete underobject "<<endl<<flush);
					cFibElement::deleteObject( (*actualUnderObject) );
				}//else don't delete
#endif //FEATURE_FAST_UPDATE
				
				DEBUG_OUT_L2(<<"erase underobject from list"<<endl<<flush);
				pContainingBranchElement->fibUnderObjects.erase(
					actualUnderObject );
				
				if ( ( pContainingBranchElement->getType() == 'l' ) &&
						( pContainingBranchElement->fibUnderObjects.size() == 1 ) &&
						( pContainingBranchElement->pSuperiorElement != NULL ) ){
					
					DEBUG_OUT_L2(<<"delete containing list element"<<endl<<flush);
					//erase the listelement
					cFibElement * pContainingSuperior =
						pContainingBranchElement->pSuperiorElement;

					cFibElement * pRemainingFibObject =
						pContainingBranchElement->fibUnderObjects.front();
					
					pContainingBranchElement->fibUnderObjects.clear();
					
					if ( pContainingSuperior->isBranch() ){
						//the superior is a branchelement
						//search in branchelement for the containing Fib element
						cFibBranch * pBranchContainingSuperior =
							(cFibBranch*)pContainingSuperior;
						
						for ( list<cFibElement*>::iterator actualUnderObjectSup =
								pBranchContainingSuperior->fibUnderObjects.begin();
								actualUnderObjectSup != pBranchContainingSuperior->fibUnderObjects.end();
								actualUnderObjectSup++ ){
							
							if ( ((*actualUnderObjectSup) != NULL) &&
									(*actualUnderObjectSup) == pContainingBranchElement ){
								
								(*actualUnderObjectSup) = pRemainingFibObject;
								
#ifndef FEATURE_FAST_UPDATE
								if ( pContainingBranchElement->pPreviousFibElement ){
									
									pContainingBranchElement->pPreviousFibElement->pNextFibElement =
										pRemainingFibObject;
								}
								pRemainingFibObject->pPreviousFibElement =
									pContainingBranchElement->pPreviousFibElement;
#endif //FEATURE_FAST_UPDATE
								break;
							}
						}
					}else{//the superior is a limbelement
						((cFibLimb*)pContainingSuperior)->pUnderObject = pRemainingFibObject;
#ifndef FEATURE_FAST_UPDATE
						pRemainingFibObject->pPreviousFibElement = pContainingSuperior;
#endif //FEATURE_FAST_UPDATE
					}
					pRemainingFibObject->pSuperiorElement = pContainingSuperior;
					pContainingFibElement = pContainingSuperior;
					
					delete pContainingBranchElement;
				}
				
				const char cContainingElementType =
					pContainingFibElement->getType();
				if ( cContainingElementType == 'r' ){
					//containing Fib element is a root-element
					((cRoot*)(pContainingFibElement))->syncSubobjects();
					
				}else if ( cContainingElementType == 'i' ){
					//containing Fib element is an if-element
					((cIf*)(pContainingFibElement))->syncSubobjects();
					
				}else if ( cContainingElementType == 'o' ){
					//containing Fib element is an external object element
					((cExtObject*)(pContainingFibElement))->syncSubobjects();
				}
				DEBUG_OUT_L2(<<"updateAllValues() from containing list element"<<endl<<flush);
				pContainingFibElement->updateAllValues();
				DEBUG_OUT_L2(<<"cFibBranch::removeObject("<<objectPoint<<", "<<bDeleteOld<<", "<<bAbsolute<<" ) done ok"<<endl<<flush);
				return true;
			}
		}
	}
	DEBUG_OUT_L2(<<"cFibBranch::removeObject("<<objectPoint<<", "<<bDeleteOld<<", "<<bAbsolute<<" ) done false"<<endl<<flush);
	return false;
}

#endif //SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method checks, if all Fib elements of this Fib object
 * have the underobjects they need to be correct.
 *
 * @return true if all Fib elements of this Fib object have the
 * 	underobjects they need to be correct, else false
 */
bool cFibBranch::hasUnderAllObjects() const{

	//check all underobjects
	for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) == NULL ){
			//no underobject
			return false;
		}
		if ( !(*actualUnderObject)->hasUnderAllObjects() ){
			//the underobject hasn't all underobjects
			return false;
		}
	}
	return true;
}

#ifndef SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method checks, if the Fib element on the specified position
 * is deletable.
 * An deletable Fib element doesn't make the Fib object invalid if
 * it is deleted (e.g. points- and listelements are never deletable).
 *
 * @see removeElement()
 * @see cutElement()
 * @see getType()
 * @param cType the type of the Fib element to check
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to check
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return true if the Fib element is deletable, else false
 */
bool cFibBranch::isRemovableElement( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute, bool bCheckVariables ) const{
	
	if ( ! cFibElement::isRemovableElement( cType, elementPoint, bAbsolute, bCheckVariables ) ){
		return false;
	}
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	
	if ( elementPoint == 0 ){
		//check this Fib element
		
		if ( getType() == 'r' ){
			//can't remove the root-element
			return false;
		}
		
		bool bOneUnderobject = false;
		
		for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				if ( bOneUnderobject ){
					//can't remove this element because it has more than one underobject
					return false;
				}
				bOneUnderobject = true;
			}
		}
		if ( ! bOneUnderobject ){
			/*if no subobjects -> element can just be removed if the
			superior element is a list element with more than 2
			subobjects or an external object element*/
			
			if ( pSuperiorElement == NULL ){
				//can't remove the topmost Fib element
				return false;
			}
			const char cTypeSuperior = pSuperiorElement->getType();
			
			if ( cTypeSuperior == 'o' ){
				//external object element -> removing this element from it is OK
				return true;
			}else if ( cTypeSuperior == 'l' ){
				/*list element -> removing this element/subobject from it
				is OK if it has at least 2 subobjects left after removing*/
				if ( 2 < ((cList*)(pSuperiorElement))->getNumberOfUnderobjects() ){
					//it has more than two subobjects -> can remove this
					return true;
				}else{//it has less than 3 subobjects -> can't remove this
					return false;
				}
			}else{//can't remove one subobject from other Fib element types
				return false;
			}
		}
		//no or one underobjects -> this Fib element can be removed
	}
	return true;
}


/**
 * This method cuts the Fib element on the specified position.
 * This works like removeElement(), except that the removed element is 
 * returned.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib element to cut
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to cut
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return the pointer to the cuted Fib element or NULL, if the Fib
 * 	-element couldn't cut
 */
cFibElement *cFibBranch::cutElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute, bool bCheckVariables ){

#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return NULL;
	}
#endif //FEATURE_FAST_UPDATE
	cFibElement * pFibElementToRemove = getFibElement( cType, elementPoint, bAbsolute );
	
	if ( (pFibElementToRemove == NULL) ||
			(pFibElementToRemove->pSuperiorElement == NULL)  ){
		return NULL;
	}
	if ( ! pFibElementToRemove->isRemovableElement( 'u', 0, false, bCheckVariables ) ){
		//can't remove the fib element
		return NULL;
	}//the element can be removed
	
	//check if the first element of an underobject should be removed
	for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) != NULL ){
			//no underobject
#ifdef FEATURE_FAST_UPDATE
			if ( (*actualUnderObject) == pFibElementToRemove ){
				cFibObjectCounts fibObjectCountsDelta;
#else //FEATURE_FAST_UPDATE
			if ( (*actualUnderObject)->getNumberOfElement()==
					pFibElementToRemove->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
				//Fib element to remove found
				
				if ( pFibElementToRemove->getNumberOfElements() != 1 ){
					//pFibElementToRemove has underobjects to replace it
					(*actualUnderObject) = pFibElementToRemove->getNextFibElement();
					
					if ( pFibElementToRemove->getNextFibElement() != NULL ){
						pFibElementToRemove->getNextFibElement()->pSuperiorElement = this;
					}
					if ( pFibElementToRemove->isBranch() ){
						/*a branch element with one subobject removed
						-> subtract one object point*/
						fibObjectCountsDelta.uiNumberOfObjectpoints--;
					}
				}else{//pFibElementToRemove has no subobjects
#ifdef FEATURE_FAST_UPDATE
					fibObjectCountsDelta.uiNumberOfObjectpoints--;
#endif //FEATURE_FAST_UPDATE
					fibUnderObjects.erase( actualUnderObject );
				}
#ifdef FEATURE_FAST_UPDATE
				fibObjectCountsDelta.vecNumberOfFibElements[
					cFibObjectCounts::elementTypeToIndex( pFibElementToRemove->getType() ) ]--;
				fibObjectCountsDelta.vecNumberOfFibElements[ cFibObjectCounts::ALL ]--;
				updateAllCounters( fibObjectCountsDelta );
				
				//clear values of cuted Fib element
				pFibElementToRemove->cutConnectionsTo( this );
				pFibElementToRemove->cutConnectionsTo(
					pFibElementToRemove->getNextFibElement() );
#else //FEATURE_FAST_UPDATE
				updateAllValues();
				
				//clear values of cuted Fib element
				pFibElementToRemove->cutConnections( ED_ALL );
#endif //FEATURE_FAST_UPDATE
				
				return pFibElementToRemove;
			}
		}
	}

	return pFibElementToRemove->pSuperiorElement->cutElement(  'u',
		pFibElementToRemove->getNumberOfElement() + 1 -
		pFibElementToRemove->pSuperiorElement->getNumberOfElement(),
		false, bCheckVariables );
}

#endif //SWITCH_JUST_STORE_AND_EVALUE


#ifdef FEATURE_FAST_UPDATE

/**
 * This method deletes this given Fib object with all the fib
 * elements it contains and is contained in. The memory for the fib
 * -object is freed.
 */
void cFibBranch::deleteObject(){
	
	//delete all underobjetcts
	while ( ! fibUnderObjects.empty() ){
		
		if ( fibUnderObjects.back() ){
			fibUnderObjects.back()->pSuperiorElement = NULL;
			fibUnderObjects.back()->deleteObject();
		}
		fibUnderObjects.pop_back();
	}
	//delete this Fib element
	delete this;
}
#endif //FEATURE_FAST_UPDATE

#ifndef SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method moves a Fib limb -element (cFibLimb) on the specified
 * position over iHowfar Fib elements.
 * Moving is stoped if an invalid Fib object would result (e.g. no Fib
 * -element can be moved over an Fib elements that defines a variable
 * the moved Fib element uses).
 * Moving an Fib element into an listelement will result in an
 * listelement with the moved element in everyone of it's underobjects.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib element to move
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to move
 * @param iHowfar the number of Fib elements over which the to move
 * 	Fib element should be moved; if this value is positiv the Fib
 * 	-element will be moved over Fib elements it contains else over
 * 	Fib elements it is contained in
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib object
 * @return the number of Fib Elements over which the to move Fib
 * 	-element was moved; if this value is positiv the Fib element
 * 	was moved over Fib elements it contains else over Fib elements
 * 	it is contained in
 */
intFib cFibBranch::moveLimbElement( const char cType, const unsignedIntFib
		elementPoint, const intFib iHowfar, bool bAbsolute ){
	
#ifdef FEATURE_FAST_UPDATE
	if ( ! cFibObjectCounts::isValidType( cType ) ){
		return 0;
	}
#endif //FEATURE_FAST_UPDATE
	if ( iHowfar == 0 ){
		//moved enougth
		return 0;
	}
	if ( iHowfar < 0 ){
		return moveLimbElementUp( cType, elementPoint, iHowfar * -1 , bAbsolute ) * -1;
	}
	cFibElement * pFibElementToMove = getFibElement( cType, elementPoint, bAbsolute );
	//check if the Fib element is moveble
	if ( (pFibElementToMove == NULL) ||
			( ! pFibElementToMove->isMovable() ) ){
		//can't move the Fib element
		return 0;
	}

	//( iHowfar > 0 ) -> move down -> move step by step
	//check if the superior element is the element to move
	if ( pSuperiorElement != NULL ){
#ifdef FEATURE_FAST_UPDATE
		if ( pSuperiorElement == pFibElementToMove ){
#else //FEATURE_FAST_UPDATE
		if ( (pSuperiorElement)->getNumberOfElement() ==
				pFibElementToMove->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
			/*if this element is the next element down of the to move element
			-> try to move it over this element*/
			
			/*if this element needs a variable, that the to move element defines
			-> stop moving*/
			set<cFibVariable*> setUsedVariables = getUsedVariables( ED_POSITION );
			
			for ( set<cFibVariable*>::const_iterator itrVariable = setUsedVariables.begin();
					itrVariable != setUsedVariables.end(); itrVariable++ ){
				
				if ( pFibElementToMove->isDefinedVariable( *itrVariable, ED_POSITION ) ){
					//can't move any further
					return 0;
				}
			}
			/*else move the to move element or copies of it (replace the defined
			variable for copies) into all underobjects*/
			
			/*count the existing underobjects and the underobjects for which
			the pFibElementToMove Fib element (the variables it defines) is
			needed*/
			list<cFibVariable*> liDefinedVariables = pFibElementToMove->
				getDefinedVariables( ED_POSITION );
			unsigned int uiUnderObjects = 0;
			unsigned int uiUnderObjectsWherNeeded = 0;
			for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
				
				if ( (*actualUnderObject) != NULL ){
					uiUnderObjects++;
					
					for ( list<cFibVariable*>::const_iterator itrVariable = liDefinedVariables.begin();
							itrVariable != liDefinedVariables.end(); itrVariable++ ){
						
						if ( pFibElementToMove->isUsedVariable( *itrVariable, ED_BELOW_EQUAL ) ){
							//the pFibElementToMove is needed in this underobject
							uiUnderObjectsWherNeeded++;
							break;
						}
					}
				}
			}
			if ( uiUnderObjects == 0 ){
				//nowher to move to
				return 0;
			}
			pFibElementToMove = cutElement( cType, elementPoint, bAbsolute, false );
			if ( pFibElementToMove == NULL ){
				//can't move the pFibElementToMove
				return 0;
			}
			if ( uiUnderObjectsWherNeeded == 0 ){
				//move in all underobjects
				uiUnderObjectsWherNeeded = uiUnderObjects;
			}
			//create for ever underobject a new copy of the pFibElementToMove Fib element
			list<cFibElement*> liMoveElementCopies;
			liMoveElementCopies.push_back( pFibElementToMove );
			while ( liMoveElementCopies.size() < uiUnderObjectsWherNeeded ){
				liMoveElementCopies.push_back( pFibElementToMove->copyElement() );
			}
			intFib iStepsMovedDown = 0;
			//for every underobject
			for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
					actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
				
				if ( (*actualUnderObject) == NULL ){
					continue;//no underobject to insert into
				}
				bool bVariableUsed = false;
				if (uiUnderObjectsWherNeeded != uiUnderObjects){
					for ( list<cFibVariable*>::const_iterator itrVariable = liDefinedVariables.begin();
							itrVariable != liDefinedVariables.end(); itrVariable++ ){
						
						if ( pFibElementToMove->isUsedVariable( *itrVariable, ED_BELOW_EQUAL ) ){
							bVariableUsed = true;
							break;
						}
					}
				}
				if ( (bVariableUsed) || (uiUnderObjectsWherNeeded == uiUnderObjects) ){
					//the pFibElementToMove is needed in this underobject
					//insert a copy of pFibElementToMove as the first element of ths underobject
					cFibElement * pToMoveCopy = liMoveElementCopies.back();
					liMoveElementCopies.pop_back();
					if ( pToMoveCopy == NULL ){
						//ERROR on copyElement()
						continue;
					}
					
					//replace the defined variables of pFibElementToMove with that of the copy
					list<cFibVariable*>::iterator itrDefVariable = liDefinedVariables.begin();
					
					list<cFibVariable*> liDefVariableCopy = pToMoveCopy->
						getDefinedVariables( ED_POSITION );
					list<cFibVariable*>::iterator itrDefVariableCopy = liDefVariableCopy.begin();
					
					for ( ; (itrDefVariable != liDefinedVariables.end()) &&
							(itrDefVariableCopy != liDefVariableCopy.end()) ;
							itrDefVariable++, itrDefVariableCopy++ ){
						
						(*actualUnderObject)->replaceVariable( *itrDefVariable, *itrDefVariableCopy );
					}
					//move the Fib element further down
					insertElement( pToMoveCopy, 'u', (*actualUnderObject)->getNumberOfElement() -
						getNumberOfElement() + 1, false, false );
					
					cFibElement * pNextFibElement = pToMoveCopy->getNextFibElement();
					if ( pNextFibElement != NULL ){
						iStepsMovedDown += pNextFibElement->moveLimbElement( 'u',
							pToMoveCopy->getNumberOfElement(), iHowfar - 1, true );
					}
				}
			}
			while ( ! liMoveElementCopies.empty() ){
				delete liMoveElementCopies.back();
				liMoveElementCopies.pop_back();
			}
			return iStepsMovedDown + 1;
		}
	}/*else get the underobject of the to move Fib element and call moveLimbElement from ther*/
	cFibElement * pNextFibElement = pFibElementToMove->getNextFibElement();
	if ( pNextFibElement == NULL ){
		//no next fib element -> nothing to move over
		return 0;
	}
	return pNextFibElement->moveLimbElement( 'u',
		pFibElementToMove->getNumberOfElement(), iHowfar, true );
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib object is equal to this fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib object to which this Fib object should be
 * 	equal
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the root-element of this Fib object that was checked
 * 		value: the to the key correspondending root-element of the
 * 			fibObject that was checked and which is equal to the key
 * 		root-element
 * 	(it is empty if bCheckExternalObjects == false)
 * @param mapEqualDefinedVariables the Fib elements that defines
 * 	variables and are equal;
 * 	map entries:
 * 		key: the Fib element of this Fib object that was checked
 * 		value: the to the key correspondending Fib element of the
 * 			fibObject that was checked and which sets its defined
 * 			variables to the same values as the key Fib element
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cFibBranch::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{

	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	cFibBranch * pBranchElement = (cFibBranch*)(&fibObject);
	
	//compare the underobjects
	if ( fibUnderObjects.size() != pBranchElement->fibUnderObjects.size() ){
		DEBUG_OUT_L2(<<"not equal not the same number of underobjects #fibUnderObjects="<<fibUnderObjects.size()<<"  #pBranchElement->fibUnderObjects="<<pBranchElement->fibUnderObjects.size()<<endl<<flush);
		//not the same number of underobjects
		return false;
	}
	list<cFibElement*>::const_iterator actualUnderObject1 = fibUnderObjects.begin();
	list<cFibElement*>::const_iterator actualUnderObject2 =
		pBranchElement->fibUnderObjects.begin();
	
	for ( ; actualUnderObject1 != fibUnderObjects.end();
			actualUnderObject1++, actualUnderObject2++ ){
		
		if ( ((*actualUnderObject1) == NULL) || ((*actualUnderObject2) == NULL) ){
			if ( (*actualUnderObject1) != (*actualUnderObject2) ){
				//one but not both underobjects are NULL
				return false;
			}
		}else{
			const bool bEqual = (*actualUnderObject1)->equalInternal(
				(**actualUnderObject2), mapEqualRootObjects,
				mapEqualDefinedVariables, bCheckExternalObjects );
			if ( ! bEqual ){
				//both underobjects are not equal
				return false;
			}
		}
	}
	//all is equal
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and aused in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib object to which this Fib object should be
 * 	equal
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cFibBranch::equal( const cFibElement & fibObject ) const{

	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	cFibBranch *pBranchElement = (cFibBranch*)(&fibObject);
	
	//compare the underobjects
	if ( fibUnderObjects.size() != pBranchElement->fibUnderObjects.size() ){
		DEBUG_OUT_L2(<<"not equal not the same number of underobjects #fibUnderObjects="<<fibUnderObjects.size()<<"  #pBranchElement->fibUnderObjects="<<pBranchElement->fibUnderObjects.size()<<endl<<flush);
		//not the same number of underobjects
		return false;
	}
	bool bEqual;
	list<cFibElement*>::const_iterator actualUnderObject1 = fibUnderObjects.begin();
	list<cFibElement*>::const_iterator actualUnderObject2 =
		pBranchElement->fibUnderObjects.begin();
	
	for ( ; (actualUnderObject1 != fibUnderObjects.end()) &&
			(actualUnderObject2 != pBranchElement->fibUnderObjects.end());
			actualUnderObject1++, actualUnderObject2++ ){
		
		if ( ((*actualUnderObject1) == NULL) || ((*actualUnderObject2) == NULL)){
			if ( (*actualUnderObject1) != (*actualUnderObject2) ){
				//one but not both underobjects are NULL
				return false;
			}
		}else{
			bEqual = (*actualUnderObject1)->equal( (**actualUnderObject2) );
			if ( !bEqual ){
				//both underobjects are not equal
				return false;
			}
		}
	}
	//all is equal
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * @return this method returns true if this Fib element is an
 * 	branchelement, alse false
 */
bool cFibBranch::isBranch() const{
	return true;
}

#endif //SWITCH_JUST_STORE_AND_EVALUE

//protected methods

#ifdef FEATURE_FAST_UPDATE


/**
 * This method evalues the Fib element counters of the given Fib object.
 *
 * @param pFibElement the Fib object, for which to evalue the counts of
 * 	the contained Fib elements
 * @return a vector with the counts of Fib elements of the seperate typs
 * 	in the given Fib object
 */
cFibObjectCounts cFibBranch::evalueCountersForObject(
		const cFibElement * pFibElement ) const{
	
	cFibObjectCounts countedFibObjectCounts;
	if ( pFibElement == NULL ){
		return countedFibObjectCounts;
	}
	
	/*add type count for every Fib element below or equal the given
	Fib element pFibElement, till the next branchelement, and add the
	counters of the next branchelement (if it exists)*/
	const cFibElement * pActualElement = pFibElement;
	
	while ( pActualElement != NULL ){
		
		const char cType = pActualElement->getType();
		
		switch ( cType ){
			//branchelement
			case 'l':
			case 'i':
			case 'o':
			case 'r':{
				const cFibObjectCounts vecBranchNumberOfFibElements(
					((cFibBranch*)(pActualElement))->fibObjectCounts );
				countedFibObjectCounts += vecBranchNumberOfFibElements;
				pActualElement = NULL;
			}break;
			//limbelement
			case 'a':
			case 'f':
			case 'c':
			case 'y':
			case 'v':
			case 'm':
				countedFibObjectCounts.vecNumberOfFibElements[
					cFibObjectCounts::elementTypeToIndex( cType ) ]++;
				//the underobject is the next Fib element
				pActualElement = ((cFibLimb*)(pActualElement))->pUnderObject;
			break;
			//leaf element
			case 'p':
			case 's':
				countedFibObjectCounts.vecNumberOfFibElements[
					cFibObjectCounts::elementTypeToIndex( cType ) ]++;
				
				pActualElement = NULL;
			break;
		}
	}
	countedFibObjectCounts.evalueAllFibElements();
	
	return countedFibObjectCounts;
}


/**
 * This method updates the Fib element counters of all branchelements in
 * this branchelement.
 *
 * @return the numbers with which the Fib element counters wher updated
 */
cFibObjectCounts cFibBranch::updateCounters(){
	
	cFibObjectCounts newFibObjectCounts;
	
	//add number of Fib elements of the typs of all underobjects
	for ( list<cFibElement *>::const_iterator
			itrUnderobject = fibUnderObjects.begin();
			itrUnderobject != fibUnderObjects.end(); itrUnderobject++ ){
		
		if ( (*itrUnderobject) != NULL ){
			newFibObjectCounts +=
				evalueCountersForObject( *itrUnderobject );
		}
	}
	newFibObjectCounts.vecNumberOfFibElements[
		cFibObjectCounts::elementTypeToIndex( getType() ) ]++;
	newFibObjectCounts.uiNumberOfObjectpoints +=
		fibUnderObjects.size();
	newFibObjectCounts.evalueAllFibElements();
	
	//evalue the delta
	cFibObjectCounts deltaFibObjectCounts;
	deltaFibObjectCounts = newFibObjectCounts;
	deltaFibObjectCounts -= fibObjectCounts;
	
	//set the counters of this branchelement toi the new values
	fibObjectCounts = newFibObjectCounts;
	
	return deltaFibObjectCounts;
}


/**
 * This method updates the Fib element counters of all branchelements in
 * this or higher this branchelement.
 *
 * @param deltaFibObjectCounts a vector with the Fib elements
 * 	counts, with which to update all branchelements counters in this
 * 	or higher this branchelement
 */
void cFibBranch::updateAllCounters(
	const cFibObjectCounts & deltaFibObjectCounts ){

	//update every branchelement
	cFibElement * pActualElement = this;
	
	while (pActualElement != NULL){
		if ( pActualElement->isBranch() ){
			
			((cFibBranch*)(pActualElement))->fibObjectCounts +=
				deltaFibObjectCounts;
		}
		pActualElement = pActualElement->pSuperiorElement;
	}
}


/**
 * This method updates the Fib element counters of all branchelements in
 * this or higher this branchelement.
 */
void cFibBranch::updateAllCounters(){
	
	//update this branchelement
	const cFibObjectCounts deltaFibObjectCounts =
		updateCounters();
	
	//update every superior branchelement
	cFibElement * pActualElement = pSuperiorElement;
	
	while (pActualElement != NULL){
		if ( pActualElement->isBranch() ){
			
			((cFibBranch*)(pActualElement))->fibObjectCounts +=
				deltaFibObjectCounts;
		}
		pActualElement = pActualElement->pSuperiorElement;
	}
}

#endif //FEATURE_FAST_UPDATE

#ifndef FEATURE_NO_REGISTER_NEW_FIB_

/**
 * With this method a new Fib element in the Fib Object is registert
 * by the other Fib elements in the Fib Object.
 *
 * @param newFibElement the new Fib element to register
 * @param uINumberOfFibElement the number of the new Fib element in the
 * 	order of all Fib Elements in the Fib object
 * @param bDirectionUp the direction in which the registration of the
 * 	new Fib element is performed in the Fib object tree;
 * 	from the position on which the new Fib Element is added the
 * 	method is called for both directions
 * @return true if the registration was successfull, else false
 */
bool cFibBranch::registerNewFibElement( cFibElement *newFibElement,
		unsignedIntFib uINumberOfFibElement, bool bDirectionUp ){
	
	if ( newFibElement == NULL ){
		//no Fib element to register
		return false;
	}
	
	if ( bDirectionUp ){
		/*register the new Fib element in all Fib element in direction up*/
		
		if ( pSuperiorElement != NULL ){
			pSuperiorElement->registerNewFibElement( newFibElement,
					uINumberOfFibElement, true );
		}
		
		/*register the new Fib element in all underobjects, wher it isn't
		registered yet*/
		list<cFibElement*>::iterator nextUnderObject;
		for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
			
			if ( (*actualUnderObject) != NULL ){
				
				nextUnderObject = actualUnderObject;
				nextUnderObject++;
				
				if ( (uINumberOfFibElement < (*actualUnderObject)->getNumberOfElement()) ||
						( (nextUnderObject != fibUnderObjects.end()) &&
							((*nextUnderObject)->getNumberOfElement() <= uINumberOfFibElement)) ){
					/*the number of the new Fib element in the order of
					Fib elements is not betwean the number of the actualUnderObject
					and the number of the nextUnderObject
					-> the Fib element wasn't added in the actualUnderObject*/
					(*actualUnderObject)->registerNewFibElement( newFibElement,
						uINumberOfFibElement, false );
				}
			}
		}
		
	}else{
		//register in direction below
		
		//register the new Fib element in all underobjects
		for (list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++){

			if ( (*actualUnderObject) != NULL ){
				(*actualUnderObject)->registerNewFibElement( newFibElement,
					uINumberOfFibElement, false );
			}
		}
	}
	
	//update the position of this Fib element in order of Fib elements
	if ( this->uINumberOfFibElement >= uINumberOfFibElement ){
		/*add 1 to the number of this fib element in the order of
		Fib elements, because the new Fib element was added in
		order of Fib elements befor it*/
		this->uINumberOfFibElement++;
	}
	//update pPreviousFibElement
	if ( this->uINumberOfFibElement == uINumberOfFibElement+1 ){
		//this Fib element is the next Fib element to the new Fib element
		pPreviousFibElement = newFibElement;
	}
	
	//update pNextFibElement
	if ( this->uINumberOfFibElement == uINumberOfFibElement-1 ){
		//the new Fib element is the next Fib element to this Fib element
		pNextFibElement = newFibElement;
	}
	return true;
}


/**
 * With this method a new part Fib object in the Fib Object is
 * registert by the other Fib elements in the Fib Object.
 *
 * @param newFibObject the new part Fib object to register
 * @param uILowerNumberOfFibElements the number of the Fib element in the
 * 	new part Fib object with the lowest number in the order of all
 * 	Fib Elements in the entire Fib object
 * @param uIUpperNumberOfFibElements the number of the Fib element in the
 * 	new part Fib object with the highest number in the order of all
 * 	Fib Elements in the entire Fib object
 * @param bDirectionUp the direction in which the registration of the
 * 	new part Fib object is performed in the Fib object tree;
 * @return true if the registration was successfull, else false
 */
bool cFibBranch::registerNewFibObject( cFibElement *newFibObject,
		unsignedIntFib uILowerNumberOfFibElements,
		unsignedIntFib uIUpperNumberOfFibElements, bool bDirectionUp ){

	if ( newFibObject == NULL ){
		//no Fib element to register
		return false;
	}
	if ( uILowerNumberOfFibElements < uIUpperNumberOfFibElements ){
		/*invalid bounderies for numbers of Fib elements in the order of
		Fib elements*/
		return false;
	}

	if ( bDirectionUp ){
		/*register the new Fib element in all Fib element in direction up*/
		
		if ( pSuperiorElement != NULL ){
			pSuperiorElement->registerNewFibObject( newFibObject,
					uILowerNumberOfFibElements, uIUpperNumberOfFibElements, true );
		}
		
		/*register the new Fib element in all underobjects, wher it isn't
		registered yet*/
		list<cFibElement*>::iterator nextUnderObject;
		for ( list<cFibElement*>::iterator actualUnderObject=fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++){
			
			if ( (*actualUnderObject) != NULL ){
			
				nextUnderObject = actualUnderObject;
				nextUnderObject++;
				
				if ( (uILowerNumberOfFibElements<(*actualUnderObject)->getNumberOfElement()) ||
						( (nextUnderObject != fibUnderObjects.end()) &&
							((*nextUnderObject)->getNumberOfElement() <= uILowerNumberOfFibElements)) ){
					/*the number of the new Fib element in the order of
					Fib elements is not betwean the number of the actualUnderObject
					and the number of the nextUnderObject
					-> the Fib element wasn't added in the actualUnderObject*/
					(*actualUnderObject)->registerNewFibObject( newFibObject,
						uILowerNumberOfFibElements, uIUpperNumberOfFibElements, false );
				}
			}
		}
		
	}else{
		//register in direction below
		
		//register the new Fib element in all underobjects
		for (list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
				actualUnderObject != fibUnderObjects.end(); actualUnderObject++){

			if ( (*actualUnderObject) != NULL ){
				(*actualUnderObject)->registerNewFibObject( newFibObject,
					uILowerNumberOfFibElements, uIUpperNumberOfFibElements, false );
			}
		}
	}
	
	//update the position of this Fib element in order of Fib elements
	if ( this->uINumberOfFibElement >= uINumberOfFibElement ){
		/*add 1 to the number of this fib element in the order of
		Fib elements, because the new Fib element was added in
		order of Fib elements befor it*/
		this->uINumberOfFibElement = this->uINumberOfFibElement+
			( uIUpperNumberOfFibElements - uILowerNumberOfFibElements + 1);
	}
	bool bReturnValue = true;
	
	//update pPreviousFibElement
	if ( this->uINumberOfFibElement == uIUpperNumberOfFibElements + 1 ){
		/*the last Fib element in the new Fib Object is the previous
		Fib element to this Fib element*/
		cFibElement *lastFibElement = newFibObject;
		//find last Fib element
		while ( lastFibElement->getNumberOfElement() != uIUpperNumberOfFibElements ){
		
			if ( lastFibElement->pNextFibElement == NULL ){
				//error: last Fib element has wrong number
				bReturnValue = false;
				break;
			}
			lastFibElement = lastFibElement->pNextFibElement;
		}
		pPreviousFibElement = lastFibElement;
	}
	
	//update pNextFibElement
	if ( this->uINumberOfFibElement == uILowerNumberOfFibElements - 1 ){
		/*the first Fib element in the new Fib Object is the next
		Fib element to this Fib element*/
		pNextFibElement = newFibObject;
	}
	return bReturnValue;
}

#endif //FEATURE_NO_REGISTER_NEW_FIB_



#ifdef FEATURE_FAST_UPDATE

/**
 * This method cuts the connections of this Fib element to the
 * given Fib element.
 *
 * @param pFibElement the Fib element to which to cut the connection
 */
void cFibBranch::cutConnectionsTo( const cFibElement * pFibElement ){
	
	cFibElement::cutConnectionsTo( pFibElement );
	//check the underobjects
	list<cFibElement*>::iterator itrActualUnderObject = fibUnderObjects.begin();
	for ( ; itrActualUnderObject != fibUnderObjects.end(); itrActualUnderObject++ ){
		
		if ( (*itrActualUnderObject) == pFibElement ){
			/*cut connection to the actual underobject;
			it is (itrActualUnderObject != fibUnderObjects.end())*/
			break;
		}
	}
	if ( itrActualUnderObject != fibUnderObjects.end() ){
		//cut connection to the actual underobject
		fibUnderObjects.erase( itrActualUnderObject );
		updateAllCounters();
	}
}


/**
 * This method returns the number of the next connected object point
 * in the order of connected object points that conntains the given
 * Fib element pLastFibElement.
 *
 * @param pLastFibElement a point to the Fib elements for which the
 * 	connected object point is to return
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @return the number of the next connected object point for the given
 * 	Fib element
 */
unsignedIntFib cFibBranch::getNumberOfObjectPointUp(
		const cFibElement * pLastFibElement ) const{
	
	unsignedIntFib uiNumberOfObjectPoint = 1;

	for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){
		/*count the underobjectpoints in all underobjects befor the
		underobject for uINumberOfStartFibElement*/
		
		if ( (*actualUnderObject) == NULL ){
			continue;
		}
		
		if ( (*actualUnderObject) == pLastFibElement ){
			//actualUnderObject contains the fib element
			break;
		}
		uiNumberOfObjectPoint += (*actualUnderObject)->getNumberOfObjectPoints();
		uiNumberOfObjectPoint++;//add the object point for the actualUnderObject
	}
	
	if ( pSuperiorElement != NULL ){
		uiNumberOfObjectPoint += pSuperiorElement->getNumberOfObjectPointUp( this );
	}
	return uiNumberOfObjectPoint;
}

#ifndef SWITCH_JUST_STORE_AND_EVALUE

/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param pLastFibElement a point to the Fib elements for which the
 * 	connected object points are to return
 * @param pFirstFibElement the Fib element for which this method was
 * 	called ( the reference Fib element)
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibBranch::elementPointToObjectPointsUp(
		const cFibElement * pLastFibElement,
		const cFibElement * pFirstFibElement ) const{

	unsignedIntFib uiNumberOfObjectPoint = 1;

	for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){
		/*count the underobjectpoints in all underobjects befor the
		underobject for uINumberOfStartFibElement*/
		
		if ( (*actualUnderObject) == NULL ){
			continue;
		}
		
		if ( (*actualUnderObject) == pLastFibElement ){
			//actualUnderObject contains the fib element
			break;
		}
		uiNumberOfObjectPoint += (*actualUnderObject)->getNumberOfObjectPoints();
		uiNumberOfObjectPoint++;//add the object point for the actualUnderObject
	}
	
	list<unsignedIntFib> liObjectPoints;
	if ( this != pFirstFibElement ){
		//serach for more objectpoints
		if ( ( pSuperiorElement != NULL ) && ( this != pFirstFibElement ) ){
			liObjectPoints = pSuperiorElement->elementPointToObjectPointsUp( this, pFirstFibElement );
		}
		if ( liObjectPoints.empty() ){
			//this is the first objectpoint found
			liObjectPoints.push_back( uiNumberOfObjectPoint );
			return liObjectPoints;
		}//else some objectpoints wher found allready
		/*the objectpoint in this branchelement, is the relativ objectpoint of
		this branch plus the last founded objectpoint*/
		liObjectPoints.push_back(
			uiNumberOfObjectPoint + liObjectPoints.back() );
		return liObjectPoints;
	}//else search done
	liObjectPoints.push_back( uiNumberOfObjectPoint );
	return liObjectPoints;
}

#endif //SWITCH_JUST_STORE_AND_EVALUE

#else //FEATURE_FAST_UPDATE


/**
 * This method cuts the connections of this Fib element to other
 * Fib elements.
 *
 * @param direction the direction into which the connections are to be
 * 	cutted
 * 	ED_HIGHER, ED_HIGHER_EQUAL, ED_ALL: will cut the conection to
 * 		superior and previous Fib elements
 * 	ED_BELOW, ED_BELOW_EQUAL, ED_ALL: will cut the conection to
 * 		next- Fib element and the underobjects
 */
void cFibBranch::cutConnections( edDirection direction ){
	
	cFibElement::cutConnections( direction );
	fibUnderObjects.clear();
}


/**
 * This method updates the values/ properties off all Fib elements in
 * this Fib object beginning with this Fib element.
 *
 * @param previosFibElement the prvios Fib element to this Fib element
 * 	in the order of Fib elements; if it is NULL ther is no previos
 * 	Fib element to this
 * @return a pointer to the last evalued Fib element;
 * 	if NULL an error has occured
 */
cFibElement* cFibBranch::updateValues( cFibElement *previosFibElement,
		cFibElement * pNextArm ){

	cFibElement * lastFibElementUpdated = NULL;
	
	if ( ! fibUnderObjects.empty() ){
		pNextFibElement = fibUnderObjects.front();
	}else{
		//no underobjects
		pNextFibElement = pNextArm;
	}
	//this Fib element is the superior of all it's underobjects
	for ( list<cFibElement*>::iterator itrActualUnderObject = fibUnderObjects.begin();
			itrActualUnderObject != fibUnderObjects.end(); itrActualUnderObject++){
		
		if ( (*itrActualUnderObject) != NULL ){
			
			(*itrActualUnderObject)->pSuperiorElement = this;
		}
	}
	
	lastFibElementUpdated = cFibElement::updateValues( previosFibElement, pNextArm );
	if ( lastFibElementUpdated == NULL ){
		//something gone wrong while updating
		return NULL;
	}
	
	//update all underobjects if existing
	list<cFibElement*>::iterator itrNextUnderObject;
	
	for (list<cFibElement*>::iterator itrActualUnderObject = fibUnderObjects.begin();
			itrActualUnderObject != fibUnderObjects.end(); itrActualUnderObject++ ){

		if ( (*itrActualUnderObject) != NULL ){
		
			//get the next underobject (pNextArm)
			itrNextUnderObject = itrActualUnderObject;
			itrNextUnderObject++;
			while ( ((*itrNextUnderObject) == NULL) &&
					(itrNextUnderObject != fibUnderObjects.end()) ){
				itrNextUnderObject++;
			}
			
			if ( itrNextUnderObject != fibUnderObjects.end() ){
				lastFibElementUpdated =
					(*itrActualUnderObject)->updateValues( lastFibElementUpdated, (*itrNextUnderObject) );
			}else{
				lastFibElementUpdated =
					(*itrActualUnderObject)->updateValues( lastFibElementUpdated, pNextArm );
			}
			
			if ( lastFibElementUpdated == NULL ){
				//something gone wrong while updating
				return NULL;
			}
		}
	}
	return lastFibElementUpdated;
}


/**
 * This method returns the number of the next connected object point
 * in the order of connected object points that conntains this Fib
 * -element.
 *
 * @param uINumberOfStartFibElement the number, in the order of all
 * 	Fib elements, of the Fib element for which the connected object
 * 	point is to return
 * @see getNumberOfObjectPoint
 * @see getNumberOfObjectPoints()
 * @return the number of the next connected object point for this Fib 
 * 	-element
 */
unsignedIntFib cFibBranch::getNumberOfObjectPoint(
		unsignedIntFib uINumberOfStartFibElement ) const{
	
	unsignedIntFib uiNumberOfObjectPoint = 1;

	list<cFibElement*>::const_iterator nextUnderObject;
	
	for ( list<cFibElement*>::const_iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++){
		/*count the underobjectpoints in all underobjects befor the
		underobject for uINumberOfStartFibElement*/
		
		if ( (*actualUnderObject) == NULL ){
			continue;
		}
		
		nextUnderObject = actualUnderObject;
		nextUnderObject++;
		if ( nextUnderObject == fibUnderObjects.end() ){
			//actualUnderObject is the last underobject -> done
			break;
		}
		if ( uINumberOfStartFibElement < (*nextUnderObject)->getNumberOfElement() ){
			//actualUnderObject branch is not befor uINumberOfStartFibElement -> done
			break;
		}
		uiNumberOfObjectPoint += (*actualUnderObject)->getNumberOfObjectPoints();
		uiNumberOfObjectPoint++;//add the object point for the actualUnderObject
	}
	
	if ( pSuperiorElement != NULL ){
		uiNumberOfObjectPoint += pSuperiorElement->getNumberOfObjectPoint( uINumberOfStartFibElement );
	}
	return uiNumberOfObjectPoint;
}


/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param referenceFibObject the Fib element from which this method was
 * 	called
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibBranch::elementPointToObjectPoints(
		const cFibElement * referenceFibObject,
		const unsignedIntFib uiLastObjectPoint ) const{

	DEBUG_OUT_L2(<<"cFibBranch::elementPointToObjectPoints("<<flush<<referenceFibObject<<", "<<uiLastObjectPoint<<") for "<<getType()<<" started"<<endl<<flush);
	
	list<cFibElement*>::const_iterator nextUnderObject;
	list<cFibElement*>::const_iterator actualUnderObject;
	
	unsignedIntFib uiLastObjectPointActual = uiLastObjectPoint;
	
	DEBUG_OUT_L2(<<"searching for reference objectpoint actual objectpoint: "<<flush);
	for ( actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		/*count the underobjectpoints in all underobjects befor the
		underobject for uINumberOfStartFibElement*/
		
		if ( (*actualUnderObject) == NULL ){
			DEBUG_OUT_L2(<<endl<<"actualUnderObject is NULL"<<endl<<flush);
			continue;
		}
		
		nextUnderObject = actualUnderObject;
		nextUnderObject++;
		if ( nextUnderObject == fibUnderObjects.end() ){
			//actualUnderObject is the last underobject -> done
			DEBUG_OUT_L2(<<endl<<"end of underobject list found"<<endl<<flush);
			break;
		}
		if ( referenceFibObject->getNumberOfElement() <
				(*nextUnderObject)->getNumberOfElement() ){
			//actualUnderObject branch is not befor referenceFibObject -> done
			DEBUG_OUT_L2(<<endl<<"reference fib objects found"<<endl<<flush);
			break;
		}
		uiLastObjectPointActual += (*actualUnderObject)->getNumberOfObjectPoints();
		uiLastObjectPointActual++;//add the object point for the underobject
//		DEBUG_OUT_L2(<<uiLastObjectPointActual<<"; "<<flush);
	}
	uiLastObjectPointActual++;//add the object point for actualUnderObject
	
	list<unsignedIntFib> liFoundedObjectPoints;
	
	DEBUG_OUT_L2(<<"store object points "<<uiLastObjectPointActual<<endl<<flush);
	if ( ((*actualUnderObject) != NULL) && (this != referenceFibObject) ){
		DEBUG_OUT_L2(<<"get objectpoints of underobject "<<*actualUnderObject<<endl<<flush);
		liFoundedObjectPoints = (*actualUnderObject)->elementPointToObjectPoints(
			referenceFibObject, uiLastObjectPointActual );
		
		DEBUG_OUT_L2(<<"add objectpoints of this branchelement "<<endl<<flush);
		liFoundedObjectPoints.push_front( uiLastObjectPointActual );
	}//else this==referenceFibObject or no pSuperiorElement -> all object points found
	
	DEBUG_OUT_L2(<<"cFibBranch::elementPointToObjectPoints("<<referenceFibObject<<", "<<uiLastObjectPoint<<") done"<<endl<<flush);
	return liFoundedObjectPoints;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method sets the each variable, which is defined over an leaf,
 * to an uniqe integer number greater than the given number
 * uiLastVariableNumber. While storing this number can be stored to
 * identify the variable.
 *
 * @param uiLastVariableNumber the number which was last use, this
 * 	means also is the greatest used, in this limb.
 * @return the number which was last use, this
 * 	means also is the greatest used, in this limb
 * 	from the method
 */
unsignedIntFib cFibBranch::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	unsignedIntFib uiBiggestUsedNumber = uiLastVariableNumber;
	
	for ( list<cFibElement*>::iterator actualUnderObject = fibUnderObjects.begin();
			actualUnderObject != fibUnderObjects.end(); actualUnderObject++ ){
		
		if ( (*actualUnderObject) == NULL ){
			continue;
		}
		unsignedIntFib uiActualBiggestUsedNumber = (*actualUnderObject)->
			enumerateVariablesForStoring( uiLastVariableNumber );

		uiBiggestUsedNumber = max( uiBiggestUsedNumber, uiActualBiggestUsedNumber );
	}
	return uiBiggestUsedNumber;
}









