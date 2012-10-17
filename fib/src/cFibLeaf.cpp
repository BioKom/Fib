/**
 * @class cFibLeaf
 * file name: cFibLeaf.cpp
 * @author Betti Oesterholz
 * @date 26.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib-element, which are leafs.
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
 * This file contains the basisclass of all Fib-elements, which are
 * leafs. Leafes can have no underobject.
 * It's not possible to create instances from this class.
 *
 * If the structur of the Fib-object is changed just set the underobjects
 * and call updateAllValues() from a position wher the highest Fib-element
 * can be reached. The updateAllValues()  method will make the conections.
 * If you remove conections you have to be more carefull.
 */
/*
History:
26.11.2009  Oesterholz  created
06.01.2010  Oesterholz  getAllFibElements() uses now getAllFibElementsFromPosition()
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
*/

//TODO weg
//#define DEBUG


#include "cFibLeaf.h"

#include <utility>


using namespace fib;

using namespace std;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorElement the Fib-Element in which this Fib-element
 * 	is the underobject
 */
cFibLeaf::cFibLeaf( cFibElement * pInSuperiorElement ):
		cFibElement( pInSuperiorElement ){
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorElement the Fib-Element in which this Fib-element
 * 	is the underobject
 * @param pInPreviousFibElement the Fib-Element which stands in th order
 * 	of Fib-elements befor this Fib-element
 * @param pInNextFibElement the Fib-Element which stands in th order
 * 	of Fib-elements behind this Fib-element
 */
cFibLeaf::cFibLeaf( cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement,
		cFibElement * pInNextFibElement ):
		cFibElement( pInSuperiorElement, pInPreviousFibElement, pInNextFibElement ){
	
	//register this new Fib-element
	if ( pPreviousFibElement != NULL ){
		pPreviousFibElement->registerNewFibElement( this, uINumberOfFibElement, true );
	}
}
#endif //FEATURE_SIMPLE_CONSTRUCTOR


/**
 * copyconstructor
 * This copyconstructor constructs a copy of this Fib-Element.
 * It dosn't copy other Fib-elements than this, even if ther are in this
 * Fib-element.
 *
 * @param fibLeafElement the Fib-element to copy
 */
cFibLeaf::cFibLeaf( const cFibLeaf &fibLeafElement ):
		cFibElement( fibLeafElement ){
	//nothing to do
}


/**
 * This method checks, if this Fib-element is an valid Fib-element.
 *
 * @return true if this Fib-element is an valid Fib-element, else false
 */
bool cFibLeaf::isValidFibElement() const{
	
#ifndef FEATURE_FAST_UPDATE
	if ( ( pSuperiorElement != NULL ) && (pPreviousFibElement == NULL) ){
		//if this is not a topmost Fib-element, it needs a previos element
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	//leafs are the only fib elements that don't need a next element to be correct
	//everything is ok
	return true;
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method returns the next Fib-element in the order of Fib-elements.
 *
 * @return a pointer to the next Fib-element in the order of Fib-elements
 * 	or the NULL pointer if non such exists
 */
cFibElement * cFibLeaf::getNextFibElement(){
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this );
	}//else
	return NULL;
}


/**
 * This method returns the next Fib-element in the order of
 * Fib-elements which is above the given fib element.
 * This method is used, if the method @see getNextFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getNextFibElement()
 * @param pLastFibElement the Fib-element relativ to which the next
 * 	Fib-element should lay
 * @return a pointer to the next Fib-element in the order of Fib-elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibLeaf::getNextFibElementUp( const cFibElement * pLastFibElement ){
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this );
	}//else
	return NULL;
}


/**
 * This method returns the next Fib-element in the order of 
 * Fib-elements with the given type cTyp.
 *
 * @param cType the type of the Fib-element to return
 * @return a pointer to the next Fib-element in the order of 
 * 	Fib-elements with the given type or the NULL pointer if non such
 * 	exists
 */
cFibElement * cFibLeaf::getNextFibElement( char cType ){
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this, cType );
	}//else
	return NULL;
}


/**
 * This method returns the next Fib-element in the order of
 * Fib-elements which is above the given fib element.
 * This method is used, if the method @see getNextFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getNextFibElement()
 * @param pLastFibElement the Fib-element relativ to which the next
 * 	Fib-element should lay
 * @param cType the type of the Fib-element to return
 * @return a pointer to the next Fib-element in the order of Fib-elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibLeaf::getNextFibElementUp( const cFibElement * pLastFibElement,
		char cType ){
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this, cType );
	}//else
	return NULL;
}


/**
 * This method returns the lNumber'th Fib-element in the order of
 * Fib-elements with the given type cTyp.
 *
 * @param lNumber the number of the Fib-Element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return a pointer to the lNumber'th Fib-element in the order of
 * 	Fib-elements or the NULL pointer if non such exists
 */
