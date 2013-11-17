/**
 * @class cFibLimb
 * file name: cFibLimb.h
 * @author Betti Oesterholz
 * @date 06.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a Fib element, which are limbs.
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
 * limbs. Limbs have exactly one underobject.
 * It's not possible to create instances from this class.
 *
 */
/*
History:
06.12.2009  Oesterholz  created
06.01.2010  Oesterholz  getAllFibElements() uses now getAllFibElementsFromPosition()
02.09.2010  Oesterholz  the destructor cuts the conections from the
	underobject to this object
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
21.02.2013  Oesterholz  Bugfix in overwriteObjectWithObject() old
	pUnderObject could be NULL
10.07.2013  Oesterholz  subobject methods added
13.11.2013  Oesterholz  FEATURE_INSERT_OBJECT_IN_ELEMENT implemented
*/

//debugging switch
//#define DEBUG

#include "cFibLimb.h"
#include "cList.h"


using namespace fib;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInUnderobject the Fib-Element which is the underobejct of
 * 	this Fib element (it also stands next in the order of Fib elements)
 * @param pInSuperiorElement the Fib-Element in which this Fib element
 * 	is the underobject
 */
cFibLimb::cFibLimb( cFibElement * pInUnderobject ,
		cFibElement * pInSuperiorElement ):
		cFibElement( pInSuperiorElement ),
		pUnderObject( pInUnderobject ){
	
	if ( pUnderObject ){
#ifdef FEATURE_FAST_UPDATE
		if ( pUnderObject->pSuperiorElement != NULL ){
			pUnderObject->pSuperiorElement->cutConnectionsTo(
				pUnderObject );
		}
#endif //FEATURE_FAST_UPDATE
		pUnderObject->pSuperiorElement = this;
	}
}

#else //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorElement the Fib-Element in which this Fib element
 * 	is the underobject
 * @param pInPreviousFibElement the Fib-Element which stands in th order
 * 	of Fib elements befor this Fib element
 * @param pInUnderobject the Fib-Element which is the underobejct of
 * 	this Fib element (it also stands next in the order of Fib elements)
 */