cFibElement * cFibLeaf::getConstFibElement( longFib lNumber,
		bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibLeaf::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	if ( lNumber == 0 ){
		//this is the correct Fib-element
		DEBUG_OUT_L2(<<"cFibLeaf::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done returning this"<<endl<<flush);
		return const_cast<cFibLeaf*>( this );
	}//else
	if ( bAbsolute ){
		return getMasterRoot()->getConstFibElement( lNumber );
	}//else lNumber is an relative value
	if ( lNumber == 1 ){
		//this is the correct Fib-element
		DEBUG_OUT_L2(<<"cFibLeaf::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done returning this"<<endl<<flush);
		return const_cast<cFibLeaf*>( this );
	}//else
	
	if ( pSuperiorElement ){
		if ( 0 < lNumber ){
			//remove this Fib-element from the count
			lNumber--;
		}
		DEBUG_OUT_L2(<<"calling cFibLeaf::getConstFibElementUp( this="<<this<<", lNumber="<<lNumber<<" )"<<endl<<flush);
		return pSuperiorElement->getConstFibElementUp( this, lNumber );
	}
	return NULL;//no such Fib-element;
}


/**
 * This method returns the lNumber'th Fib-element in the order of
 * Fib-elements which is above the given Fib-element.
 * This method is used, if the method @see getConstFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getConstFibElementUp()
 * @param pLastFibElement the Fib-element relativ to which the next
 * 	Fib-element should lay
 * @param lNumber the number of the Fib-Element to return
 * @return a pointer to the next Fib-element in the order of Fib-elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibLeaf::getConstFibElementUp( const cFibElement * pLastFibElement,
		longFib lNumber ) const{
	
	if ( lNumber == -1 ){
		//this is the correct Fib-element
		return const_cast<cFibLeaf*>( this );
	}//else
	//no such Fib-element under this branch -> search higher
	if ( pSuperiorElement ){
		//remove this Fib-element from the count
		if ( lNumber < 0 ){
			lNumber++;
		}
		return pSuperiorElement->getConstFibElementUp( this, lNumber );
	}//else
	
	return NULL;
}


/**
 * This method returns the lNumber'th Fib-element in the order of
 * Fib-elements of the given type cTyp with the given type cTyp.
 *
 * @param cType the type of the Fib-element to return
 * @param lNumber the number of the Fib-element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return a pointer to the lNumber'th Fib-element in the order of
 * 	Fib-elements with the given type or the NULL pointer if non such
 * 	exists
 */
cFibElement * cFibLeaf::getConstFibElement( char cType, longFib lNumber,
		bool bAbsolute ) const{
	
	if ( lNumber == 0 ){
		//this is the correct Fib-element
		return const_cast<cFibLeaf*>( this );
	}//else
	if ( bAbsolute ){
		return getMasterRoot()->getConstFibElement( cType, lNumber );
	}//else lNumber is an relative value
	if ( cType == 'u' ){
		//type is irrelevant respectivly return of every type
		return getConstFibElement( lNumber );
	}
	if ( (lNumber == 1) && ( getType() == cType ) ){
		//this is the correct Fib-element
		return const_cast<cFibLeaf*>( this );
	}//else
	
	if ( pSuperiorElement ){
		if ( ( getType() == cType ) && ( 0 < lNumber ) ){
			lNumber--;//remove this Fib-element from the count
		}
		return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
	}
	return NULL;//no such Fib-element;
}


/**
 * This method returns the lNumber'th Fib-element in the order of
 * Fib-elements of the given type cTyp with the given type cTyp which is
 * above the given Fib-element.
 * This method is used, if the method @see getConstFibElement() reaches
 * an leaf in the object tree.
 *
 * @see getConstFibElementUp()
 * @param pLastFibElement the Fib-element relativ to which the next
 * 	Fib-element should lay
 * @param cType the type of the Fib-element to return
 * @param lNumber the number of the Fib-Element to return
 * @return a pointer to the next Fib-element in the order of Fib-elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibLeaf::getConstFibElementUp( const cFibElement * pLastFibElement,
		char cType, longFib lNumber ) const{
	

	if ( (lNumber == -1) && ( getType() == cType ) ){
		//this is the correct Fib-element
		return const_cast<cFibLeaf*>( this );
	}//else
	//no such Fib-element under this branch -> search higher
	if ( pSuperiorElement ){
		if ( ( getType() == cType ) && ( lNumber < 0 ) ){
			lNumber++;//remove this Fib-element from the count
		}
		return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
	}//else
	
	return NULL;
}

#endif //FEATURE_FAST_UPDATE

/**
 * This method returns a number of (lNumberOfMaxReturnedElements)
 * Fib-elements beginning from the actual Fib-element in the
 * given direction of the given type cType.
 * The actual Fib-element will never be included in the returned list.
 *
 * @param cType the type of the Fib-elements to return;
 * 	'w' stands for wrong/ not correct Fib-elements
 * @param direction the direction, beginning from the reference 
 * 	Fib-element, in which the to return Fib-elements should stand
 * @param lNumberOfMaxReturnedElements the maximal number of 
 * 	Fib-elements to return
 * @return a list with the pointers to the to returning Fib-elements
 */