cFibLimb::cFibLimb( cFibElement * pInSuperiorElement,
		cFibElement * pInPreviousFibElement, cFibElement * pInUnderobject ):
		cFibElement( pInSuperiorElement, pInPreviousFibElement, pInUnderobject ),
		pUnderObject( pInUnderobject ){
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * copyconstructor
 * This copyconstructor constructs a copy of this Fib-Element.
 * It dosn't copy other Fib elements than this, even if ther are in this
 * Fib element.
 *
 * @param fibLimbElement the Fib element to copy
 */
cFibLimb::cFibLimb( const cFibLimb & fibLimbElement ):
		cFibElement( fibLimbElement ),
		pUnderObject( NULL ){
	//nothing to do
}


/**
 * destructor
 */
cFibLimb::~cFibLimb(){
	
	//remove the superior Fib element of the underobject
	if ( pUnderObject != NULL ){
		//incorrect underobject
		pUnderObject->cutConnectionsTo( this );
	}
}


/**
 * This method checks, if this Fib element is an valid Fib element.
 *
 * @return true if this Fib element is an valid Fib element, else false
 */
bool cFibLimb::isValidFibElement() const{
	
#ifndef FEATURE_FAST_UPDATE
	if ( ( pSuperiorElement != NULL ) && (pPreviousFibElement == NULL) ){
		//if this is not a topmost Fib element it need a previos element
		return false;
	}
#endif //FEATURE_FAST_UPDATE
	if ( pUnderObject == NULL ){
		/*every limb Fib element need an underobject
		-> Fib element incorrect*/
		return false;
	}

	//everything is ok
	return true;
}

#ifdef FEATURE_FAST_UPDATE

/**
 * This method returns the next Fib element in the order of Fib elements.
 *
 * @return a pointer to the next Fib element in the order of Fib elements
 * 	or the NULL pointer if non such exists
 */
cFibElement * cFibLimb::getNextFibElement(){
	
	if ( pUnderObject ){
		return pUnderObject;
	}//else
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
cFibElement * cFibLimb::getNextFibElementUp( const cFibElement * pLastFibElement ){
	
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
cFibElement * cFibLimb::getNextFibElement( char cType ){
	
	if ( pUnderObject ){
		if (  (cType == 'u') || (pUnderObject->getType() == cType) ){
			return pUnderObject;
		}//else
		return pUnderObject->getNextFibElement( cType );
	}//else
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
cFibElement * cFibLimb::getNextFibElementUp( const cFibElement * pLastFibElement,
		char cType ){
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNextFibElementUp( this, cType );
	}//else no such Fib element
	return NULL;
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements with the given type cTyp.
 *
 * @param lNumber the number of the Fib-Element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements or the NULL pointer if non such exists
 */
cFibElement * cFibLimb::getConstFibElement( longFib lNumber,
		bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibLimb::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	if ( lNumber == 0 ){
		//this is the correct Fib element
		return const_cast<cFibLimb*>( this );
	}//else
	if ( bAbsolute ){
		return getMasterRoot()->getConstFibElement( lNumber );
	}//else lNumber is an relative value
	if ( lNumber == 1 ){
		//this is the correct Fib element
		return const_cast<cFibLimb*>( this );
	}//else
	
	if ( (0 < lNumber) && ( pUnderObject != NULL ) ){
		//the lNumber underobject is under this branchelement -> return the lNumber underobject
		lNumber--;//remove this Fib element from the count
		//search the underobject Fib element
		DEBUG_OUT_L2(<<"pUnderObject->getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done return NULL"<<endl<<flush);
		return pUnderObject->getConstFibElement( lNumber );
	}//else no such Fib element under this limb -> search higher
	if ( pSuperiorElement ){
		DEBUG_OUT_L2(<<"pSuperiorElement->getConstFibElementUp( this="<<this<<", lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done return NULL"<<endl<<flush);
		return pSuperiorElement->getConstFibElementUp( this, lNumber );
	}//else no such Fib element
	DEBUG_OUT_L2(<<"cFibLimb::getConstFibElement( lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done return NULL"<<endl<<flush);
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
 * @param lNumber the number of the Fib-Element to return
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibLimb::getConstFibElementUp( const cFibElement * pLastFibElement,
		longFib lNumber ) const{
	

	if ( lNumber == -1 ){
		//this is the correct Fib element
		return const_cast<cFibLimb*>( this );
	}//else
	//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		if ( lNumber < 0 ){
			//remove this Fib element from the count
			lNumber++;
		}
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
cFibElement * cFibLimb::getConstFibElement( char cType, longFib lNumber,
		bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibLimb::getConstFibElement( cType="<<cType<<", lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) started"<<endl<<flush);
	if ( lNumber == 0 ){
		//this is the correct Fib element
		return const_cast<cFibLimb*>( this );
	}//else
	if ( bAbsolute ){
		return getMasterRoot()->getConstFibElement( cType, lNumber );
	}//else lNumber is an relative value
	if ( cType == 'u' ){
		//type is irrelevant respectivly return of every type
		return getConstFibElement( lNumber );
	}
	if ( ( lNumber == 1 ) && ( getType() == cType ) ){
		//this is the correct Fib element
		return const_cast<cFibLimb*>( this );
	}//else
	
	if ( ( 0 < lNumber ) && ( pUnderObject != NULL ) ){
		//the lNumber underobject is under this branchelement -> return the lNumber underobject
		if ( getType() == cType ){
			lNumber--;//remove this Fib element from the count
		}
		//search the underobject Fib element
		DEBUG_OUT_L2(<<"pUnderObject->getConstFibElement( cType="<<cType<<", lNumber="<<lNumber<<" ) done no such Fib element"<<endl<<flush);
		return pUnderObject->getConstFibElement( cType, lNumber );
	}//else no such Fib element under this limb -> search higher
	if ( pSuperiorElement ){
		DEBUG_OUT_L2(<<"pSuperiorElement->getConstFibElementUp( this="<<this<<", cType="<<cType<<", lNumber="<<lNumber<<" ) done no such Fib element"<<endl<<flush);
		return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
	}//else no such Fib element
	DEBUG_OUT_L2(<<"cFibLimb::getConstFibElement( cType="<<cType<<", lNumber="<<lNumber<<", bAbsolute="<<bAbsolute<<" ) done no such Fib element"<<endl<<flush);
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
 * @param lNumber the number of the Fib-Element to return
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement * cFibLimb::getConstFibElementUp( const cFibElement * pLastFibElement,
		char cType, longFib lNumber ) const{
	

	if ( (lNumber == -1) && ( getType() == cType ) ){
		//this is the correct Fib element
		return const_cast<cFibLimb*>( this );
	}//else
	//no such Fib element under this branch -> search higher
	if ( pSuperiorElement ){
		if ( ( lNumber < 0 ) && (getType() == cType) ){
			lNumber++;//remove this Fib element from the count
		}
		return pSuperiorElement->getConstFibElementUp( this, cType, lNumber );
	}//else
	
	return NULL;
}

#endif //FEATURE_FAST_UPDATE



/**
 * This method returns the number of subobjects in this Fib element.
 * (e. g. limb elements have one subobject)
 *
 * @see getSubobject()
 * @see getSubobjects()
 * @return the number of subobjects in this Fib element
 */
unsignedIntFib cFibLimb::getNumberOfSubobjects() const{
	
	return 1;
}


/**
 * This method returns the uiNumberOfSubobject'th subobject of this
 * Fib element.
 *
 * @see getNumberOfSubobjects()
 * @see getSubobjects()
 * @param uiNumberOfSubobject the number of the subobject to return
 * @return a pointer to the uiNumberOfSubobject'th subobject of this
 * 	Fib element, or the null pointer NULL if non exists
 */
cFibElement * cFibLimb::getSubobject( const unsignedIntFib uiNumberOfSubobject ){
	
	return (uiNumberOfSubobject == 1) ? pUnderObject : NULL;
}


/**
 * This method returns the uiNumberOfSubobject'th subobject of this
 * Fib element.
 *
 * @see getNumberOfSubobjects()
 * @see getSubobjects()
 * @param uiNumberOfSubobject the number of the subobject to return
 * @return a pointer to the uiNumberOfSubobject'th subobject of this
 * 	Fib element, or the null pointer NULL if non exists
 */
const cFibElement * cFibLimb::getSubobject(
	const unsignedIntFib uiNumberOfSubobject ) const{
	
	
	return (uiNumberOfSubobject == 1) ? pUnderObject : NULL;
}


/**
 * This method returns all subobjects of this Fib element.
 *
 * @see getNumberOfSubobjects()
 * @see getSubobject()
 * @return a list with all the subobjects of this Fib element
 */
list< cFibElement * > cFibLimb::getSubobjects(){
	
	return list< cFibElement * >( 1, pUnderObject );
}


/**
 * This method returns all subobjects of this Fib element.
 *
 * @see getNumberOfSubobjects()
 * @see getSubobject()
 * @return a list with all the subobjects of this Fib element
 */
const list< cFibElement * > cFibLimb::getSubobjects() const{
	
	return list< cFibElement * >( 1, pUnderObject );
}



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
list<cFibElement*> cFibLimb::getAllFibElementsFromPosition(
		char cType, edDirection direction,
		unsignedLongFib lNumberOfMaxReturnedElements ){
	
	unsignedLongFib lOldNumberOfMaxReturnedElements = lNumberOfMaxReturnedElements;
	
	/*list with the founded elements for the subobjectst*/
	list<cFibElement*> liFoundedElements;

	/*if the direction is ED_ALL, ED_BELOW or ED_BELOW_EQUAL add
	lNumberOfMaxReturnedElements Fib elements below to the list*/
	if ( (direction == ED_ALL) || (direction == ED_BELOW) ||
			(direction == ED_BELOW_EQUAL) ){
		
		if ( pUnderObject != NULL ){

			//add the underobject, if it has the correct type
			bool bFindMoreFibElements = true;
			if ( (cType == 'u') || (pUnderObject->getType() == cType) ||
					( (cType == 'w') && (!(pUnderObject->isValidFibElement())) ) ){
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
				liFoundedElements = pUnderObject->getAllFibElementsFromPosition(
					cType, ED_BELOW, lNumberOfMaxReturnedElements );
			}
			
			if ( (cType == 'u') || (pUnderObject->getType() == cType) ||
					( (cType == 'w') && (!(pUnderObject->isValidFibElement())) ) ){
				//next element has the correct type -> it will be added
				liFoundedElements.push_front( pUnderObject );
			}
			if ( direction != ED_ALL ){
				//just give back from belower
				return liFoundedElements;
			}
		}//else no underobject
	}

	list<cFibElement*> liSupFoundedElements;
	if (  (direction == ED_ALL) || (direction == ED_HIGHER) ||
			(direction == ED_HIGHER_EQUAL) ){
		
		/*if elements wher found decrase lNumberOfMaxReturnedElements
		about the minimum of founded elements in the list or the half of the
		old lNumberOfMaxReturnedElements*/
		if ( (direction == ED_ALL) && (lOldNumberOfMaxReturnedElements != 0) ){

			unsignedLongFib lNumberOfEntriesToBeFound =
				lOldNumberOfMaxReturnedElements / 2 + 1;
				
			lNumberOfMaxReturnedElements =
				lOldNumberOfMaxReturnedElements - liFoundedElements.size();
			
			if ( lNumberOfMaxReturnedElements < lNumberOfEntriesToBeFound ){
				lNumberOfMaxReturnedElements = lNumberOfEntriesToBeFound;
			}
		}
		
		if ( pSuperiorElement != NULL ){
	
			/*if the direction is ED_ALL, ED_HIGHER or ED_HIGHER_EQUAL add
			lNumberOfMaxReturnedElements Fib elements higher to the list*/
				//add the pSuperiorElement, if it has the correct type
			bool bFindMoreFibElements = true;
			if ( (cType == 'u') || (pSuperiorElement->getType() == cType)  ||
					( (cType == 'w') && ( ! (pSuperiorElement->isValidFibElement()) ) ) ){
				//previous element has the correct type -> it will be added
				if ( 0 < lNumberOfMaxReturnedElements ){
					//the reference element will be added
					lNumberOfMaxReturnedElements--;
					if ( lNumberOfMaxReturnedElements == 0 ){
						bFindMoreFibElements = false;
					}
				}
			}
			
			//find more entries
			if ( bFindMoreFibElements ){
				liSupFoundedElements = pSuperiorElement->getAllFibElementsFromPosition(
					cType, ED_HIGHER, lNumberOfMaxReturnedElements );
			}
				
			if ( (cType == 'u') || (pSuperiorElement->getType() == cType)  ||
					( (cType == 'w') && ( ! (pSuperiorElement->isValidFibElement()) ) ) ){
				//previous element has the correct type -> it will be added
				liSupFoundedElements.push_front( pSuperiorElement );
			}
		}
	}
	if ( (direction == ED_HIGHER) || (direction == ED_HIGHER_EQUAL) ){
		//all elements to give back are found
		return liSupFoundedElements;
	}
	if ( lOldNumberOfMaxReturnedElements != 0){
		/*reduce the founded Fib elements so that maximal lOldNumberOfMaxReturnedElements
		elements are given back*/
		while ( lOldNumberOfMaxReturnedElements <
				(liSupFoundedElements.size() + liFoundedElements.size()) ){
			
			if ( liSupFoundedElements.size() < liFoundedElements.size() ){
				liFoundedElements.pop_back();
			}else{
				liSupFoundedElements.pop_back();
			}
		}
	}
	// concatinate the tow lists
	liFoundedElements.insert( liFoundedElements.begin(),
		liSupFoundedElements.begin(), liSupFoundedElements.end() );
	
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
bool cFibLimb::isUsedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	if ( direction == ED_POSITION ){
		return false;
	}
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//check underobject
		if ( pUnderObject != NULL ){
			if ( pUnderObject->isUsedVariable( variable, ED_BELOW_EQUAL ) ){
				return true;
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
set<cFibVariable*> cFibLimb::getUsedVariables( edDirection direction ){
	
	set<cFibVariable*> setUsedVariables;
	if ( direction == ED_POSITION ){
		return setUsedVariables;
	}
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//check underobject
		if ( pUnderObject != NULL ){
			set<cFibVariable*> setUsedVariablesOfUnderObject =
				pUnderObject->getUsedVariables( ED_BELOW_EQUAL );
			setUsedVariables.insert( setUsedVariablesOfUnderObject.begin(),
				setUsedVariablesOfUnderObject.end() );
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
 * @param pCallingFibElement the Fib-Element which called this method
 * @return true if the variable is used, else false
 */
bool cFibLimb::isDefinedVariableInternal( const cFibVariable *variable,
		edDirection direction,
		const cFibElement * pCallingFibElement ) const{
	
	if ( direction == ED_POSITION ){
		return false;
	}
	
	if ( (direction == ED_ALL) || (direction == ED_BELOW) ||
			(direction == ED_BELOW_EQUAL) ){
		//check underobject
		if ( pUnderObject != NULL ){
			if ( pUnderObject->isDefinedVariableInternal(
					variable, ED_BELOW_EQUAL, this ) ){
				return true;
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
 * @param pCallingFibElement the Fib-Element which called this method
 * @return the set with all variables used in the given direction from
 * 	this Fib element
 */
list<cFibVariable*> cFibLimb::getDefinedVariablesInternal(
		edDirection direction,
		const cFibElement * pCallingFibElement ){
	
	list<cFibVariable*> liDefinedVariables;
	if ( direction == ED_POSITION ){
		return liDefinedVariables;
	}
	
	if ( (direction == ED_ALL) || ( direction == ED_BELOW ) ||
			(direction == ED_BELOW_EQUAL) ){
		//check for underobject
		if ( pUnderObject != NULL ){
			list<cFibVariable*> liDefinedVariablesOfUnderObject =
				pUnderObject->getDefinedVariablesInternal( ED_BELOW_EQUAL, this );
			liDefinedVariables.insert( liDefinedVariables.end() ,
				liDefinedVariablesOfUnderObject.begin(),
				liDefinedVariablesOfUnderObject.end() );
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
bool cFibLimb::replaceVariable( cFibVariable *variableOld,
		cFibVariable *variableNew ){
	
	if ( (variableOld == NULL) || (variableNew == NULL) ){
		//can't replace
		return false;
	}
	if ( pUnderObject != NULL ){
		//replace the variable in the underobject
		return pUnderObject->replaceVariable(
			variableOld, variableNew );
	}
	return true;
}



#ifdef FEATURE_FAST_UPDATE

/**
 * This method returns the number of this Fib element in the order of
 * Fib-Elements or order of Fib-Elements of the same type if bOfType
 * is true.
 *
 * @see getNumberOfElements()
 * @param bOfType if true the returned number is the number the order
 * 	of Fib elements of the same type as this Fib-Element, else in
 * 	the order of all Fib elements
 * @return the number of this Fib element in the order of fib
 * 	-Elements or order of Fib-Elements of the same type if bOfType
 * 	is true
 */
unsignedIntFib cFibLimb::getNumberOfElement( bool bOfType ) const{
	
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
unsignedIntFib cFibLimb::getNumberOfElementUp(
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
 * This method returns the number of this Fib element in the order of
 * move points.
 *
 * @see getNumberOfMovePoints()
 * @return the number of this Fib element in the order of move points
 */
unsignedIntFib cFibLimb::getNumberOfMovePoint() const{
	
	return getNumberOfMovePointUp( this );
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
unsignedIntFib cFibLimb::getNumberOfMovePointUp(
		const cFibElement * pLastFibElement ) const{
	
	if ( pSuperiorElement ){
		return pSuperiorElement->getNumberOfMovePointUp( this ) + 1;
	}//else no superior done counting
	return 1;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method returns the number of Fib elements of a type in this Fib
 * -object.
 *
 * @see getType()
 * @see getNumberOfElement()
 * @param cType the character of the type ( @see getType() ), for which
 * 	the elements should be counted; u (the standartvalue) stands for
 * 	Fib-Elements of any type
 * @return the number of Fib elements of a type in the Fib object
 */
unsignedIntFib cFibLimb::getNumberOfElements( char cType ) const{

	unsignedIntFib uiNumberOfElements = 0;

	if ( pUnderObject != NULL ){
		uiNumberOfElements += pUnderObject->getNumberOfElements( cType );
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
unsignedIntFib cFibLimb::getNumberOfMovePoints() const{

	unsignedIntFib uiNumberOfMovePoints = 0;
	
	if ( isMovable() ){
		//this Fib element is movable -> it is a move point so count it
		uiNumberOfMovePoints = 1;
	}
	if ( pUnderObject != NULL ){
		uiNumberOfMovePoints += pUnderObject->getNumberOfMovePoints();
	}
	return uiNumberOfMovePoints;
}


/**
 * This method returns the number of object points in this Fib object.
 *
 * @see getNumberOfObjectPoint()
 * @return the number of object points in this Fib object
 */
unsignedIntFib cFibLimb::getNumberOfObjectPoints() const{

	if ( pUnderObject != NULL ){
		return pUnderObject->getNumberOfObjectPoints();
	}
	return 0;
}


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
unsignedIntFib cFibLimb::objectPointToElementPoint( const unsignedIntFib
		uiObjectPoint, bool bAbsolute ) const{
	
	if ( bAbsolute ){
		return getMasterRoot()->objectPointToElementPoint( uiObjectPoint );
	}//else lNumber is an relative value

	if ( pUnderObject != NULL ){
		const unsignedIntFib uiNumberOfFibElementsUnderObject =
			pUnderObject->objectPointToElementPoint( uiObjectPoint );
		
		if ( uiNumberOfFibElementsUnderObject == 0 ){
			//no such underobject
			return 0;
		}
		return uiNumberOfFibElementsUnderObject + 1;
	}//else no such underobject
	return 0;

}


/**
 * This method inserts the given Fib element fibElement on the
 * specified position. The replaced Fib element will be the underobject
 * of the inserted Fib element fibElement.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type of the Fib element insted of which the given
 * 	Fib element fibElement should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, in which position the given
 * 	Fib element fibElement should be inserted; if 0 the given
 * 	fibElement will be inserted under this Fib element
 * @param pFibElement a pointer to the Fib element to insert
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return true if the Fib element fibElement was inserted, else false
 */
bool cFibLimb::insertElement( cFibElement * pFibElement, const char cType,
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
	if ( elementPoint == 0 ){
		//replace the underobject of this Fib element
		return insertElement( pFibElement, 'u', 2, false, bCheckVariables );
	}
	if ( bAbsolute ){
		return getMasterRoot()->insertElement( pFibElement, cType,
			elementPoint, false, bCheckVariables );
	}//else elementPoint is an relative value
	
	/*check ( if (cType=='u') ) if the pFibElement should replace a
	underobject of this object*/
	if ( (cType == 'u') && (elementPoint == 2) ){
		//insert the pFibElement in this cFibLimb Fib element
		
		//replace the underobject with the given pFibElement
		if ( pFibElement->isLeaf() ){
			if ( pUnderObject != NULL ){
				//can't insert the underobject into a leafelement
				return false;
			}//else no underobject
			//check if the variables used in the to insert Fib element are defined higer
			if ( bCheckVariables && ( ! variablesAreDefined( pFibElement->
					getUsedVariables( ED_POSITION), ED_HIGHER_EQUAL ) ) ){
				return false;
			}
			pUnderObject = pFibElement;
#ifdef FEATURE_FAST_UPDATE
			if ( pUnderObject->pSuperiorElement != NULL ){
				pUnderObject->pSuperiorElement->cutConnectionsTo(
					pUnderObject );
			}
			pUnderObject->pSuperiorElement = this;
#endif //FEATURE_FAST_UPDATE
			updateAllValues();
			return true;
		}
		//check if the variables used in the to insert Fib element are defined higer
		if ( bCheckVariables && ( ! variablesAreDefined( pFibElement->
				getUsedVariables( ED_POSITION), ED_HIGHER_EQUAL ) ) ){
			return false;
		}
		//set the underobject of the pFibElement
		if ( pUnderObject != NULL ){
			const bool bUnderObjectReplaced =
				pFibElement->insertObjectInElement( pUnderObject );
			if ( ! bUnderObjectReplaced ){
				//can't replace the underobject
				return false;
			}
		}
		//set the new underobject of this element
		pUnderObject = pFibElement;
#ifdef FEATURE_FAST_UPDATE
		if ( pUnderObject->pSuperiorElement != NULL ){
			pUnderObject->pSuperiorElement->cutConnectionsTo(
				pUnderObject );
		}
		pUnderObject->pSuperiorElement = this;
#endif //FEATURE_FAST_UPDATE
		updateAllValues();
		//done and pFibElement inserted
		return true;

	}
	
	/*get the pSuperiorElement of the to replacing object and call
	insertElement of theas*/
	cFibElement *pFibElementToReplace = getFibElement( cType, elementPoint );
	if ( (pFibElementToReplace != NULL) &&
			(pFibElementToReplace->pSuperiorElement != NULL) ){
			
		return pFibElementToReplace->pSuperiorElement->insertElement(
			pFibElement, 'u', (pFibElementToReplace->getNumberOfElement()) + 1 -
			(pFibElementToReplace->pSuperiorElement->getNumberOfElement() ),
			false, bCheckVariables );
		
	}//else the to replace Fib element dosn't exists or is the topmost
	return false;
}


#ifdef FEATURE_INSERT_OBJECT_IN_ELEMENT
/**
 * This method inserts the given Fib object pFibObject on the
 * specified position. On the specified position a listelement will
 * be inserted, with the old Fib object and the given Fib object
 * pFibObject as its subobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib element, on which position the
 * 	given Fib object pFibObject should be inserted
 * @param uiElementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, on which position the given
 * 	Fib object pFibObject should be inserted
 * @param pFibObject the Fib object to insert
 * @param bFirst if true, the inserted object will be the first
 * 	subobject of the list element, else (it is false) the inserted
 * 	object will be the last subobject of the list element
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return true if the Fib object pFibObject was inserted, else false
 */
bool cFibLimb::insertObjectInElement( cFibElement *pFibObject, const char cType,
		const unsignedIntFib uiElementPoint, bool bFirst, bool bAbsolute ){
	
	if ( pFibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( pFibObject->getType() == 'r' ){
		//can't insert a root -element
		return false;
	}
	
	if ( (uiElementPoint == 0) || ( ! bAbsolute &&
			(uiElementPoint == 2) && (cType == 'u') ) ){
		//insert for the subobject of this Fib element
		
		//check if the subobject to overwrite is NULL
		if ( pUnderObject == NULL ){
		
			//set the values of the pFibObject
			if ( pFibObject->pSuperiorElement != NULL ){
				pFibObject->pSuperiorElement->cutConnectionsTo(
					pFibObject );
			}
			pFibObject->pSuperiorElement = this;
			
			pUnderObject = pFibObject;
			
			updateAllValues();
			
			return true;
		}//else subobject exists
		
		if ( pUnderObject->getType() == 'l' ){
			//subobject is list element -> insert pFibObject into it
			if( bFirst ){
				//add new Fib object to front of list
				(static_cast<cList*>(pUnderObject))->addUnderobject(
					pFibObject, 1 );
			}else{//add new Fib object to end of list
				(static_cast<cList*>(pUnderObject))->addUnderobject(
					pFibObject, ((static_cast<cList*>(pUnderObject))->
						getNumberOfUnderobjects()) + 1);
			}
			return true;
		}/*else create a list element and insert the old subobject and the
		new into it*/
		cFibElement * pOldSubObject = pUnderObject;
		
		if ( pFibObject->pSuperiorElement != NULL ){
			pFibObject->pSuperiorElement->cutConnectionsTo(
				pFibObject );
		}
		pOldSubObject->pSuperiorElement = NULL;
		if( bFirst ){
			pUnderObject = new cList( pFibObject, pOldSubObject );
		}else{
			pUnderObject = new cList( pOldSubObject, pFibObject );
		}
		//set superior Fib element
		pUnderObject->pSuperiorElement  = this;
		pOldSubObject->pSuperiorElement = pUnderObject;
		pFibObject->pSuperiorElement    = pUnderObject;
		updateAllValues();
		//done with inserting
		return true;
	}
	if ( bAbsolute ){
		return getMasterRoot()->insertObjectInElement(
			pFibObject, cType, uiElementPoint, bFirst );
	}//else uiElementPoint is an relative value

	/*get the pSuperiorElement of the to inserting object position and call
	insertElement() of it*/
	cFibElement *pFibElementPosition = getFibElement( cType, uiElementPoint );
	if ( (pFibElementPosition != NULL) &&
			(pFibElementPosition->pSuperiorElement != NULL) ){
			
			return pFibElementPosition->pSuperiorElement->insertObjectInElement(
				pFibObject, 'u',
				(pFibElementPosition->getNumberOfElement()) + 1 -
				(pFibElementPosition->pSuperiorElement->getNumberOfElement() ),
				bFirst );
			
	}//else the to insert position dosn't exists or is the top most
	return false;
}

#else //FEATURE_INSERT_OBJECT_IN_ELEMENT

/**
 * This method inserts the given Fib object fibObject on the
 * specified position. On the specified position a listelement will
 * be inserted, with the old Fib object and the given Fib object
 * fibObject as its subobjects.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see overwriteObjectWithObject()
 * @see getType()
 * @param cType the type of the Fib element, on which position the 
 * 	given Fib object fibObject should be inserted
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, on which position the given
 * 	Fib object fibObject should be inserted
 * @param fibObject the Fib object to insert
 * @param first if true, the inserted object will be the first
 * 	underobject of the new listelement
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return true if the Fib object fibObject was inserted, else false
 */
bool cFibLimb::insertObjectInElement( cFibElement *fibObject, const char cType,
		const unsignedIntFib elementPoint, bool first, bool bAbsolute ){
	
	if ( fibObject == NULL ){
		//nothing to insert
		return false;
	}
	if ( fibObject->getType() == 'r' ){
		//can't insert a root -element
		return false;
	}
	
	if ( (elementPoint == 0) || ( ! bAbsolute &&
			(elementPoint == 2) && (cType == 'u') ) ){
		//insert for the (first) underobject of this Fib element
		
		//check if the underobject to overwrite is NULL
		if ( pUnderObject == NULL ){
		
			//set the values of the fibElement
#ifdef FEATURE_FAST_UPDATE
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			fibObject->pSuperiorElement = this;
#else //FEATURE_FAST_UPDATE
			fibObject->pSuperiorElement = this;
			fibObject->pPreviousFibElement = this;
#endif //FEATURE_FAST_UPDATE
			
			pUnderObject = fibObject;
			
			updateAllValues();
			
			return true;
		}//else
		
		/*create a listelement and insert the old underobejct and the new into it*/
		cFibElement * pOldUnderObject = pUnderObject;
#ifdef FEATURE_FAST_UPDATE
			if ( fibObject->pSuperiorElement != NULL ){
				fibObject->pSuperiorElement->cutConnectionsTo(
					fibObject );
			}
			pOldUnderObject->pSuperiorElement = NULL;
#endif //FEATURE_FAST_UPDATE
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
		if( first ){
			pUnderObject = new cList( fibObject, pOldUnderObject );
		}else{
			pUnderObject = new cList( pOldUnderObject, fibObject );
		}
#else //FEATURE_SIMPLE_CONSTRUCTOR
		if( first ){
			pUnderObject = new cList( fibObject, pOldUnderObject, this, this );
		}else{
			pUnderObject = new cList( pOldUnderObject, fibObject, this, this );
		}
#endif //FEATURE_SIMPLE_CONSTRUCTOR
#ifdef FEATURE_FAST_UPDATE
		//set superior Fib element
		pUnderObject->pSuperiorElement = this;
		pOldUnderObject->pSuperiorElement = pUnderObject;
		fibObject->pSuperiorElement = pUnderObject;
#endif //FEATURE_FAST_UPDATE
		updateAllValues();
		//done with inserting
		return true;
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

#endif //FEATURE_INSERT_OBJECT_IN_ELEMENT


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
bool cFibLimb::overwriteObjectWithObject( cFibElement * pFibObject,
		const char cType, const unsignedIntFib elementPoint, bool bDeleteOld,
		bool bAbsolute ){
	
	if ( pFibObject == NULL ){
		//nothing to insert
		return false;
	}
	
	if ( elementPoint == 0 ){
		//insert for the (first) underobject of this Fib element
		return overwriteObjectWithObject( pFibObject, 'u', 2, bDeleteOld );
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->overwriteObjectWithObject( pFibObject, cType,
			elementPoint, bDeleteOld );
	}//else elementPoint is an relative value

	/*check ( if (cType=='u') ) if the pFibObject should inserted as an
	neibour of an underobject of this object*/
	if ( (elementPoint == 2) && (cType == 'u') ){
	
		if ( pFibObject->getType() == 'r' ){
			//insert a root -element into a limb element
			return false;
		}
		
		//set the values of the fibElement
#ifdef FEATURE_FAST_UPDATE
		if ( ( pUnderObject != NULL ) &&
				( pUnderObject->pSuperiorElement == this ) ){
			pUnderObject->pSuperiorElement = NULL;
			if ( bDeleteOld && (pUnderObject != NULL) ){
				pUnderObject->deleteObject();
			}//else don't delete
		}
		pUnderObject = pFibObject;
		if ( pUnderObject->pSuperiorElement != NULL ){
			pUnderObject->pSuperiorElement->cutConnectionsTo(
				pUnderObject );
		}
		pUnderObject->pSuperiorElement = this;
#else //FEATURE_FAST_UPDATE
		pFibObject->pSuperiorElement    = this;
		pFibObject->pPreviousFibElement = this;
		
		//check if the underobject to overwrite is NULL
		if ( pUnderObject == NULL ){
		
			pUnderObject = pFibObject;
			
			updateAllValues();
			
			return true;
		}//else
		
		cFibElement * pOldFibObject = pUnderObject;
		pUnderObject = pFibObject;
		
		//remove connections of pOldFibObject to this Fib object
		cFibElement * pLastFibElementInOld = pOldFibObject->getFibElement(
				pOldFibObject->getNumberOfElements() );
		if ( pLastFibElementInOld == NULL ){
			pLastFibElementInOld = pOldFibObject;
		}
		
		pOldFibObject->cutConnections( ED_HIGHER );
		pLastFibElementInOld->cutConnections( ED_BELOW );
		
		if ( bDeleteOld ){
			cFibElement::deleteObject( pOldFibObject );
		}//else don't delete
#endif //FEATURE_FAST_UPDATE
		
		updateAllValues();
		//done and fibElement inserted
		return true;
	}
	
	/*get the pSuperiorElement of the to insering objectposition and call
	insertElement of theas*/
	cFibElement *pFibElementPosition = getFibElement( cType, elementPoint );
	if ( (pFibElementPosition != NULL) &&
			(pFibElementPosition->pSuperiorElement != NULL) ){
			
			return pFibElementPosition->pSuperiorElement->overwriteObjectWithObject(
				pFibObject, 'u', 1 + (pFibElementPosition->getNumberOfElement()) -
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
bool cFibLimb::removeObject( const unsignedIntFib objectPoint,
		bool bDeleteOld, bool bAbsolute ){
	
	if ( bAbsolute ){
		return getMasterRoot()->removeObject( objectPoint, bDeleteOld );
	}//else elementPoint is an relative value
	
	if ( pUnderObject ){
		//go to the next branch Fib element
		return pUnderObject->removeObject( objectPoint, bDeleteOld );
	}//else no such objectpoint
	return false;
}

/**
 * This method checks, if all Fib elements of this Fib object
 * have the subobjects they need to be correct.
 *
 * @return true if all Fib elements of this Fib object have the
 * 	subobjects they need to be correct, else false
 */
bool cFibLimb::hasUnderAllObjects() const{
	
	if ( pUnderObject != NULL ){
		return pUnderObject->hasUnderAllObjects();
	}//else
	return false;
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
cFibElement *cFibLimb::cutElement( const char cType, const unsignedIntFib
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
	
	//check if the first element of the underobject should be removed
	if ( pUnderObject != NULL ){
		//no underobject
#ifdef FEATURE_FAST_UPDATE
		if ( pUnderObject == pFibElementToRemove ){
#else //FEATURE_FAST_UPDATE
		if ( pUnderObject->getNumberOfElement() ==
				pFibElementToRemove->getNumberOfElement() ){
#endif //FEATURE_FAST_UPDATE
			//Fib element to remove found
			
			if ( 1 < pFibElementToRemove->getNumberOfElements() ){
				//pFibElementToRemove has subobjects to replace it
				pUnderObject = pFibElementToRemove->getNextFibElement();
				
				if ( pUnderObject != NULL ){
					pUnderObject->pSuperiorElement = this;
#ifndef FEATURE_FAST_UPDATE
					pUnderObject->pPreviousFibElement = this;
#endif //FEATURE_FAST_UPDATE
				}
			}else{//pFibElementToRemove has no subobjects -> can't remove
				return NULL;
			}
			updateAllValues();
			
#ifdef FEATURE_FAST_UPDATE
			//clear values of cuted Fib element
			pFibElementToRemove->cutConnectionsTo( this );
			pFibElementToRemove->cutConnectionsTo(
				pFibElementToRemove->getNextFibElement() );
#else //FEATURE_FAST_UPDATE
			//clear values of cuted Fib element
			pFibElementToRemove->cutConnections( ED_ALL );
#endif //FEATURE_FAST_UPDATE

			return pFibElementToRemove;
		}
	}

	return pFibElementToRemove->pSuperiorElement->cutElement( 'u',
		pFibElementToRemove->getNumberOfElement() + 1 -
		pFibElementToRemove->pSuperiorElement->getNumberOfElement(),
		false, bCheckVariables );
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method deletes this given Fib object with all the fib
 * elements it contains and is contained in. The memory for the fib
 * -object is freed.
 */
void cFibLimb::deleteObject(){
	
	//delete the underobjetcts
	if ( pUnderObject ){
		pUnderObject->pSuperiorElement = NULL;
		pUnderObject->deleteObject();
		pUnderObject = NULL;
	}
	//delete this Fib element
	delete this;
}

#endif //FEATURE_FAST_UPDATE


/**
	* @return true if this Fib element is movebel else false
	*/
bool cFibLimb::isMovable() const{
	return true;
}


/**
 * This method moves a Fib-limb -element (cFibLimb) on the specified
 * position over iHowfar Fib elements.
 * Moving is stoped if an invalid Fib object would result (e.g. no Fib
 * -element can be moved over an Fib elements that defines a variable
 * the moved Fib element uses).
 * Moving an Fib element into an listelement will result in an
 * listelement with the moved element in everyone of it's subobjects.
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
 * @return the number of Fib-Elements over which the to move Fib
 * 	-element was moved; if this value is positiv the Fib element
 * 	was moved over Fib elements it contains else over Fib elements
 * 	it is contained in
 */
intFib cFibLimb::moveLimbElement( const char cType, const unsignedIntFib
		elementPoint, const intFib iHowfar, bool bAbsolute ){
	
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
		if ( pSuperiorElement->getNumberOfElement() ==
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
			/*else move the to move element into the underobject*/
			pFibElementToMove = cutElement( cType, elementPoint, bAbsolute, false );
			if ( pFibElementToMove == NULL ){
				//can't move the pFibElementToMove
				return 0;
			}
			
			//move the Fib element further down
			if ( pUnderObject != NULL ){
				insertElement( pFibElementToMove, 'u',
					pUnderObject->getNumberOfElement() - getNumberOfElement() + 1,
					false, false );
			}else{
				insertElement( pFibElementToMove, 'u', 0, false, false );
			}
			
			cFibElement * pNextMoveFibElement = pFibElementToMove->getNextFibElement();
			if ( pNextMoveFibElement ){
				//move next step down
				return pNextMoveFibElement->moveLimbElement( 'u',
					pFibElementToMove->getNumberOfElement(), iHowfar - 1, true ) + 1;
			}else{//can't move down further
				return 1;
			}
		}
	}/*else get the underobject of the to move Fib element and call moveLimbElement from ther*/
	cFibElement * pNextMoveFibElement = pFibElementToMove->getNextFibElement();
	if ( pNextMoveFibElement == NULL ){
		//no next fib element -> nothing to move over
		return 0;
	}
	return pNextMoveFibElement->moveLimbElement( 'u',
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
bool cFibLimb::equalInternal( const cFibElement & fibObject,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	
	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	//compare the subobjects
	cFibLimb * pOtherLimb = (cFibLimb *)(&fibObject);
	
	if ( (pUnderObject == NULL) || (pOtherLimb->pUnderObject == NULL) ){
		if ( pUnderObject == pOtherLimb->pUnderObject ){
			//not both subobjects are 0 subobjects
			return true;
		}//else pointers not both NULL
		return false;
	}//else compare the subobjects
	return pUnderObject->equalInternal( *(pOtherLimb->pUnderObject),
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
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
bool cFibLimb::equal( const cFibElement & fibObject ) const{
	
	if ( getType() != fibObject.getType() ){
		//not the same element type
		return false;
	}
	//compare the subobjects
	cFibLimb * pOtherLimb = (cFibLimb *)(&fibObject);
	
	if ( (pUnderObject == NULL) || (pOtherLimb->pUnderObject == NULL) ){
		if ( pUnderObject == pOtherLimb->pUnderObject ){
			//not both subobjects are 0 subobjects
			return true;
		}//else pointers not both NULL
		return false;
	}//else compare the subobjects
	return pUnderObject->equal( *(pOtherLimb->pUnderObject) );
}

#endif //FEATURE_EQUAL_FIB_OBJECT


/**
 * @return this method returns true if this Fib element is an
 * 	limbelement, alse false
 */
bool cFibLimb::isLimb() const{
	return true;
}



#ifndef FEATURE_NO_REGISTER_NEW_FIB_

/**
 * With this method a new Fib element in the Fib-Object is registert
 * by the other Fib elements in the Fib-Object.
 *
 * @param newFibElement the new Fib element to register
 * @param uINumberOfFibElement the number of the new Fib element in the
 * 	order of all Fib-Elements in the Fib object
 * @param bDirectionUp the direction in which the registration of the
 * 	new Fib element is performed in the Fib object tree;
 * 	from the position on which the new Fib-Element is added the
 * 	method is called for both directions
 * @return true if the registration was successfull, else false
 */
bool cFibLimb::registerNewFibElement( cFibElement *newFibElement,
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

	}else{
		//register in direction below

		if ( pUnderObject != NULL ){
			pUnderObject->registerNewFibElement( newFibElement,
				uINumberOfFibElement, false );
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
	if ( this->uINumberOfFibElement == uINumberOfFibElement + 1 ){
		//this Fib element is the next Fib element to the new Fib element
		pPreviousFibElement = newFibElement;
	}
	
	//update pNextFibElement
	if ( this->uINumberOfFibElement == uINumberOfFibElement - 1 ){
		//the new Fib element is the next Fib element to this Fib element
		pNextFibElement = newFibElement;
	}
	return true;
}


/**
 * With this method a new part Fib object in the Fib-Object is
 * registert by the other Fib elements in the Fib-Object.
 *
 * @param newFibObject the new part Fib object to register
 * @param uILowerNumberOfFibElements the number of the Fib element in the
 * 	new part Fib object with the lowest number in the order of all
 * 	Fib-Elements in the entire Fib object
 * @param uIUpperNumberOfFibElements the number of the Fib element in the
 * 	new part Fib object with the highest number in the order of all
 * 	Fib-Elements in the entire Fib object
 * @param bDirectionUp the direction in which the registration of the
 * 	new part Fib object is performed in the Fib object tree;
 * @return true if the registration was successfull, else false
 */
bool cFibLimb::registerNewFibObject( cFibElement *newFibObject,
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
	}else{
		//register in direction below
		if ( pUnderObject != NULL ){
			pUnderObject->registerNewFibObject( newFibObject,
				uILowerNumberOfFibElements, uIUpperNumberOfFibElements, false );
		}
	}
	
	//update the position of this Fib element in order of Fib elements
	if ( this->uINumberOfFibElement >= uINumberOfFibElement ){
		/*add 1 to the number of this fib element in the order of
		Fib elements, because the new Fib element was added in
		order of Fib elements befor it*/
		this->uINumberOfFibElement = this->uINumberOfFibElement +
			( uIUpperNumberOfFibElements - uILowerNumberOfFibElements + 1);
	}
	bool bReturnValue = true;
	
	//update pPreviousFibElement
	if ( this->uINumberOfFibElement == uIUpperNumberOfFibElements + 1 ){
		/*the last Fib element in the new Fib-Object is the previous
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
		/*the first Fib element in the new Fib-Object is the next
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
void cFibLimb::cutConnectionsTo( const cFibElement * pFibElement ){
	
	cFibElement::cutConnectionsTo( pFibElement );
	
	if ( ( pFibElement != NULL ) && ( pUnderObject == pFibElement ) ){
		//cut connections to the underobject
		pUnderObject = NULL;
		updateAllValues();
	}
}

#else //FEATURE_FAST_UPDATE

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
cFibElement * cFibLimb::updateValues( cFibElement * previosFibElement,
		cFibElement * pNextArm ){

	cFibElement * pLastFibElementUpdated = NULL;
	
	//this Fib element is the superior of it's underobject
	if ( pUnderObject != NULL ){
		pUnderObject->pSuperiorElement = this;
		pNextFibElement = pUnderObject;
	}else{//this limbelement has no underobject
		pNextFibElement = pNextArm;
	}
	pLastFibElementUpdated = cFibElement::updateValues( previosFibElement, pNextArm );
	if ( pLastFibElementUpdated == NULL ){
		//something gone wrong while updating
		return NULL;
	}
	
	//update subobjects if existing
	if ( pUnderObject != NULL ){
		pLastFibElementUpdated = pUnderObject->updateValues(
			pLastFibElementUpdated, pNextArm );
	}
	return pLastFibElementUpdated;
}

/**
 * This method cuts the connections of this Fib element to other
 * Fib elements.
 *
 * @param direction the direction into which the connections are to be
 * 	cutted
 * 	ED_HIGHER, ED_HIGHER_EQUAL, ED_ALL: will cut the conection to
 * 		superior and previous Fib elements
 * 	ED_BELOW, ED_BELOW_EQUAL, ED_ALL: will cut the conection to
 * 		next- Fib element and the subobjects
 */
void cFibLimb::cutConnections( edDirection direction ){
	
	cFibElement::cutConnections( direction );
	pUnderObject = NULL;
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
unsignedIntFib cFibLimb::enumerateVariablesForStoring(
		unsignedIntFib uiLastVariableNumber ){
	
	if ( pUnderObject != NULL ){
		return pUnderObject->enumerateVariablesForStoring( uiLastVariableNumber );
	}
	return uiLastVariableNumber;
}





