list<cFibElement*> cFibLeaf::getAllFibElementsFromPosition(
		char cType, edDirection direction,
		unsignedLongFib lNumberOfMaxReturnedElements ){
	

	/*if the direction is ED_ALL, ED_BELOW or ED_BELOW_EQUAL no
	Fib-elements to add from below this to the list*/
	
	list<cFibElement*> liFoundedElements;
	
	//just add Fib-elements from higher positions
	if (  (direction == ED_ALL) || (direction == ED_HIGHER) ||
			(direction == ED_HIGHER_EQUAL) ){
	
		if ( pSuperiorElement != NULL ){
	
			/*if the direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL add
			lNumberOfMaxReturnedElements Fib-elements higher to the list*/
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
				liFoundedElements = pSuperiorElement->getAllFibElementsFromPosition(
					cType, ED_HIGHER, lNumberOfMaxReturnedElements );
			}
			if ( (cType == 'u') || (pSuperiorElement->getType() == cType)  ||
					( (cType == 'w') && ( ! (pSuperiorElement->isValidFibElement()) ) )){
				//previous element has the correct type -> it will be added
				liFoundedElements.push_front( pSuperiorElement );
			}
		}
	}
	//all elements to give back are found
	return liFoundedElements;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib-element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param variable the variable to check if it is used
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @return true if the variable is used, else false
 */
bool cFibLeaf::isUsedVariable( const cFibVariable *variable,
		edDirection direction ) const{
	
	if ( direction == ED_POSITION ){
		//child classes should check this branch seperatly
		return false;
	}
	
	if ( ( direction == ED_BELOW ) || (direction == ED_BELOW_EQUAL) ){
		//no elements to check in the direction
		return false;
	}//direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL
	
	if ( pSuperiorElement != NULL ){
		//no elements to check in the direction
		return pSuperiorElement->isUsedVariable( variable , ED_HIGHER_EQUAL );
	}//else no elements to check in the direction
	return false;
}


/**
 * This method checks if the given variable is used in the given
 * direction from this Fib-element.
 *
 * @see cFibVariable
 * @see isDefinedVariable()
 * @param variable the variable to check if it is used
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @return true if the variable is used, else false
 */
set<cFibVariable*> cFibLeaf::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( direction == ED_POSITION ){
		//child classes should check this branch seperatly
		return setUsedVariables;
	}
	
	if ( ( direction == ED_BELOW ) || (direction == ED_BELOW_EQUAL) ){
		//no elements to check in the direction
		return setUsedVariables;
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
 * direction from this Fib-element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param variable the variable to check if it is defined
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return true if the variable is used, else false
 */
bool cFibLeaf::isDefinedVariableInternal( const cFibVariable *variable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( direction == ED_POSITION ){
		return false;
	}
	
	if ( (direction == ED_BELOW) || (direction == ED_BELOW_EQUAL) ){
		//else no elements to check in the direction
		return false;
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
 * this Fib-element.
 * This is for intern use to get the correct data from
 * getDefinedVariables() without pCallingFibElement.
 *
 * @see cFibVariable
 * @see getUsedVariables()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib-element, in which the
 * 	variable should be used; standardvalue is ED_POSITION so yust
 * 	this Fib-element will be checked
 * @param pCallingFibElement the Fib-Element which called this method
 * @return the set with all variables used in the given direction from
 * 	this Fib-element
 */
list<cFibVariable*> cFibLeaf::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){
	
	if ( direction == ED_POSITION ){
		//child classes should check this branch seperatly
		return list<cFibVariable*>();
	}
	
	if ( ( direction == ED_BELOW ) || (direction == ED_BELOW_EQUAL) ){
		//no elements to check in the direction
		return list<cFibVariable*>();
	}//direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL
	
	if ( pSuperiorElement != NULL ){
		//elements to check in the direction
		return pSuperiorElement->getDefinedVariablesInternal( ED_HIGHER_EQUAL, this );
		
	}//else no elements to check in the direction
	return list<cFibVariable*>();
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method returns the number of this Fib-element in the order of
 * Fib-Elements or order of Fib-Elements of the same type if bOfType
 * is true.
 *
 * @see getNumberOfElements()
 * @param bOfType if true the returned number is the number the order
 * 	of Fib-elements of the same type as this Fib-Element, else in
 * 	the order of all Fib-elements
 * @return the number of this Fib-element in the order of fib
 * 	-Elements or order of Fib-Elements of the same type if bOfType
 * 	is true
 */
unsignedIntFib cFibLeaf::getNumberOfElement( bool bOfType ) const{
	
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
 * Basicly it counts the number of Fib-elements of the given type befor
 * the given Fib-element pLastFibElement .
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @param pLastFibElement a pointer to the Fib-element which called this
 * 	method last
 * @param cType the type of the Fib-elements, for which to evalue the count,
 * 	if 'u' Fib-elements of all typs are counted
 * @return the number of Fib-elements of the given type cType befor the
 * 	given Fib-element pLastFibElement
 */
unsignedIntFib cFibLeaf::getNumberOfElementUp(
		const cFibElement * pLastFibElement, const char cType ) const{
	
	if ( pSuperiorElement ){
		if ( ( cType == 'u' ) || ( getType() == cType ) ){
			return pSuperiorElement->getNumberOfElementUp( this, cType ) + 1;
		}
		return pSuperiorElement->getNumberOfElementUp( this, cType );
	}//else no superior done counting
	if ( ( cType == 'u' ) || ( getType() == cType ) ){
		//count this fib element
		return 1;
	}
	return 0;
}


/**
 * This method returns the number of this Fib-element in the order of
 * move points.
 *
 * @see getNumberOfMovePoints()
 * @return the number of this Fib-element in the order of move points
 */
unsignedIntFib cFibLeaf::getNumberOfMovePoint() const{
	
	//this Fib-element is not movable -> it is no move point
	return 0;
}


/**
 * This method is a helpmethod for getNumberOfMovePoint() .
 * Basicly it counts the number of move points befor the given
 * Fib-element pLastFibElement .
 *
 * @see getNumberOfMovePoint()
 * @see getNumberOfMovePoints()
 * @param pLastFibElement a pointer to the Fib-element which called this
 * 	method last
 * @return the number of movepoints befor the given Fib-element pLastFibElement
 */
unsignedIntFib cFibLeaf::getNumberOfMovePointUp(
		const cFibElement * pLastFibElement ) const{
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNumberOfMovePointUp( this );
	}//else no superior done counting
	return 0;
}

#endif //FEATURE_FAST_UPDATE

/**
 * This method returns the number of Fib-elements of a type in this Fib
 * -object.
 *
 * @see getType()
 * @see getNumberOfElement()
 * @param cType the character of the type ( @see getType() ), for which
 * 	the elements should be counted; u (the standartvalue) stands for
 * 	Fib-Elements of any type
 * @return the number of Fib-elements of a type in the Fib-object
 */
unsignedIntFib cFibLeaf::getNumberOfElements( char cType ) const{

	if ( (cType == 'u') || (getType() == cType) ){
		//this element has the correct type
		return 1;
	}
	return 0;
}


/**
 * This method returns the number of move points in this Fib-object.
 *
 * @see getNumberOfMovePoint()
 * @return the number of move points in this Fib-object
 */
unsignedIntFib cFibLeaf::getNumberOfMovePoints( ) const{
	//leaf -elements aren't moveble
	return 0;
}

/**
 * @return true if this Fib-element is movebel else false
 */
bool cFibLeaf::isMovable() const{
	//leaf -elements aren't moveble
	return false;
}

/**
 * This method returns the number of object points in this Fib-object.
 *
 * @see getNumberOfObjectPoint()
 * @return the number of object points in this Fib-object
 */
unsignedIntFib cFibLeaf::getNumberOfObjectPoints() const{

	//no object points for this object
	return 0;
}


/**
 * This method returns the number of the Fib-element over wich the
 * objectPoint object point is defined.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @param uiObjectPoint the number of the object point for which the
 * 	definig Fib-element number should be returned
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return the number of the Fib-element over wich the objectPoint
 * 	object point is defined
 */
unsignedIntFib cFibLeaf::objectPointToElementPoint( const unsignedIntFib
		uiObjectPoint, bool bAbsolute ) const{

	if ( bAbsolute ){
		/*go to the most top/ superior Fib-element and call this method non
		absolute*/
		cFibElement * pActualElement = const_cast<cFibLeaf *>( this );
		while ( pActualElement->pSuperiorElement != NULL ){
			pActualElement = pActualElement->pSuperiorElement;
		}
		return pActualElement->objectPointToElementPoint( uiObjectPoint );
	}//else lNumber is an relative value

	//no such underobject, leafs don't have underobjects
	return 0;
}


/**
 * This method inserts the given Fib-element fibElement on the
 * specified position. The replaced Fib-element will be the underobject
 * of the inserted Fib-element fibElement.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type of the Fib-element insted of which the given
 * 	Fib-element fibElement should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, in which position the given
 * 	Fib-element fibElement should be inserted; if 0 the given
 * 	fibElement will be inserted under this Fib-element
 * @param fibElement the Fib-element to insert
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib-element defines are needed, else the 
 * 	Fib-element will be removed even if its variables are needed elsewher
 * @return true if the Fib-element fibElement was inserted, else false
 */
bool cFibLeaf::insertElement( cFibElement * fibElement, const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute, bool bCheckVariables ){
	
	if ( fibElement == NULL ){
		//nothing to insert
		return false;
	}
	if ( elementPoint == 0 ){
		//can't insert the fib Element in this
		return false;
	}
	if ( bAbsolute ){
		return getMasterRoot()->insertElement( fibElement, cType,
			elementPoint, false, bCheckVariables );
	}//else elementPoint is an relative value
	
	/*get the pSuperiorElement of the to replacing object and call
	insertElement of it*/
	cFibElement * pFibElementToReplace = getFibElement( cType, elementPoint );
	if ( (pFibElementToReplace != NULL) &&
			(pFibElementToReplace->pSuperiorElement != NULL) ){
			
			return pFibElementToReplace->pSuperiorElement->insertElement(
				fibElement, 'u', (pFibElementToReplace->getNumberOfElement()) + 1 -
				(pFibElementToReplace->pSuperiorElement->getNumberOfElement() ),
				false, bCheckVariables );
			
	}//else the to replace Fib-element dosn't exists or is the topmost
	return false;
}


/**
 * This method inserts the given Fib-object fibObject on the
 * specified position. On the specified position a listelement will
 * be inserted, with the old Fib-object and the given Fib-object
 * fibObject as its underobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib-element, on which position the 
 * 	given Fib-object fibObject should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, on which position the given
 * 	Fib-object fibObject should be inserted
 * @param fibObject the Fib-object to insert
 * @param first if true, the inserted object will be the first
 * 	underobject of the new listelement
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib-object
 * @return true if the Fib-object fibObject was inserted, else false
 */
bool cFibLeaf::insertObjectInElement( cFibElement *fibObject, const char cType,
		const unsignedIntFib elementPoint, bool first,
		bool bAbsolute ){
	
	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	
	if ( elementPoint == 0 ){
		//insert for the underobject of this Fib-element
		//can't replace in an leaf -element
		return false;
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->insertObjectInElement( fibObject, cType, elementPoint, first );
	}//else elementPoint is an relative value
	
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	cFibElement *pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition != NULL) &&
			(pFibElementPosition->pSuperiorElement != NULL) ){
			
			return pFibElementPosition->pSuperiorElement->insertObjectInElement(
				fibObject, 'u',
				(pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				first );
			
	}//else the to insert position dosn't exists or is the topmost
	return false;
}


/**
 * This method overwrites the Fib-object on specified position with
 * the given Fib-object fibObject. The Fib-object on specified
 * position will be replaced with the given Fib-object fibObject.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see insertObjectInElement()
 * @see getType()
 * @param cType the type of the Fib-element, on which position the 
 * 	given Fib-object fibObject should be inserted
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, on which position the given
 * 	Fib-object fibObject should be inserted
 * @param fibObject the Fib-object to insert
 * @param bDeleteOld if true, delete the old Fib-object from the memory
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return true if the old Fib-object was overwritten and the given 
 * 	Fib-object fibObject was inserted, else false
 */
bool cFibLeaf::overwriteObjectWithObject( cFibElement *fibObject,
		const char cType, const unsignedIntFib elementPoint,
		bool bDeleteOld, bool bAbsolute ){
	
	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	
	if ( elementPoint == 0 ){
		//insert for the (first) underobject of this Fib-element
		//can't replace in an leaf -element
		return false;
	}
	if ( bAbsolute ){
		return getMasterRoot()->overwriteObjectWithObject( fibObject, cType, elementPoint, bDeleteOld );
	}//else elementPoint is an relative value

	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	cFibElement *pFibElementPosition = getFibElement( cType, elementPoint, bAbsolute );
	if ( (pFibElementPosition != NULL) &&
			(pFibElementPosition->pSuperiorElement != NULL) ){
			
			return pFibElementPosition->pSuperiorElement->overwriteObjectWithObject(
				fibObject, 'u', (pFibElementPosition->getNumberOfElement()) + 1 -
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
 * 	Fib-object
 * @return true if the connected Fib-object was removed, else false
 */
bool cFibLeaf::removeObject( const unsignedIntFib objectPoint,
		bool bDeleteOld, bool bAbsolute ){
	
	if ( objectPoint == 0 ){
		//can't remove whool object
		return false;
	}
	
	if ( bAbsolute ){
		/*go to the most top/ superior Fib-element and call this method non
		absolute*/
		cFibElement * pActualElement=this;
		while ( pActualElement->pSuperiorElement != NULL ){
			pActualElement = pActualElement->pSuperiorElement;
		}
		return pActualElement->removeObject( objectPoint, bDeleteOld );
	}//else elementPoint is an relative value

	unsignedIntFib uiDefiningElementPoint = objectPointToElementPoint( objectPoint );
	if ( uiDefiningElementPoint == 0 ){
		//no defining element point
		return false;
	}
	cFibElement *pDefiningFibElement = getFibElement( uiDefiningElementPoint );
	if ( pDefiningFibElement == NULL ){
		//nothing to remove
		return false;
	}
	cFibElement *pContainingFibElement = pDefiningFibElement->pSuperiorElement;
	if ( pContainingFibElement == NULL ){
		//nowher to remove
		return false;
	}
	if ( ( pContainingFibElement->getType() != 'l' ) ||
			( pContainingFibElement->getType() != 'o' ) ){
		//containing element is no listelement -> can't remove
		return false;
	}

	return pContainingFibElement->removeObject(
		pDefiningFibElement->getNumberOfMovePoint() -
		pContainingFibElement->getNumberOfMovePoint(),
		bDeleteOld );
}


/**
 * This method checks, if all Fib-elements of this Fib-object
 * have the underobjects they need to be correct.
 *
 * @return true if all Fib-elements of this Fib-object have the
 * 	underobjects they need to be correct, else false
 */
bool cFibLeaf::hasUnderAllObjects() const{

	//leaf -elements need no underobjects
	return true;
}

/**
 * This method checks, if the Fib-element on the specified position
 * is deletable.
 * An deletable Fib-element doesn't make the Fib-object invalid if
 * it is deleted (e.g. points- and listelements are never deletable).
 *
 * @see removeElement()
 * @see cutElement()
 * @see getType()
 * @param cType the type of the Fib-element to check
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, to check
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib-element defines are needed, else the 
 * 	Fib-element will be removed even if its variables are needed elsewher
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return true if the Fib-element is deletable, else false
 */
bool cFibLeaf::isRemovableElement( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute, bool bCheckVariables ) const{
	
	if ( elementPoint == 0 ){
		//check this Fib-element
		//this is a leafelement -> this Fib-element can't be removed
		return false;
	}//else check an other Fib-element

	const cFibElement * pFibElementToCheck = getConstFibElement( cType,
		elementPoint, bAbsolute );
	
	if ( pFibElementToCheck != NULL ){
		return pFibElementToCheck->isRemovableElement( 'u', 0, false, bCheckVariables );
	}//else no element ->can't remove
	return false;
}


/**
 * This method cuts the Fib-element on the specified position.
 * This works like removeElement(), except that the removed element is 
 * returned.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib-element to cut
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, to cut
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib-element defines are needed, else the 
 * 	Fib-element will be removed even if its variables are needed elsewher
 * @return the pointer to the cuted Fib-element or NULL, if the Fib
 * 	-element couldn't cut
 */
cFibElement * cFibLeaf::cutElement( const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute, bool bCheckVariables ){

	cFibElement * pFibElementToRemove = getFibElement( cType, elementPoint, bAbsolute );
	
	if ( (pFibElementToRemove == NULL) ||
			(pFibElementToRemove->pSuperiorElement == NULL)  ){
		return NULL;
	}
	
	if ( ! pFibElementToRemove->isRemovableElement( 'u', 0, false, bCheckVariables ) ){
		//can't remove the fib element
		return NULL;
	}//the element can be removed
	
	return pFibElementToRemove->pSuperiorElement->cutElement( 'u',
		pFibElementToRemove->getNumberOfElement() + 1 -
		pFibElementToRemove->pSuperiorElement->getNumberOfElement(),
		false, bCheckVariables );
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method deletes this given Fib-object with all the fib
 * elements it contains and is contained in. The memory for the fib
 * -object is freed.
 */
void cFibLeaf::deleteObject(){

	//delete this Fib-element
	delete this;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method moves a Fib-limb -element (cFibLimb) on the specified
 * position over iHowfar Fib-elements.
 * Moving is stoped if an invalid Fib-object would result (e.g. no Fib
 * -element can be moved over an Fib-elements that defines a variable
 * the moved Fib-element uses).
 * Moving an Fib-element into an listelement will result in an
 * listelement with the moved element in everyone of it's underobjects.
 *
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib-element to move
 * @param elementPoint the number of the Fib-element, in the order of
 * 	Fib-elements of the given type cType, to move
 * @param iHowfar the number of Fib-elements over which the to move
 * 	Fib-element should be moved; if this value is positiv the Fib
 * 	-element will be moved over Fib-elements it contains else over
 * 	Fib-elements it is contained in
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib-object
 * @return the number of Fib-Elements over which the to move Fib
 * 	-element was moved; if this value is positiv the Fib-element
 * 	was moved over Fib-elements it contains else over Fib-elements
 * 	it is contained in
 */
intFib cFibLeaf::moveLimbElement( const char cType, const
		unsignedIntFib elementPoint, const intFib iHowfar, bool bAbsolute ){
	
	if ( iHowfar == 0 ){
		//moved enougth
		return 0;
	}
	if ( iHowfar < 0 ){
		return moveLimbElementUp( cType, elementPoint, iHowfar * -1 , bAbsolute ) * -1;
	}
	cFibElement * pFibElementToMove = getFibElement( cType, elementPoint, bAbsolute );
	//check if the Fib-element is moveble
	if ( (pFibElementToMove == NULL) ||
			( ! pFibElementToMove->isMovable() ) ){
		//can't move the Fib-element
		return 0;
	}

	if ( iHowfar > 0 ){
		//move down
		if ( pFibElementToMove == pSuperiorElement ){
			//can't move over this element
			return 0;
		}
		
	}//else move up
	return pFibElementToMove->moveLimbElement( 'u', 0, iHowfar );
}


#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this fib
 * -object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib-elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
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
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cFibLeaf::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	//all is equal
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib-object is equal to this Fib
 * -object.
 * Variables can be others, but must be defined and aused in equivalent
 * Fib-elements.
 *
 * @param fibObject the Fib-object to which this Fib-object should be
 * 	equal
 * @return true if this Fib-object is equal to the given Fib-object,
 * 	else false
 */
bool cFibLeaf::equal( const cFibElement & fibObject ) const{
	
	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	//all is equal
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * @return this method returns true if this Fib-element is an
 * 	leafelement, alse false
 */
bool cFibLeaf::isLeaf() const{
	return true;
}



//protected methods


#ifndef FEATURE_NO_REGISTER_NEW_FIB_

/**
 * With this method a new Fib-element in the Fib-Object is registert
 * by the other Fib-elements in the Fib-Object.
 *
 * @param newFibElement the new Fib-element to register
 * @param uINumberOfFibElement the number of the new Fib-element in the
 * 	order of all Fib-Elements in the Fib-object
 * @param bDirectionUp the direction in which the registration of the
 * 	new Fib-element is performed in the Fib-object tree;
 * 	from the position on which the new Fib-Element is added the
 * 	method is called for both directions
 * @return true if the registration was successfull, else false
 */
bool cFibLeaf::registerNewFibElement( cFibElement *newFibElement,
		unsignedIntFib uINumberOfFibElement, bool bDirectionUp ){
	
	if ( newFibElement==NULL ){
		//no Fib-element to register
		return false;
	}
	
	if ( bDirectionUp ){
		/*register the new Fib-element in all Fib-element in direction up*/
		
		if ( pSuperiorElement != NULL ){
			pSuperiorElement->registerNewFibElement( newFibElement,
					uINumberOfFibElement, true );
		}
		
	}//for register in direction below -> nothing below -> nothing todo

	
	//update the position of this Fib-element in order of Fib-elements
	if ( this->uINumberOfFibElement >= uINumberOfFibElement ){
		/*add 1 to the number of this fib element in the order of
		Fib-elements, because the new Fib-element was added in
		order of Fib-elements befor it*/
		this->uINumberOfFibElement++;
	}
	//update pPreviousFibElement
	if ( this->uINumberOfFibElement == uINumberOfFibElement + 1 ){
		//this Fib-element is the next Fib-element to the new Fib-element
		pPreviousFibElement = newFibElement;
	}
	
	//update pNextFibElement
	if ( this->uINumberOfFibElement == uINumberOfFibElement - 1 ){
		//the new Fib-element is the next Fib-element to this Fib-element
		pNextFibElement = newFibElement;
	}
	return true;
}


/**
 * With this method a new part Fib-object in the Fib-Object is
 * registert by the other Fib-elements in the Fib-Object.
 *
 * @param newFibObject the new part Fib-object to register
 * @param uILowerNumberOfFibElements the number of the Fib-element in the
 * 	new part Fib-object with the lowest number in the order of all
 * 	Fib-Elements in the entire Fib-object
 * @param uIUpperNumberOfFibElements the number of the Fib-element in the
 * 	new part Fib-object with the highest number in the order of all
 * 	Fib-Elements in the entire Fib-object
 * @param bDirectionUp the direction in which the registration of the
 * 	new part Fib-object is performed in the Fib-object tree;
 * @return true if the registration was successfull, else false
 */
bool cFibLeaf::registerNewFibObject( cFibElement *newFibObject,
		unsignedIntFib uILowerNumberOfFibElements,
		unsignedIntFib uIUpperNumberOfFibElements, bool bDirectionUp ){

	if ( newFibObject == NULL ){
		//no Fib-element to register
		return false;
	}
	if ( uILowerNumberOfFibElements < uIUpperNumberOfFibElements ){
		/*invalid bounderies for numbers of Fib-elements in the order of
		Fib-elements*/
		return false;
	}

	if ( bDirectionUp ){
		/*register the new Fib-element in all Fib-element in direction up*/
		
		if ( pSuperiorElement != NULL ){
			pSuperiorElement->registerNewFibObject( newFibObject,
					uILowerNumberOfFibElements, uIUpperNumberOfFibElements, true );
		}
		
		
	}//for register in direction below -> nothing below -> nothing todo
	
	//update the position of this Fib-element in order of Fib-elements
	if ( this->uINumberOfFibElement >= uINumberOfFibElement ){
		/*add 1 to the number of this fib element in the order of
		Fib-elements, because the new Fib-element was added in
		order of Fib-elements befor it*/
		this->uINumberOfFibElement = this->uINumberOfFibElement+
			( uIUpperNumberOfFibElements - uILowerNumberOfFibElements + 1);
	}
	bool bReturnValue = true;
	
	//update pPreviousFibElement
	if ( this->uINumberOfFibElement == uIUpperNumberOfFibElements + 1 ){
		/*the last Fib-element in the new Fib-Object is the previous
		Fib-element to this Fib-element*/
		cFibElement *lastFibElement = newFibObject;
		//find last Fib-element
		while ( lastFibElement->getNumberOfElement() != uIUpperNumberOfFibElements ){
		
			if ( lastFibElement->pNextFibElement == NULL ){
				//error: last Fib-element has wrong number
				bReturnValue = false;
				break;
			}
			lastFibElement = lastFibElement->pNextFibElement;
		}
		pPreviousFibElement = lastFibElement;
	}
	
	//update pNextFibElement
	if ( this->uINumberOfFibElement == uILowerNumberOfFibElements - 1 ){
		/*the first Fib-element in the new Fib-Object is the next
		Fib-element to this Fib-element*/
		pNextFibElement = newFibObject;
	}
	return bReturnValue;
}
#endif //FEATURE_NO_REGISTER_NEW_FIB_

#ifndef FEATURE_FAST_UPDATE

/**
 * This method updates the values/ properties off all Fib-elements in
 * this Fib-object beginning with this Fib-element.
 *
 * @param previosFibElement the prvios Fib-element to this Fib-element
 * 	in the order of Fib-elements; if it is NULL ther is no previos
 * 	Fib-element to this
 * @return a pointer to the last evalued Fib-element;
 * 	if NULL an error has occured
 */
cFibElement* cFibLeaf::updateValues( cFibElement *previosFibElement,
		cFibElement * pNextArm ){

	cFibElement * lastFibElementUpdated = NULL;
	
	pNextFibElement = pNextArm;
	
	lastFibElementUpdated = cFibElement::updateValues( previosFibElement, pNextArm );
	if ( lastFibElementUpdated == NULL ){
		//something gone wrong while updating
		return NULL;
	}
	
	return lastFibElementUpdated;
}


/**
 * This method returns the number of the next connected object point
 * in the order of connected object points that conntains this Fib
 * -element.
 *
 * @param uINumberOfStartFibElement the number, in the order of all
 * 	Fib-elements, of the Fib-element for which the connected object
 * 	point is to return
 * @see getNumberOfObjectPoint
 * @see getNumberOfObjectPoints()
 * @return the number of the next connected object point for this Fib 
 * 	-element
 */
unsignedIntFib cFibLeaf::getNumberOfObjectPoint(
		unsignedIntFib uINumberOfStartFibElement ) const{
	
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getNumberOfObjectPoint( uINumberOfStartFibElement );
	}
	return 0;
}


/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib-element.
 *
 * @see elementPointToObjectPoints()
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param referenceFibObject the Fib-element from which this method was
 * 	called
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib-element of the type cType
 */
list<unsignedIntFib> cFibLeaf::elementPointToObjectPoints(
		const cFibElement *referenceFibObject,
		const unsignedIntFib uiLastObjectPoint ) const{

	//no object point in an leafelement
	list<unsignedIntFib> liFoundedObjectPoints;
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
unsignedIntFib cFibLeaf::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	/*leafelements shouldn't define variables (they couldn't be used below
	the leafelement, because ther is nothing below), so ther is nothing to do*/
	return uiLastVariableNumber;
}









