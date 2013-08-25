/**
 * @class cFibElement
 * file name: cFibElement.h
 * @author Betti Oesterholz
 * @date 05.08.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This class represents a basic Fib element.
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
 * This file contains the basisclass of all Fib elements. It's not
 * possible to create instances from this class.
 * The Fib elements are the elements of the Fib multimedialanguage.
 * The class cFibElement defines methods to change the structur of an
 * Fib object/-tree.
 *
 * If the structur of the Fib object is changed just set the underobjects
 * and call updateAllValues() from a position wher the highest Fib element
 * can be reached. The updateAllValues()  method will make the conections.
 * If you remove conections you have to be more carefull.
 *
 */
/*
History:
05.08.2009  Oesterholz  created
19.12.2009  Oesterholz  updateValues() and updateAllValues() changed
18.04.2010  Oesterholz  evalueObject() methods changed: not a function but
	an object is given to evalue the data
14.03.2011  Oesterholz  getNextFibElement() const added
23.05.2011  Oesterholz  restore* cIf added
07.08.2011  Oesterholz  isDefinedVariable() and getDefinedVariables() with
	pCallingFibElement implemented
20.08.2011  Oesterholz  cExtObject and restoreBit() NULL added
19.10.2011  Oesterholz  FEATURE_EQUAL_FIB_OBJECT implemented
30.11.2011  Oesterholz  cFibDatabase inserted ( getAllDatabaseObjectIdentifiers() )
11.12.2011  Oesterholz  cFibSet added 
11.12.2011  Oesterholz  cFibMatrix added and changes for cArea, which uses
	now a domain for the number of subareas
11.12.2011  Oesterholz  restoreXmlInternal(): restore next XML element till
	Fib element was read or error occured
16.01.2013  Oesterholz  FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	implemented: if no root object exists to retrieve external objects
	-> search the Fib database
16.08.2013  Oesterholz  method getVariablesToReplace() added
*/


//TODO switches for test proposes
//#define DEBUG


#include "cFibElement.h"
#include "cRoot.h"
#include "cPoint.h"
#include "cList.h"
#include "cProperty.h"
#include "cArea.h"
#include "cFunction.h"
#include "cIf.h"
#include "cComment.h"
#include "cExtObject.h"
#include "cExtSubobject.h"
#include "cFibSet.h"
#include "cFibMatrix.h"
#include "cFibDatabase.h"


#include "cVectorPosition.h"
#include "cFibVariable.h"

#include <algorithm>


using namespace fib;


#ifdef FEATURE_SIMPLE_CONSTRUCTOR

/**
 * parameterconstructor
 *
 * @param pInSuperiorElement the Fib Element in which this Fib element
 * 	is the underobject
 */
cFibElement::cFibElement( cFibElement * pInSuperiorElement ):
		pSuperiorElement( pInSuperiorElement )
#ifndef FEATURE_FAST_UPDATE
		,pPreviousFibElement( NULL ),
		pNextFibElement( NULL ),
		pNextRootElement( NULL )
#endif //FEATURE_FAST_UPDATE
		{
	//nothing to do
}

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
 */
cFibElement::cFibElement( cFibElement * pInSuperiorElement, cFibElement * pInPreviousFibElement,
		cFibElement * pInNextFibElement ):
		pSuperiorElement( pInSuperiorElement ),
		pPreviousFibElement( pInPreviousFibElement ),
		pNextFibElement( pInNextFibElement ),
		pNextRootElement( NULL ){

	if ( (pSuperiorElement != NULL) && (pPreviousFibElement == NULL) ){
		/*find pPreviousFibElement, which is the last Fib element in the
		order of Fib elements which is below this Fib element*/
		pPreviousFibElement = pSuperiorElement;
		
		while ( (pPreviousFibElement->getNextFibElement() != NULL) &&
				 (pPreviousFibElement->getNextFibElement() != this) ){
		
			pPreviousFibElement = pPreviousFibElement->getNextFibElement();
		}
	}
	if ( pPreviousFibElement ){
		pPreviousFibElement->pNextFibElement = this;
	}
	if ( pSuperiorElement == this ){
		//this element can't be it's own superior
		pSuperiorElement = NULL;
	}
	if ( pPreviousFibElement == this ){
		//this element can't be it's own previous Fib element
		pPreviousFibElement = NULL;
	}
	if ( pNextFibElement == this ){
		//this element can't be it's own next Fib element
		pNextFibElement = NULL;
	}

	uINumberOfFibElement = 1;
	
	cFibElement * actualFibElement = pPreviousFibElement;
	
	//go troug all previous Fib elements
	while ( actualFibElement != NULL ){
		/*count the number of Fib elements befor this Fib element to get
		the number this Fib element has in the order of all Fib elements*/
		uINumberOfFibElement++;
		
		/*set the next root element to the first found Fib element in the
		previous Fib elements*/
		if ( (pNextRootElement == NULL) && (actualFibElement->getType() == 'r') ){
			pNextRootElement = (cRoot*)actualFibElement;
		}
		/*go to previous Fib element*/
		actualFibElement = actualFibElement->pPreviousFibElement;
	}
}

#endif //FEATURE_SIMPLE_CONSTRUCTOR

/**
 * copyconstructor
 * This copyconstructor constructs a copy of of the given Fib Element.
 * It dosn't copy other Fib elements than the given, even if ther are
 * in the Fib element.
 *
 * @param fibElement the Fib element to copy
 */
cFibElement::cFibElement( const cFibElement &fibElement ):
		pSuperiorElement( NULL )
#ifndef FEATURE_FAST_UPDATE
		, pPreviousFibElement( NULL ),
		pNextFibElement( NULL ),
		pNextRootElement( NULL ),
		uINumberOfFibElement( 1 )
#endif //FEATURE_FAST_UPDATE
		{
//nothing to do
}

/**
 * desstructor
 */
cFibElement::~cFibElement(){

	if ( pSuperiorElement != NULL ){
		//incorrect underobject
		pSuperiorElement->cutConnectionsTo( this );
	}
	pSuperiorElement     = NULL;
#ifndef FEATURE_FAST_UPDATE
	pPreviousFibElement  = NULL;
	pNextFibElement      = NULL;
	pNextRootElement     = NULL;
	uINumberOfFibElement = 0;
#endif //FEATURE_FAST_UPDATE
}



/**
 * This function converts a element type character into a string with 
 * the element name.
 *
 * @see getTyp
 * @param cType a character for the type of a Fib element, like the
 *		getTyp() returns it
 * @return a string with the name of the Fib element for the given character
 */
string cFibElement::getTypeName( char cType ){

	switch ( cType ){
		case 'u': return "unknown";
		case 'p': return "point";
		case 'l': return "list element";
		case 'y': return "property";
		case 'c': return "comment";
		case 'a': return "area";
		case 'f': return "function";
		case 'i': return "if";
		case 'o': return "extern object";
		case 's': return "extern subobject";
		case 'v': return "set-element";
		case 'm': return "matrix element";
		case 'r': return "root";
	}
	return "unknown";
}


/**
 * This method returns the superior Fib element of this Fib element.
 *
 * @return the superior Fib element of this Fib element or the NULL 
 * 	pointer, if non such exists
 */
cFibElement * cFibElement::getSuperiorFibElement(){
	return pSuperiorElement;
}


/**
 * This method returns the next Fib element in the order of Fib elements.
 *
 * @return a pointer to the next Fib element in the order of Fib elements
 * 	or the NULL pointer if non such exists
 */
const cFibElement * cFibElement::getNextFibElement() const{

	return const_cast< cFibElement* >(this)->getNextFibElement();
}


#ifndef FEATURE_FAST_UPDATE

/**
 * This method returns the next Fib element in the order of Fib elements.
 *
 * @return a pointer to the next Fib element in the order of Fib elements
 *		or the NULL pointer if non such exists
 */
cFibElement *cFibElement::getNextFibElement(){
	return pNextFibElement;
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
cFibElement *cFibElement::getNextFibElement( char cType ){

	if ( pNextFibElement == NULL ){
		//no next Fib element
		return NULL;
	}

	if (  (cType == 'u') || (pNextFibElement->getType() == cType) ){
		//next Fib element has the correct type
		return pNextFibElement;
	}//else

	return pNextFibElement->getNextFibElement( cType );
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements with the given type cTyp.
 *
 * @param lNumber the number of the Fib Element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements or the NULL pointer if non such exists
 */
cFibElement * cFibElement::getConstFibElement( longFib lNumber,
		bool bAbsolute ) const{

	DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) called"<<endl<<flush);

	if ( lNumber == 0 ){
		//this is the correct Fib element
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done lNumber is 0 returning this="<<this<<endl<<flush);
		return const_cast<cFibElement*>( this );
	}//else

#define BUGFIX_GET_FIB_ELEMENT_NON_RECURSIV

#ifdef BUGFIX_GET_FIB_ELEMENT_NON_RECURSIV
	if ( bAbsolute ){
		DEBUG_OUT_L2(<<"searching absolute"<<endl<<flush);
		//lNumber is an absolute value
		unsignedIntFib ulNumberOfThisElement = getNumberOfElement();
		if ( lNumber == ulNumberOfThisElement ){
			//element found
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done returning this="<<this<<endl<<flush);
			return const_cast<cFibElement*>( this );
		}else if ( lNumber < ulNumberOfThisElement ){
			//Fib element is an previouse Fib element
			const cFibElement * pActualPrevElement = NULL;
			for ( pActualPrevElement = pPreviousFibElement;
					(pActualPrevElement != NULL) &&
					( lNumber < pActualPrevElement->getNumberOfElement() );
					pActualPrevElement = pActualPrevElement->pPreviousFibElement ){
				//nothing to do
			}
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pPreviousFibElement found: "<<pActualPrevElement<<")"<<endl<<flush);
			return const_cast<cFibElement*>( pActualPrevElement );
		}//else (ulNumberOfThisElement < lNumber)
		//Fib element is an next Fib element
		const cFibElement * pActualNextElement = NULL;
		for ( pActualNextElement = pNextFibElement;
				(pActualNextElement != NULL) &&
				( pActualNextElement->getNumberOfElement() < lNumber );
				pActualNextElement = pActualNextElement->pNextFibElement ){
			//nothing to do
		}
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pNextFibElement found: "<<pActualNextElement<<")"<<endl<<flush);
		return const_cast<cFibElement*>( pActualNextElement );
	}//lNumber is an relative value
	DEBUG_OUT_L2(<<"searching not absolute"<<endl<<flush);
	
	if ( 0 < lNumber ){
		//search the next Fib elements
		const cFibElement * pActualNextElement = NULL;
		for ( pActualNextElement = this;
				(pActualNextElement != NULL) && ( 1 < lNumber );
				pActualNextElement = pActualNextElement->pNextFibElement, lNumber-- ){
			//nothing to do
		}
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pNextFibElement found: "<<pActualNextElement<<")"<<endl<<flush);
		return const_cast<cFibElement*>( pActualNextElement );
	}

	const cFibElement * pActualPrevElement = NULL;
	for ( pActualPrevElement = pPreviousFibElement;
			(pActualPrevElement != NULL) && ( lNumber < -1 );
			pActualPrevElement = pActualPrevElement->pPreviousFibElement, lNumber++ ){
		//nothing to do
	}
	DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pPreviousFibElement found: "<<pActualPrevElement<<")"<<endl<<flush);
	return const_cast<cFibElement*>( pActualPrevElement );

#else
	
	if ( bAbsolute ){
		DEBUG_OUT_L2(<<"searching absolute"<<endl<<flush);
		//lNumber is an absolute value
		unsignedIntFib ulNumberOfThisElement = getNumberOfElement();
		if ( lNumber == ulNumberOfThisElement ){
			//element found
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done returning this="<<this<<endl<<flush);
			return const_cast<cFibElement*>( this );
		}else if ( lNumber < ulNumberOfThisElement ){
			//Fib element is an previouse Fib element
			if ( pPreviousFibElement ){
				DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pPreviousFibElement (Type="<<flush<<pNextFibElement->getType()<<")"<<endl<<flush);
				return pPreviousFibElement->getConstFibElement( lNumber, true );
			}//else no such fib element
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done direction pPreviousFibElement is NULL"<<endl<<flush);
			return NULL;
		}//else ulNumberOfThisElement<lNumber
		//Fib element is an next Fib element
		if ( pNextFibElement ){
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pNextFibElement (Type="<<flush<<pNextFibElement->getType()<<")"<<endl<<flush);
			return pNextFibElement->getConstFibElement( lNumber, true );
		}//else no such fib element
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done direction pNextFibElement is NULL"<<endl<<flush);
		return NULL;
	}//lNumber is an relative value
	DEBUG_OUT_L2(<<"searching not absolute"<<endl<<flush);

	if ( (lNumber == 0) || (lNumber == 1) ){
		//this is the correct Fib element
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done returning this="<<this<<endl<<flush);
		return const_cast<cFibElement*>( this );
	}//else
	
	if ( 1 < lNumber ){
		//search the next Fib elements
		if ( pNextFibElement == NULL ){
			//no next Fib element
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done direction pNextFibElement is NULL"<<endl<<flush);
			return NULL;
		}//else
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pNextFibElement (Type="<<flush<<pNextFibElement->getType()<<")"<<endl<<flush);
		return pNextFibElement->getConstFibElement( --lNumber );
	}//else
	
	if ( lNumber < 0 ){
		//search the previous Fib elements
		if ( pPreviousFibElement == NULL ){
			//no previous Fib element
			DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done direction pPreviousFibElement is NULL"<<endl<<flush);
			return NULL;
		}//else
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pPreviousFibElement (Type="<<flush<<pNextFibElement->getType()<<")"<<endl<<flush);
		return pPreviousFibElement->getConstFibElement( ++lNumber );
	}
#endif
	DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done unreachable"<<endl<<flush);
	//unreachable
	return NULL;
}



/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements of the given type cTyp with the given type cTyp.
 *
 * @param lNumber the number of the Fib element to return
 * @param cType the type of the Fib element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements with the given type or the NULL pointer if non such
 * 	exists
 */
cFibElement *cFibElement::getConstFibElement( char cType, longFib lNumber,
		bool bAbsolute ) const{

	if ( lNumber == 0 ){
		//this is the correct Fib element
		return const_cast<cFibElement*>( this );
	}//else
	if ( cType == 'u' ){
		//return of all types
		return getConstFibElement( lNumber, bAbsolute );
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->getConstFibElement( cType, lNumber );
	}//else lNumber is an relative value
	
	if ( ( lNumber == 1 ) &&
			(getType() == cType) ){
		//this is the Fib element to return
		return const_cast<cFibElement*>( this );
	}
#ifdef BUGFIX_GET_FIB_ELEMENT_NON_RECURSIV
	
	if ( 0 < lNumber ){
		//search the next Fib elements
		const cFibElement * pActualNextElement = NULL;
		for ( pActualNextElement = this;
				(pActualNextElement != NULL) && ( 0 < lNumber );
				pActualNextElement = pActualNextElement->pNextFibElement ){
			
			if ( pActualNextElement->getType() == cType ){
				lNumber--;
				if ( lNumber == 0 ){
					break;
				}
			}
		}
		DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pNextFibElement found: "<<pActualNextElement<<")"<<endl<<flush);
		return const_cast<cFibElement*>( pActualNextElement );
	}

	const cFibElement * pActualPrevElement = NULL;
	for ( pActualPrevElement = pPreviousFibElement;
			(pActualPrevElement != NULL) && ( lNumber < 0 );
			pActualPrevElement = pActualPrevElement->pPreviousFibElement ){
		
		if ( pActualPrevElement->getType() == cType ){
			lNumber++;
			if ( lNumber == 0 ){
				break;
			}
		}
	}
	DEBUG_OUT_L2(<<"cFibElement::getConstFibElement( "<<lNumber<<", "<<bAbsolute<<" ) done go in direction pPreviousFibElement found: "<<pActualPrevElement<<")"<<endl<<flush);
	return const_cast<cFibElement*>( pActualPrevElement );

#else
	if ( lNumber > 0 ){
		//search the next Fib elements
		if ( pNextFibElement == NULL ){
			//no next Fib element
			return NULL;
		}//else
		if ( getType() == cType ){
			return pNextFibElement->getConstFibElement( cType, --lNumber );
		}else{
			return pNextFibElement->getConstFibElement( cType, lNumber );
		}
	}
	
	if ( lNumber < 0 ){
		//search the previous Fib elements
		if ( pPreviousFibElement == NULL ){
			//no previous Fib element
			return NULL;
		}//else
		if ( pPreviousFibElement->getType() == cType ){
			return pPreviousFibElement->getConstFibElement( cType, ++lNumber );
		}else{
			return pPreviousFibElement->getConstFibElement( cType, lNumber );
		}
	}
#endif
	//unreachable
	return NULL;
}

#endif //FEATURE_FAST_UPDATE

/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements with the given type cTyp.
 *
 * @param lNumber the number of the Fib Element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements or the NULL pointer if non such exists
 */
cFibElement * cFibElement::getFibElement( longFib lNumber,
		bool bAbsolute ){
	
	return getConstFibElement( lNumber, bAbsolute );
}


/**
 * This method returns the lNumber'th Fib element in the order of
 * Fib elements of the given type cTyp with the given type cTyp.
 *
 * @param lNumber the number of the Fib element to return
 * @param cType the type of the Fib element to return
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a pointer to the lNumber'th Fib element in the order of
 * 	Fib elements with the given type or the NULL pointer if non such
 * 	exists
 */
cFibElement * cFibElement::getFibElement( char cType, longFib lNumber,
		bool bAbsolute ){
	
	return getConstFibElement( cType, lNumber, bAbsolute );
}


/**
 * This method returns a number of (lNumberOfMaxReturnedElements)
 * Fib elements beginning from the reference Fib element in the
 * given direction of the given type cType.
 *
 * @param cTypeBasis the type of the reference Fib element
 * @param lNumber the number of the reference Fib element to return
 * @param cType the type of the Fib elements to return;
 * 	'w' stands for wrong/ not correct Fib elements
 * @param direction the direction, beginning from the reference 
 * 	Fib element, in which the to return Fib elements should stand
 * @param lNumberOfMaxReturnedElements the maximal number of 
 * 	Fib elements to return
 * @return a list with the pointers to the to returning Fib elements
 */
list<cFibElement*> cFibElement::getAllFibElements( char cTypeBasis,
		longFib lNumber, char cType, edDirection direction,
		unsignedLongFib lNumberOfMaxReturnedElements, bool bAbsolute ){
	
	if ( bAbsolute ){
		return getMasterRoot()->getAllFibElements( cTypeBasis, lNumber, cType,
			direction, lNumberOfMaxReturnedElements );
	}//else lNumber is an relative value

	//get the reference Fib element
	cFibElement* pRefernceElement = getFibElement( cTypeBasis, lNumber );
	
	if ( pRefernceElement == NULL ){
		//no reference element
		return list<cFibElement*>();
	}
	
	if ( (cType == 'u') || (pRefernceElement->getType() == cType) ){
		//pRefernceElement element has the correct type
		if ( (direction == ED_ALL) || (direction == ED_POSITION)
				|| (direction == ED_BELOW_EQUAL) || (direction == ED_HIGHER_EQUAL) ){
			/*if the direction is ED_ALL, ED_POSITION, ED_BELOW_EQUAL or
			ED_HIGHER_EQUAL add the referenc element to the list, if it
			has the correct type*/
			list<cFibElement*> liFoundedElements;
			bool bFindMoreFibElements = true;
			if ( lNumberOfMaxReturnedElements != 0 ){
				//the referenc element will be added
				lNumberOfMaxReturnedElements--;
				if ( lNumberOfMaxReturnedElements == 0 ){
					bFindMoreFibElements = false;
				}
			}
			
			if ( (direction != ED_POSITION) && bFindMoreFibElements ){
				liFoundedElements = pRefernceElement->getAllFibElementsFromPosition(
					cType, direction, lNumberOfMaxReturnedElements );
			}//else yust give back the referenc element
			
			liFoundedElements.push_front( pRefernceElement );
			return liFoundedElements;

		}
	}//else pRefernceElement has not the correct type -> don't add it
	if ( direction != ED_POSITION){
		return pRefernceElement->getAllFibElementsFromPosition(
			cType, direction, lNumberOfMaxReturnedElements );
	}//else direction == ED_POSITION ->done
	return list<cFibElement*>();
}


/**
 * This method evaluades the Fib object.
 *
 * @param evaluePosition a reference to the object with the
 * 	evaluePosition() method to evalue /store the positions and ther
 * 	properties; everytime a point (to evalue) is reached in the
 * 	evaluation, this method is called with the position and the
 * 	properties of the point; @see iEvaluePosition
 * @param objectPoint the object point in the order of true partobjects
 *		to evalue
 * @return if the evalueation was successfull true, else false
 */
bool cFibElement::evalueObjectSimple( iEvaluePosition & evaluePosition,
		const unsignedIntFib objectPoint ) const{
	
	list<cVectorProperty> liPropertyList;
	return evalueObject( evaluePosition, objectPoint, liPropertyList );
}

/**
 * This method evaluades the Fib object.
 * Evertime a Fib elements, with a type of the given type chars in
 * liCFibElementTyps, is reached while evaluation, it is given
 * back with the properties which it has.
 * Ever pointelement is given back. The type chars for pointelements
 * don't need to be in the list liCFibElementTyps.
 *
 * @param evalueFibElement a reference to the object with the
 * 	evalueElement() method to evalue /store the Fib elements and ther
 * 	properties; everytime a Fib element (with one of the type given
 * 	in liCFibElementTyps) is reached in the evaluation, the method
 * 	evalueElement() of this objects is called with the Fib element
 * 	and the properties of the Fib element; @see iEvalueFibElement
 * @param objectPoint the object point in the order of true partobjects
 *		to evalue
 * @param liCFibElementTyps a list with the type chars (@see getType)
 * 	of the Fib elements to return
 * @return if the evalueation was successfull true, else false
 */
bool cFibElement::evalueObjectSimple( iEvalueFibElement & evalueFibElement,
		const unsignedIntFib objectPoint,
		const list<char> liCFibElementTyps ){
	
	list<cVectorProperty> liPropertyList;
	return evalueObject( evalueFibElement, objectPoint, liPropertyList,
		liCFibElementTyps );
}


/** This method checks if the given variable is defined in the given
 * direction from this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param variable the variable to check if it is defined
 * @param direction the direction from this Fib element, in which the
 * 	variable should be defined; standardvalue is ED_POSITION so yust
 * 	this Fib element will be checked
 * @return true if the variable is defined, else false
 */
bool cFibElement::isDefinedVariable( const cFibVariable *variable ,
		edDirection direction ) const{
	
	return isDefinedVariableInternal( variable, direction );
}


/**
 * This method returns all variables defined in the given direction from
 * this Fib element.
 *
 * @see cFibVariable
 * @see getUsedVariables()
 * @see isDefinedVariable()
 * @param direction the direction from this Fib element, in which the
 * 	variable should be defined; standardvalue is ED_HIGHER so yust
 * 	higher Fib elements will be checked
 * @return the set with all variables defined in the given direction from
 * 	this Fib element
 */
list<cFibVariable*> cFibElement::getDefinedVariables( edDirection direction ){
	
	return getDefinedVariablesInternal( direction );
}


/**
 * This method checks if the variables in the given variablelist are
 * defined in the given direction from this Fib element.
 *
 * @see cFibVariable
 * @see isUsedVariable()
 * @param liVariable the list with the  variable to check, if it is defined
 * @param direction the direction from this Fib element, in which the
 * 	variables should be defined; standardvalue is ED_HIGHER so yust
 * 	higher Fib elements will be checked
 * @return true if the variables is are all defined, else false
 */
bool cFibElement::variablesAreDefined( const set<cFibVariable*> & setVariable ,
	edDirection direction ) const{
	
	//check if the variables used in the to insert Fib element are defined higer

	if ( setVariable.empty() ){
		return true;
	}
	const list<cFibVariable*> liDefinedVariables =
		(const_cast<cFibElement*>(this))->getDefinedVariables( direction );

	for ( set<cFibVariable*>::const_iterator itrVariable = setVariable.begin();
			itrVariable != setVariable.end(); itrVariable++ ){
		
		const list<cFibVariable*>::const_iterator itrFoundedVariable = std::find(
			liDefinedVariables.begin(), liDefinedVariables.end(),
			(*itrVariable) );
		
		if ( itrFoundedVariable == liDefinedVariables.end() ){
			/*variable not found in the defined variables ->
			can't insert the Fib element*/
			return false;
		}
	}
	return true;
}


#ifdef FEATURE_FAST_UPDATE

/**
 * This method returns the number of the next connected object point
 * in the order of connected object points that conntains this Fib
 * element.
 *
 * @see getNumberOfObjectPoints()
 * @return the number of the next connected object point for this Fib 
 * 	element
 */
unsignedIntFib cFibElement::getNumberOfObjectPoint() const{
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getNumberOfObjectPointUp( this );
	}//else this is the beginning of the wool object
	return 0;
}



/**
 * This method converts the number of the elementPoint Fib element
 * of the type cType in this Fib object to the number it has in the
 * order of all Fib elements.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type the original Fib element has
 * @param elementPoint the number of the original Fib element in the
 * 	order of Fib elements of the type cType
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return the number of the elementPoint Fib element of the type
 * 	cType in this Fib object has in the order of all Fib elements
 */
unsignedIntFib cFibElement::typeElementPointToElementPoint( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		return 1;
	}
	const cFibElement * pFibElement =
		getConstFibElement( cType, elementPoint, bAbsolute );
	
	if ( pFibElement == NULL ){
		return 0;
	}
	if ( bAbsolute ){
		return pFibElement->getNumberOfElement();
	}//else lNumber is an relative value
	return pFibElement->getNumberOfElement() - getNumberOfElement() + 1;
}


/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element of the type cType.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param cType the type the Fib element has
 * @param elementPoint the number of the Fib element in the order of
 * 	Fib elements of the type cType
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibElement::elementPointToObjectPoints( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibElement::elementPointToObjectPoints("<<cType<<", "<<elementPoint<<", "<<bAbsolute<<") started"<<endl<<flush);
	
	const cFibElement * pActualElement = this;
	
	if ( bAbsolute ){
		pActualElement = getMasterRoot();
	}//else lNumber is an relative value
	
	DEBUG_OUT_L2(<<"actual fib element: "<<pActualElement<<endl<<flush);
	if ( elementPoint <= pActualElement->getNumberOfElements( cType ) ){
		
		DEBUG_OUT_L2(<<"evaluing reference Fib object "<<endl<<flush);
		const cFibElement * pRefernceElement = pActualElement->
			getConstFibElement( cType, elementPoint );
		
		if ( ( pRefernceElement != NULL ) && (pRefernceElement != pActualElement) &&
				( pRefernceElement->pSuperiorElement != NULL ) ){
			DEBUG_OUT_L2(<<"cFibElement::elementPointToObjectPointsUp("<<cType<<", "<<elementPoint<<", "<<bAbsolute<<") done"<<endl<<flush);
			return pRefernceElement->pSuperiorElement->elementPointToObjectPointsUp(
				pRefernceElement, pActualElement );
		}//else no reference Fib element
	}//else the choosen Fib element is no Fib element under this
	DEBUG_OUT_L2(<<"cFibElement::elementPointToObjectPoints("<<cType<<", "<<elementPoint<<", "<<bAbsolute<<") done; no reference fib element"<<endl<<flush);
	return list<unsignedIntFib>();
}


/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element of the type cType.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param pRefernceElement the Fib element for which the object points
 * 	are to evalue
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibElement::getObjectPointsForElement(
		const cFibElement * pRefernceElement, bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibElement::getObjectPointsForElement("<<pRefernceElement<<", "<<bAbsolute<<") started"<<endl<<flush);
	
	if ( pRefernceElement == NULL ){
		//no Fib element -> no object points
		return list<unsignedIntFib>();
	}
	cFibElement * pActualElement = const_cast<cFibElement *>( this );
	
	if ( bAbsolute ){
		pActualElement = getMasterRoot();
	}//else lNumber is an relative value
	
	if ( ( pRefernceElement != NULL ) && ( pRefernceElement->pSuperiorElement != NULL ) ){
		DEBUG_OUT_L2(<<"cFibElement::getObjectPointsForElement("<<pRefernceElement<<", "<<bAbsolute<<") done"<<endl<<flush);
		return pRefernceElement->pSuperiorElement->elementPointToObjectPointsUp(
			pRefernceElement, pActualElement );
	}//else no reference Fib element
	DEBUG_OUT_L2(<<"cFibElement::getObjectPointsForElement("<<pRefernceElement<<", "<<bAbsolute<<") done; no reference fib element"<<endl<<flush);
	return list<unsignedIntFib>();
}


/**
 * This method deletes the whool given Fib object with all the Fib
 * elements it contains and is contained in. The memory for the Fib
 * object is freed.
 *
 * @param fibObject the Fib object to delete
 */
void cFibElement::deleteObject( cFibElement * fibObject ){
	
	cFibElement * pFibElementToDelete = fibObject->getMasterRoot();
	
	pFibElementToDelete->deleteObject();
}


#else //FEATURE_FAST_UPDATE

/**
 * This method returns the number of this Fib element in the order of
 * Fib Elements or order of Fib Elements of the same type if bOfType
 * is true.
 *
 * @see getNumberOfElements()
 * @param bOfType if true the returned number is the number the order
 * 	of Fib elements of the same type as this Fib Element, else in
 * 	the order of all Fib elements
 * @return the number of this Fib element in the order of Fib
 * 	-Elements or order of Fib Elements of the same type if bOfType
 * 	is true
 */
unsignedIntFib cFibElement::getNumberOfElement( bool bOfType ) const{

	if ( !bOfType ){//of any type
		return uINumberOfFibElement;
	}//else
	
	unsignedIntFib ulNumberOfElement=1;
	
	cFibElement *actualFibElement = pPreviousFibElement;
	while ( actualFibElement != NULL ){
		
		if ( actualFibElement->getType() == getType() ){
			//actual Fib element and this are of the same type
			ulNumberOfElement++;
		}
		actualFibElement = actualFibElement->pPreviousFibElement;
	}

	return ulNumberOfElement;
}


/**
 * This method returns the number of this Fib element in the order of
 * move points.
 *
 * @see getNumberOfMovePoints()
 * @return the number of this Fib element in the order of move points
 */
unsignedIntFib cFibElement::getNumberOfMovePoint() const{
	
	if ( ! isMovable() ){
		//this Fib element is not movable -> it is no move point
		return 0;
	}
	
	unsignedIntFib ulNumberOfMovePoint = 1;
	
	cFibElement *actualFibElement = pPreviousFibElement;
	while ( actualFibElement != NULL ){
		
		if ( actualFibElement->isMovable() ){
			//actual Fib element and this are of the same type
			ulNumberOfMovePoint++;
		}
		actualFibElement = actualFibElement->pPreviousFibElement;
	}

	return ulNumberOfMovePoint;
}


/**
 * This method returns the number of the next connected object point
 * in the order of connected object points that conntains this Fib
 * element.
 *
 * @see getNumberOfObjectPoints()
 * @return the number of the next connected object point for this Fib 
 * 	element
 */
unsignedIntFib cFibElement::getNumberOfObjectPoint() const{
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getNumberOfObjectPoint( uINumberOfFibElement );
	}//else this is the beginning of the wool object
	return 0;
}


/**
 * This method converts the number of the elementPoint Fib element
 * of the type cType in this Fib object to the number it has in the
 * order of all Fib elements.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getType()
 * @param cType the type the original Fib element has
 * @param elementPoint the number of the original Fib element in the
 * 	order of Fib elements of the type cType
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return the number of the elementPoint Fib element of the type
 * 	cType in this Fib object has in the order of all Fib elements
 */
unsignedIntFib cFibElement::typeElementPointToElementPoint( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute ) const{
	
	if ( elementPoint == 0 ){
		return 0;
	}
	
	if ( bAbsolute ){
		return getMasterRoot()->typeElementPointToElementPoint( cType, elementPoint );
	}//else lNumber is an relative value
	
	if ( pNextFibElement == NULL ){
		return 0;
	}

	unsignedIntFib elementPointAll;
	
	if ( (getType() == cType) || (cType == 'u') ){
		//this element has the correct type -> count it
		if ( 1 < elementPoint ){
			elementPointAll = pNextFibElement->typeElementPointToElementPoint(
				cType, elementPoint - 1 );
		}else{//this is the correct element point
			return 1;
		}
	}else{
		elementPointAll = pNextFibElement->typeElementPointToElementPoint(
			cType, elementPoint );
	}

	if ( elementPointAll == 0 ){
		//no such element point
		return 0;
	}
	//count this element
	elementPointAll++;
	
	return elementPointAll;
}


/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element of the type cType.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param cType the type the Fib element has
 * @param elementPoint the number of the Fib element in the order of
 * 	Fib elements of the type cType
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibElement::elementPointToObjectPoints( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibElement::elementPointToObjectPoints("<<cType<<", "<<elementPoint<<", "<<bAbsolute<<") started"<<endl<<flush);
	
	cFibElement * pActualElement = const_cast<cFibElement *>( this );
	
	if ( bAbsolute ){
		pActualElement = getMasterRoot();
	}//else lNumber is an relative value
	
	DEBUG_OUT_L2(<<"actual fib element: "<<pActualElement<<endl<<flush);
	if ( elementPoint <= pActualElement->getNumberOfElements( cType ) ){
		
		DEBUG_OUT_L2(<<"evaluing reference Fib object "<<endl<<flush);
		cFibElement * pRefernceElement = pActualElement->
			getConstFibElement( cType, elementPoint );
		
		if ( pRefernceElement != NULL ){
			DEBUG_OUT_L2(<<"cFibElement::elementPointToObjectPoints("<<cType<<", "<<elementPoint<<", "<<bAbsolute<<") done"<<endl<<flush);
			return pActualElement->elementPointToObjectPoints( pRefernceElement, 0 );
		}//else no reference Fib element
	}//else the choosen Fib element is no Fib element under this
	DEBUG_OUT_L2(<<"cFibElement::elementPointToObjectPoints("<<cType<<", "<<elementPoint<<", "<<bAbsolute<<") done; no reference fib element"<<endl<<flush);
	return list<unsignedIntFib>();
}


/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element of the type cType.
 *
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param pFibElement the Fib element for which the object points
 * 	are to evalue
 * @param bAbsolute if the lNumber is an absolute value for the wool
 * 	Fib object
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibElement::getObjectPointsForElement(
		const cFibElement * pFibElement, bool bAbsolute ) const{
	
	DEBUG_OUT_L2(<<"cFibElement::getObjectPointsForElement("<<pFibElement<<", "<<bAbsolute<<") started"<<endl<<flush);
	
	if ( pFibElement == NULL ){
		//no Fib element -> no object points
		return list<unsignedIntFib>();
	}
	cFibElement * pActualElement = const_cast<cFibElement *>( this );
	
	if ( bAbsolute ){
		pActualElement = getMasterRoot();
	}//else lNumber is an relative value
	
	DEBUG_OUT_L2(<<"actual fib element: "<<pActualElement<<endl<<flush);
	if ( pFibElement->getNumberOfElements()  <= pActualElement->getNumberOfElements() ){
		
		DEBUG_OUT_L2(<<"cFibElement::getObjectPointsForElement("<<pFibElement<<", "<<bAbsolute<<") done"<<endl<<flush);
		return pActualElement->elementPointToObjectPoints( pFibElement, 0 );
	}//else the choosen Fib element is no Fib element under this
	DEBUG_OUT_L2(<<"cFibElement::getObjectPointsForElement("<<pFibElement<<", "<<bAbsolute<<") done; no reference fib element"<<endl<<flush);
	return list<unsignedIntFib>();
}


/**
 * This method deletes the whool given Fib object with all the Fib
 * elements it contains and is contained in. The memory for the Fib
 * object is freed.
 *
 * @param fibObject the Fib object to delete
 */
void cFibElement::deleteObject( cFibElement * fibObject ){
	
	cFibElement * pFibElementToDelete = fibObject;
	
	/*go to the first element in the object tree*/
	while ( pFibElementToDelete->pPreviousFibElement != NULL ){
		pFibElementToDelete = pFibElementToDelete->pPreviousFibElement;
	}
	
	cFibElement * pFibElementNext;
	/*delete all Fib elements, by stepping to the next Fib element and
	deleting the actual Fib element*/
	while ( pFibElementToDelete != NULL ){
		pFibElementNext = pFibElementToDelete->pNextFibElement;
		delete pFibElementToDelete;
		pFibElementToDelete = pFibElementNext;
	}
}

#endif //FEATURE_FAST_UPDATE


/**
 * @return true if this Fib element is movebel else false
 */
bool cFibElement::isMovable() const{
	//the default is that the Fib element is not movable
	return false;
}

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
bool cFibElement::isRemovableElement( const char cType,
		const unsignedIntFib elementPoint, bool bAbsolute, bool bCheckVariables ) const{
	
	if ( elementPoint == 0 ){
		//check this Fib element
		
		if ( pSuperiorElement == NULL ){
			//can't remove the topmost Fib element
			return false;
		}
		
		if ( bCheckVariables ){
			//check if the variables this Fib element defines are needed
			
			const list<cFibVariable*> liDefinedVariables =
				const_cast<cFibElement*>(this)->getDefinedVariables( ED_POSITION );
			
			for ( list<cFibVariable*>::const_iterator actualVariable = liDefinedVariables.begin();
					actualVariable != liDefinedVariables.end(); actualVariable++ ){
				
				if ( (*actualVariable)->getNumberOfUsingElements() != 0 ){
					return false;
				}
			}
		}
		return true;
	}//else check an other Fib element

	const cFibElement * pFibElementToCheck = getConstFibElement( cType,
		elementPoint, bAbsolute );
	
	if ( pFibElementToCheck != NULL ){
		return pFibElementToCheck->isRemovableElement( 'u', 0, false, bCheckVariables );
	}//else no element ->can't remove
	return false;
}


/**
 * This method removes the Fib element on the specified position.
 *
 * @see isDeletableElement()
 * @see getType()
 * @param cType the type of the Fib element to remove
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to remove
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib object
 * @param bCheckVariables if true (standardvalue) it will be checked if
 * 	the variables the Fib element defines are needed, else the 
 * 	Fib element will be removed even if its variables are needed elsewher
 * @return true if the Fib element was removed, else false
 */
bool cFibElement::removeElement(  const char cType, const unsignedIntFib
		elementPoint, bool bAbsolute, bool bCheckVariables ){
	
	cFibElement * pCutElement = cutElement( cType, elementPoint, bAbsolute, bCheckVariables );
	if ( pCutElement == NULL ){
		return false;
	}//else
	delete pCutElement;
	return true;
}


/**
 * This method duplicates the whole Fib object, beginning with it's
 * highest Fib element (the one which contains all the other elements).
 *
 * @return the cloned/ duplicates Fib object
 */
cFibElement * cFibElement::clone() const{
	//go to the topmost fib element
	return getMasterRoot()->copy();
}

/**
 * This method copies the connected object with the given number in the
 * order of connected objects.
 * For this every Fib element, beginning from this Fib element, that
 * is part of the connected object will be copied.
 * Variables which are not defined in the connected object but used
 * don't change ther reference.
 *
 * @param iObjectPoint the number of the connected object to copy;
 * 	the standartvalue is 0 for coping the complet actual object
 * @return the copy of the connected object or NULL if non such exists
 */
cFibElement * cFibElement::copy( const unsignedIntFib iObjectPoint ) const{

	cFibElement * pCopiedElement = copyInternal( iObjectPoint );
#ifndef FEATURE_FAST_UPDATE
	if ( pCopiedElement ){
		pCopiedElement->updateAllValues();
	}
#endif //FEATURE_FAST_UPDATE
	return pCopiedElement;
}



/**
 * This method restores a Fib object from the stream where it is
 * stored in the XML format.
 *
 * @pattern Factory Method
 * @param stream the stream where the Fib object is stored in
 * @param outStatus An pointer to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @return the readed Fib object or the Nullpointer NULL, if reading
 * 	was not possible
 */
cFibElement *cFibElement::restoreXml( istream &stream, intFib *outStatus ){
	
	
	TiXmlDocument xmlDocFibObject;

	stream >> xmlDocFibObject;
	
	if ( xmlDocFibObject.Error() ){
		if ( outStatus ){
			*outStatus = -1;
		}
		return NULL;
	}
	
	//TODO check on xsd

	return restoreXml( &xmlDocFibObject, outStatus );
}


/**
 * This method restores this Fib object from the TinyXml handle where
 * it is stored.
 *
 * @pattern Factory Method
 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
 * @param outStatus An pointer to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid node
 * 		- -2 loading error, invalid data in node
 * 		- 1 loading warning, invalid data in node, error could be corrected
 * 		- 2 loading warning, invalid data in node, maybe the loaded
 * 			object is wrong
 * @return the readed Fib object or the Nullpointer NULL, if reading
 * 	was not possible
 */
cFibElement * cFibElement::restoreXml( const TiXmlNode * pXmlNode, intFib *outStatus ){
	
	if ( pXmlNode == NULL ){
		if (outStatus != NULL){
			*outStatus = -1;
		}
		return NULL;
	}
	intFib outStatusInt = 0;
	list<cFibVariable*> liDefinedVariables;
	
	cFibElement * pRestoredFibObject = restoreXmlInternal( pXmlNode,
		outStatusInt, liDefinedVariables );
	
#ifdef FEATURE_FAST_UPDATE
	if ( pRestoredFibObject == NULL ){
		//Error: nothing restored
		outStatusInt = -2;
	}
#else //FEATURE_FAST_UPDATE
	if ( pRestoredFibObject ){
		pRestoredFibObject->updateAllValues();
	}else{//Error: nothing restored
		outStatusInt = -2;
	}
#endif //FEATURE_FAST_UPDATE
	if (outStatus != NULL){
		//copy error status
		*outStatus = outStatusInt;
	}
#ifndef TEST
	if ( outStatusInt < 0 ){
		//an error occured
		if ( pRestoredFibObject ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		return NULL;
	}
#endif
	return pRestoredFibObject;
}


/**
 * This method restores this Fib object from the TinyXml handle where
 * it is stored.
 *
 * @pattern Factory Method
 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid node
 * 		- -2 loading error, invalid data in node
 * 		- 1 loading warning, invalid data in node, error could be corrected
 * 		- 2 loading warning, invalid data in node, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @return the readed Fib object or the Nullpointer NULL, if reading
 * 	was not possible
 */
cFibElement * cFibElement::restoreXml( const TiXmlNode * pXmlNode,
		intFib &outStatus, list<cFibVariable*> & liDefinedVariables ){
	
	if ( pXmlNode == NULL ){
		outStatus = -1;
		return NULL;
	}
	
	cFibElement * pRestoredFibObject = restoreXmlInternal( pXmlNode,
		outStatus, liDefinedVariables );
	
#ifdef FEATURE_FAST_UPDATE
	if ( pRestoredFibObject == NULL ){
		//Error: nothing restored
		outStatus = -2;
	}
#else //FEATURE_FAST_UPDATE
	if ( pRestoredFibObject ){
		pRestoredFibObject->updateAllValues();
	}else{//Error: nothing restored
		outStatus = -2;
	}
#endif //FEATURE_FAST_UPDATE
#ifndef TEST
	if ( outStatus < 0 ){
		//an error occured
		if ( pRestoredFibObject ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		return NULL;
	}
#endif
	return pRestoredFibObject;
}


/**
 * This method restores this Fib object from the TinyXml handle where
 * it is stored.
 *
 * @pattern Factory Method
 * @param pXmlNode a pointer to the TinyXml node the Fib object is stored in
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid node
 * 		- -2 loading error, invalid data in node
 * 		- 1 loading warning, invalid data in node, error could be corrected
 * 		- 2 loading warning, invalid data in node, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @return the readed Fib object or the Nullpointer NULL, if reading
 * 	was not possible
 */
cFibElement * cFibElement::restoreXmlInternal( const TiXmlNode * pXmlNode,
		intFib &outStatus, list<cFibVariable*> & liDefinedVariables ){
	
	cFibElement * pRestoredFibObject = NULL;
	
	if ( pXmlNode == NULL ){
		//Error: nothing to load
		outStatus = -1;
		return NULL;
	}
	//as long no Fib element was read and no error occured
	while ( ( pXmlNode != NULL ) && ( 0 <= outStatus ) ){
		//get type of XML element
		const int iType = pXmlNode->Type();

#ifdef DEBUG_RESTORE_XML
		//print debugging output
		switch ( iType ){
			case TiXmlNode::ELEMENT:
				printf( "Element \"%s\" (outStatus now %i)\n", pXmlNode->Value(), outStatus );
			break;
			
			case TiXmlNode::DOCUMENT:
				printf( "Document\n" );
			break;
			case TiXmlNode::COMMENT:
				printf( "Comment: \"%s\"\n", pXmlNode->Value());
			break;
			case TiXmlNode::UNKNOWN:
				printf( "Unknown\n" );
			break;
			case TiXmlNode::TEXT:{
				const TiXmlText * pText = pXmlNode->ToText();
				printf( "Text: [%s]\n", pText->Value() );
			}break;
			case TiXmlNode::DECLARATION:
				printf( "Declaration\n" );
			break;
			default:
				printf( "No known XML element\n" );
		}
#endif
		switch ( iType ){
			case TiXmlNode::ELEMENT:{
				/*check if this is a valid Fib element XML element, create
				the apropirate Fib element and call its restoreXml() method*/
				const TiXmlElement * pXmlElement = pXmlNode->ToElement();
				if ( pXmlElement == NULL ){
					//Error: nothing to load
					outStatus = 2;
					return NULL;
				}
				string szElementType( pXmlElement->Value() );
				
				if ( szElementType == "fib_object" ){
					
					for ( const TiXmlNode * pChild = pXmlNode->FirstChild();
							pChild != NULL; pChild = pChild->NextSibling() ) {
						
						pRestoredFibObject = restoreXmlInternal(
							pChild, outStatus, liDefinedVariables );
						if ( pRestoredFibObject != NULL ){
							return pRestoredFibObject;
						}
						if ( outStatus < 0 ){
							//an error occured
							return NULL;
						}
					}
					//nothing to load
					outStatus = -2;
					return NULL;
				}else if ( szElementType == "root" ){
					pRestoredFibObject = new cRoot( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "point" ){
					pRestoredFibObject = new cPoint( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "background" ){
					cVectorPosition pVectorPosition( 0 );
					pRestoredFibObject = new cPoint( &pVectorPosition );
				}else if ( szElementType == "list" ){
					pRestoredFibObject = new cList( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "property" ){
					pRestoredFibObject = new cProperty( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "area" ){
					pRestoredFibObject = new cArea( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "function" ){
					pRestoredFibObject = new cFunction( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "if" ){
					pRestoredFibObject = new cIf( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "comment" ){
					pRestoredFibObject = new cComment( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "obj" ){
					pRestoredFibObject = new cExtObject( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "subobject" ){
					pRestoredFibObject = new cExtSubobject( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "set" ){
					pRestoredFibObject = new cFibSet( pXmlElement, outStatus, liDefinedVariables );
				}else if ( szElementType == "matrix" ){
					pRestoredFibObject = new cFibMatrix( pXmlElement, outStatus, liDefinedVariables );
				}else{//Error: no Fib element to load
#ifdef DEBUG_RESTORE_XML
					//print debugging output
					printf( "Error: No Fib element to load\n" );
#endif//DEBUG_RESTORE_XML
					outStatus = 2;
					return NULL;
				}//TODO more Fib elements
#ifdef DEBUG_RESTORE_XML
				//print debugging output
				if ( pRestoredFibObject == NULL ){
					printf( "Error: No Fib object restored (NULL)\n" );
				}
#endif//DEBUG_RESTORE_XML
				
				return pRestoredFibObject;
			}break;
			case TiXmlNode::DOCUMENT:{
				//ignore
				for ( const TiXmlNode * pChild = pXmlNode->FirstChild();
						pChild != NULL; pChild = pChild->NextSibling() ) {
					
					pRestoredFibObject = restoreXmlInternal(
						pChild, outStatus, liDefinedVariables );
					if ( pRestoredFibObject != NULL ){
						return pRestoredFibObject;
					}
					if ( outStatus < 0 ){
						//an error occured
						return NULL;
					}
				}
				//nothing to load
#ifdef DEBUG_RESTORE_XML
				//print debugging output
				printf( "Error: nothing to load\n" );
#endif//DEBUG_RESTORE_XML
				outStatus = -2;
				return NULL;
			}break;
			case TiXmlNode::DECLARATION:
			case TiXmlNode::COMMENT:{
				//ignore
			}break;
			case TiXmlNode::TEXT:
			case TiXmlNode::UNKNOWN:
			default:
				//ignore; Warning: invalid Fib object
				outStatus = 2;
		}//end switch XML element type
		//if no Fib element was read check next XML eleemnt
		pXmlNode = pXmlNode->NextSibling();
	}//end as long no Fib element was read and no error occured
	//Error: no Fib object restored
	outStatus = -2;
	return NULL;
}


/**
 * This method stores this Fib object in the compressed Fib format
 * into the given stream.
 *
 * @param stream the stream where this Fib object should be stored to
 * @return true if this Fib object is stored, else false
 */
bool cFibElement::store( ostream &stream ) const{
	char cRestBits = 0;
	unsigned char uiRestBitPosition = 0;
	bool bObjectStored = storeBit( stream, cRestBits, uiRestBitPosition );
	
	if ( bObjectStored && ( uiRestBitPosition != 0 ) ){
		//store the restbits
		stream << cRestBits;
	}
	return bObjectStored;
}


/**
 * This method restores a Fib object from the stream where it is
 * stored in the compressed Fib format.
 *
 * @pattern Factory Method
 * @param stream the stream where this Fib object is stored to in
 * @param outStatus An pointer to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @return the readed Fib object or the Nullpointer NULL, if reading
 * 	was not possible
 */
cFibElement *cFibElement::restore( istream &stream, intFib *outStatus ){

	if ( ! stream.good() ){
		if (outStatus != NULL){
			*outStatus = -1;
		}
		return NULL;
	}
	intFib outStatusInt = 0;
	
	cReadBits iBitStream( stream );

	cFibElement * pRestoredFibObject = restoreRootInternal( iBitStream,
		outStatusInt, NULL );
	
#ifdef FEATURE_FAST_UPDATE
	if ( pRestoredFibObject == NULL ){
		//Error: nothing restored
		outStatusInt = -2;
	}
#else //FEATURE_FAST_UPDATE
	if ( pRestoredFibObject ){
		pRestoredFibObject->updateAllValues();
	}else{//Error: nothing restored
		outStatusInt = -2;
	}
#endif //FEATURE_FAST_UPDATE
	if (outStatus != NULL){
		//copy error status
		*outStatus = outStatusInt;
	}
#ifndef TEST
	if ( outStatusInt < 0 ){
		//an error occured
		if ( pRestoredFibObject ){
			cFibElement::deleteObject( pRestoredFibObject );
		}
		return NULL;
	}
#endif
	return pRestoredFibObject;
}


/**
 * This method restores a rootobject from the stream where it is
 * stored in the compressed Fib format.
 * This method is for internal use only.
 *
 * @pattern Factory Method
 * @param iBitStream the stream where this rootobject is stored to in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @param pNextRoot the next higher root element for the to restore
 * 	Fib elements, or the last restored root element;
 * 	if NULL the next Fib element restored will be an root element
 * 	be restore)
 * @return the readed rootobject or the Nullpointer NULL, if reading
 * 	was not possible
 */
cRoot * cFibElement::restoreRootInternal( cReadBits & iBitStream, intFib & outStatus,
		cRoot * pNextRoot ){
	
	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return NULL;
	}
	cRoot * pRestoredRoot = NULL;
	
	//restore an root element
	pRestoredRoot = new cRoot( iBitStream, outStatus, pNextRoot );
	return pRestoredRoot;
}


/**
 * This method restores a (non root) Fib object from the stream where it is
 * stored in the compressed Fib format.
 * This method is for internal use only.
 *
 * @pattern Factory Method
 * @param iBitStream the stream where this Fib object is stored to in,
 * 	because this stream is an cReadBits, any number of bits can be
 * 	readed from it
 * @param outStatus An reference to an integervalue where the errorvalue
 * 	can be stored to. If the pointer is NULL no errorvalue will be
 * 	given back.
 * 	possible errorvalues are:
 * 		- 0  loading successful
 * 		- -1 loading error, invalid stream
 * 		- -2 loading error, invalid data in stream
 * 		- 1 loading warning, invalid data in stream, error could be corrected
 * 		- 2 loading warning, invalid data in stream, maybe the loaded
 * 			object is wrong
 * @param liDefinedVariables a list with the defined variables for the
 * 	to restore Fib element, every variable should have it's number
 * 	(the number under which it is stored) as it's value
 * @param validDomains the domains valid for restoring the Fib elements
 * @param pNextRoot the next higher root element for the to restore
 * 	Fib elements, or the last restored root element
 * @return the readed Fib object or the Nullpointer NULL, if reading
 * 	was not possible
 */
cFibElement * cFibElement::restoreInternal( cReadBits & iBitStream, intFib & outStatus,
		list<cFibVariable*> & liDefinedVariables, const cDomains & validDomains,
		cRoot * pNextRoot ){

	if ( ! iBitStream.getStream()->good() ){
		outStatus = -1;
		return NULL;
	}
	cFibElement * pRestoredFibObject = NULL;
	
	//read the bits to indicate which Fib element should be readed next
	char cTypeNextFibElement = 0x00;
	int iBitsRead = iBitStream.readBits( &cTypeNextFibElement, 4 );
	
	if ( iBitsRead != 4 ){
		outStatus = -2;
		DEBUG_OUT_EL2(<<"Error type Fib element: 4 bits to read, but "<<iBitsRead<<" bits readed"<<endl);
		return NULL;
	}
	DEBUG_OUT_L4(<<"outStatus="<<outStatus<<endl);
	
	switch ( cTypeNextFibElement ){
		case 0x00:{//read NULL
			DEBUG_OUT_L4(<<"reading NULL"<<endl);
			pRestoredFibObject = NULL;
			outStatus = 2;
		}break;
		case 0x01:{//read a point element
			DEBUG_OUT_L4(<<"reading point"<<endl);
			pRestoredFibObject = new cPoint( iBitStream, outStatus,
				liDefinedVariables, validDomains );
		}break;
		case 0x02:{//read a point element with empty or no positionsvector
			char cTypePointElement = 0x00;
			iBitsRead = iBitStream.readBits( &cTypePointElement, 1 );
			
			if ( iBitsRead != 1 ){
				outStatus = -2;
				return NULL;
			}
			if ( cTypePointElement == 0x00 ){
				//empty positionsvector
				DEBUG_OUT_L4(<<"reading point with empty positions vector"<<endl);
				cVectorPosition pVectorPosition( 0 );
				pRestoredFibObject = new cPoint( &pVectorPosition );
			}else{
				//no positionsvector
				DEBUG_OUT_L4(<<"reading point with no positions vector"<<endl);
				pRestoredFibObject = new cPoint();
			}
		}break;
		case 0x03:{//read a property element
			DEBUG_OUT_L4(<<"reading property element"<<endl);
			pRestoredFibObject = new cProperty( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x04:{//read a list element with two underobjects
			DEBUG_OUT_L4(<<"reading list element with two underobjects"<<endl);
			pRestoredFibObject = new cList( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x05:{//read a list element with maximal 256 underobjects
			DEBUG_OUT_L4(<<"reading list element with max 256 underobjects"<<endl);
			pRestoredFibObject = new cList( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot, 8 );
		}break;
		case 0x06:{//read a list element with maximal 2^64 underobjects
			DEBUG_OUT_L4(<<"reading list element with max 2^64 underobjects"<<endl);
			pRestoredFibObject = new cList( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot, 64 );
		}break;
		case 0x07:{//read a comment element
			DEBUG_OUT_L4(<<"reading comment element"<<endl);
			pRestoredFibObject = new cComment( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x08:{//read a area element
			DEBUG_OUT_L4(<<"reading area element"<<endl);
			pRestoredFibObject = new cArea( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		//free 0x09; 0x0A
		case 0x0B:{//read a function element
			DEBUG_OUT_L4(<<"reading function element"<<endl);
			pRestoredFibObject = new cFunction( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x0C:{//read a ifelement
			DEBUG_OUT_L4(<<"reading ifelement"<<endl);
			pRestoredFibObject = new cIf( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x0D:{//read an external object element
			DEBUG_OUT_L4(<<"reading external object element"<<endl);
			pRestoredFibObject = new cExtObject( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x0E:{//read an external suobject element
			DEBUG_OUT_L4(<<"reading external suobject element"<<endl);
			pRestoredFibObject = new cExtSubobject( iBitStream, outStatus,
				liDefinedVariables, validDomains, pNextRoot );
		}break;
		case 0x0F:{//read an Fib element with more than 4 bit initiatior
			//read remaining 12 bits to indicate which Fib element should be readed next
			char cTypeNextFibElement12Bit[ 2 ];
			cTypeNextFibElement12Bit[ 0 ] = 0x00;
			cTypeNextFibElement12Bit[ 1 ] = 0x00;
			int iBitsRead = iBitStream.readBits( cTypeNextFibElement12Bit, 12 );
			
			if ( iBitsRead != 12 ){
				outStatus = -2;
				DEBUG_OUT_EL2(<<"Error type Fib element: 12 bits more to read, but "<<iBitsRead<<" bits readed"<<endl);
				return NULL;
			}
			
			if ( cTypeNextFibElement12Bit[ 1 ] == 0x00 ){
				if ( cTypeNextFibElement12Bit[ 0 ] == 0x01 ){
					//0x1F, 0x00: read an set-element
					DEBUG_OUT_L4(<<"reading set-element"<<endl);
					
					pRestoredFibObject = new cFibSet( iBitStream, outStatus,
						liDefinedVariables, validDomains, pNextRoot );
				}else if ( cTypeNextFibElement12Bit[ 0 ] == 0x02 ){
					//0x2F, 0x00: read an matrix element
					DEBUG_OUT_L4(<<"reading matrix element"<<endl);
					
					pRestoredFibObject = new cFibMatrix( iBitStream, outStatus,
						liDefinedVariables, validDomains, pNextRoot );
				}
			}
		}break;
		
		//TODO more Fib elements
		
		default:
			//ignore; Warning: invalid Fib object
			DEBUG_OUT_L4(<<"Warning: invalid Fib object 0x"<< hex << (unsigned short)cTypeNextFibElement << dec <<endl);
			outStatus = -2;
	}
	return pRestoredFibObject;
}


#ifdef FEATURE_FAST_UPDATE

/**
 * @return a pointer to the next superior root element or NULL, if non
 * 	such exists
 */
cRoot * cFibElement::getSuperiorRootElement(){
	
	
	for ( cFibElement * pActualSuperiorElement = this->pSuperiorElement;
			pActualSuperiorElement != NULL;
			pActualSuperiorElement = pActualSuperiorElement->pSuperiorElement ){
		
		if ( pActualSuperiorElement->getType() == 'r' ){
			return ((cRoot*)(pActualSuperiorElement));
		}
	}
	return NULL;
}

/**
 * @return a pointer to the next superior root element or NULL, if non
 * 	such exists
 */
const cRoot * cFibElement::getSuperiorRootElement() const{
	
	
	for ( const cFibElement * pActualSuperiorElement = this->pSuperiorElement;
			pActualSuperiorElement != NULL;
			pActualSuperiorElement = pActualSuperiorElement->pSuperiorElement ){
		
		if ( pActualSuperiorElement->getType() == 'r' ){
			return ((const cRoot*)(pActualSuperiorElement));
		}
	}
	return NULL;
}

#else //FEATURE_FAST_UPDATE

/**
 * @return a pointer to the next superior root element or NULL, if non
 * 	such exists
 */
cRoot * cFibElement::getSuperiorRootElement(){

	return pNextRootElement;
}

/**
 * @return a pointer to the next superior root element or NULL, if non
 * 	such exists
 */
const cRoot * cFibElement::getSuperiorRootElement() const{

	return pNextRootElement;
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method returns the identifiers of all root objects of this
 * object.
 *
 * @return the identifiers of all root objects of this object
 */
list<longFib> cFibElement::getAllRootObjectIdentifiers() const{
	//the root element will implement the functionality for this method
	const cFibElement * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getAllRootObjectIdentifiers();
	}else{//no next root element -> no root object identifiers
		return list<longFib>();
	}
}


/**
 * This method returns the identifiers of all database objects, in the
 * actual database.
 *
 * @return the identifiers of all database objects
 */
list<longFib> cFibElement::getAllDatabaseObjectIdentifiers() const{

	//return database identifiers
	return cFibDatabase::getInstance()->getAllDatabaseObjectIdentifiers();
}


/**
 * This method returns the root object for the given identifier.
 * If non such exists the null pointer NULL is returned.
 *
 * @param lIdentifier the identifier of the root object to return
 * @return the root object for the given identifier or NULL if non
 * 	such exists
 */
cRoot * cFibElement::getRootObject( longFib lIdentifier ){
	//the root element will implement the functionality for this method
	cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getRootObject( lIdentifier );
	}else{
#ifdef FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
		//no next root element -> just check Fib database
		//search database root objects
		return cFibDatabase::getInstance()->getFibObject( lIdentifier );
#else //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
		//no next root element -> no root object for the identifiers
		return NULL;
#endif //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	}
}

/**
 * This method returns the identifiers of all from this Fib element
 * accessible root objects of this object.
 *
 * @return the identifiers of all accessible root objects
 */
list<longFib> cFibElement::getAllAccessibleRootObjectIdentifiers() const{
	//the root element will implement the functionality for this method
	const cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getAllAccessibleRootObjectIdentifiers();
	}else{
#ifdef FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
		//no next root element -> just return iderntifiers from Fib database
		//search database root objects
		return cFibDatabase::getInstance()->getAllDatabaseObjectIdentifiers();
#else //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
		//no next root element -> no accessible root object identifiers
		return list<longFib>();
#endif //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	}
}

/**
 * This method returns the from this Fib element accessible root
 * object for the given identifier. If non such exists the Nullpoint 
 * NULL is returned.
 *
 * @param lIdentifier the identifier of the root object to return
 * @return the accessible root object for the given identifier or NULL
 * 	if non such exists
 */
cRoot * cFibElement::getAccessibleRootObject( longFib lIdentifier ){
	//the root element will implement the functionality for this method
	cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getAccessibleRootObject( lIdentifier );
	}else{
#ifdef FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
		//no next root element -> just check Fib database
		//search database root objects
		return cFibDatabase::getInstance()->getFibObject( lIdentifier );
#else //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
		//no next root element -> no accessible root objects
		return NULL;
#endif //FEATURE_FIB_ELEMENT_CHECKS_DATABASE_FOR_EXTERNAL_OBJECTS
	}
}

/**
 * This method returns the domains that are valid for this Fib element.
 *
 * @return the domains that are valid for this Fib element
 */
cDomains cFibElement::getValidDomains() const{
	//the root element will implement the functionality for this method
	const cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getValidDomains();
	}else{//no next root element -> no domains
		return cDomains();
	}
}

/**
 * This method returns the value domains that are valid for this 
 * Fib element.
 *
 * @return the value domains that are valid for this Fib element
 */
cDomains cFibElement::getValidValueDomains() const{
	//the root element will implement the functionality for this method
	const cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getValidValueDomains();
	}else{//no next root element -> no domains
		return cDomains();
	}
}


/**
 * This method returns the number of dimensions in this
 * Fib Multimediaobject.
 *
 * @return the number of dimensions in
 */
unsignedIntFib cFibElement::getNumberOfDimensions() const{
	//the root element will implement the functionality for this method
	const cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getNumberOfDimensions();
	}else{//no next root element -> no dimensions
		return (unsignedIntFib)(0);
	}
}

/**
 * This method returns in which direction the iDimensionNumber dimension
 * is mapped.
 *
 * @param iDimensionNumber the number of the dimension for which the
 * 	mapping is to be returned
 * @return the direction in which the iDimensionNumber dimension is
 * 	mapped
 */
unsignedIntFib cFibElement::getDimensionMapping( unsignedIntFib iDimensionNumber ) const{
	//the root element will implement the functionality for this method
	const cRoot * pNextRootElement = getSuperiorRootElement();
	if ( pNextRootElement != NULL ){
		return pNextRootElement->getDimensionMapping( iDimensionNumber );
	}else{//no next root element -> no dimensions
		return (unsignedIntFib)(0);
	}
}



/**
 * @return this method returns true if this Fib element is an
 * 	branchelement, alse false
 */
bool cFibElement::isBranch() const{
	return false;
}


/**
 * @return this method returns true if this Fib element is an
 * 	limbelement, alse false
 */
bool cFibElement::isLimb() const{
	return false;
}


/**
 * @return this method returns true if this Fib element is an
 * 	leafelement, alse false
 */
bool cFibElement::isLeaf() const{
	return false;
}

//protected methods

#ifdef FEATURE_FAST_UPDATE

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
unsignedIntFib cFibElement::getNumberOfObjectPointUp(
		const cFibElement * pLastFibElement ) const{
	
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getNumberOfObjectPointUp( this );
	}//the object point is the wool object
	return 0;
}

#else //FEATURE_FAST_UPDATE


/**
 * This method returns the number of the next connected object point
 * in the order of connected object points that conntains this Fib
 * element.
 *
 * @param uINumberOfStartFibElement the number, in the order of all
 * 	Fib elements, of the Fib element for which the connected object
 * 	point is to return
 * @see getNumberOfObjectPoint
 * @see getNumberOfObjectPoints()
 * @return the number of the next connected object point for this Fib 
 * 	element
 */
unsignedIntFib cFibElement::getNumberOfObjectPoint(
		unsignedIntFib uINumberOfStartFibElement ) const{
	if ( pSuperiorElement != NULL ){
		return pSuperiorElement->getNumberOfObjectPoint( uINumberOfStartFibElement );
	}//the object point is the wool object
	return 0;
}

#endif //FEATURE_FAST_UPDATE



#ifdef FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib object is equal to this fib
 * object.
 * Variables can be others, but must be defined and used in equivalent
 * Fib elements.
 *
 * @param fibObject the Fib object to which this Fib object should be
 * 	equal
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib object is equal to the given Fib object,
 * 	else false
 */
bool cFibElement::equal( const cFibElement & fibObject,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	if ( ( pSuperiorElement == NULL ) &&
			( fibObject.pSuperiorElement == NULL ) ){
		//external objects will be compared in the rootelements
		return equalInternal( fibObject,
			mapEqualRootObjects, mapEqualDefinedVariables, false );
	}
	return equalInternal( fibObject,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib element is equal to this fib
 * element.
 * The subobjects arn't compared, not even ther count is compared.
 * Used variables can be others.
 *
 * @param fibElement the Fib element to which this Fib element should be
 * 	equal
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib element is equal to the given Fib object,
 * 	else false
 */
bool cFibElement::equalElement( const cFibElement & fibElement,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalElementInternal( fibElement,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param variableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable fibElement in the given
 * 	Fib element fibElement
 * @param fibElement the Fib element to which this Fib element should be
 * 	compared
 * @param variable a pointer to a defined variable in the other 
 * 	Fib element fibElement
 * @param bCheckExternalObjects if true the external objects of
 * 	cExtObject will be compared
 * @return true if this Fib element sets the variable to the same
 * 	values as this Fib element
 */
bool cFibElement::equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable,
		const bool bCheckExternalObjects ) const{
	
	map< const cRoot *, const cRoot * > mapEqualRootObjects;
	map< const cFibElement *, const cFibElement * > mapEqualDefinedVariables;
	
	return equalValuesSetInternal( variableOwn, fibElement, variable,
		mapEqualRootObjects, mapEqualDefinedVariables, bCheckExternalObjects );
}


/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param variableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable fibElement in the given
 * 	Fib element fibElement
 * @param fibElement the Fib element to which this Fib element should be
 * 	compared
 * @param variable a pointer to a defined variable in the other 
 * 	Fib element fibElement
 * @param mapEqualRootObjects the root objects of this object that wher
 * 	already checked as equal
 * 	map entries:
 * 		key: the rootelement of this Fib object that was checked
 * 		value: the to the key correspondending rootelement of the
 * 			fibObject that was checked and which is equal to the key
 * 		rootelement
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
 * @return true if this Fib element sets the variable to the same
 * 	values as this Fib element
 */
bool cFibElement::equalValuesSetInternal( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable,
		map< const cRoot *, const cRoot * > & mapEqualRootObjects,
		map< const cFibElement *, const cFibElement * > & mapEqualDefinedVariables,
		const bool bCheckExternalObjects ) const{
	/*most Fib elements don't define variables, so the set them to the
	same values*/
	return true;
}

#else //FEATURE_EQUAL_FIB_OBJECT

/**
 * This method checks if the given Fib element sets the variable to
 * the same values as this Fib element.
 *
 * @param variableOwn a pointer to a defined variable in this Fib element,
 * 	it is compared to the equivalent variable fibElement in the given
 * 	Fib element fibElement
 * @param fibElement the Fib element to which this Fib element should be
 * 	compared
 * @param variable a pointer to a defined variable in the other 
 * 	Fib element fibElement
 * @return true if this Fib element sets the variable to the same
 * 	values as this Fib element
 */
bool cFibElement::equalValuesSet( const cFibVariable * variableOwn,
		const cFibElement & fibElement,
		const cFibVariable * variable ) const{
	/*most Fib elements don't define variables, so the set them to the
	same values*/
	return true;
}

#endif //FEATURE_EQUAL_FIB_OBJECT


#ifdef FEATURE_FAST_UPDATE

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
list<unsignedIntFib> cFibElement::elementPointToObjectPointsUp(
		const cFibElement * pLastFibElement,
		const cFibElement * pFirstFibElement ) const{
	
	if ( ( pSuperiorElement != NULL ) && ( this != pFirstFibElement ) ){
		//search for more objectpoints
		return pSuperiorElement->elementPointToObjectPointsUp( this, pFirstFibElement );
	}//else all object points found
	return list<unsignedIntFib>();
}


/**
 * This method updates the values/ properties off all Fib elements in
 * the whool Fib object this Fib element is part of.
 *
 * The highest Fib element needs to be reachebel from this
 * Fib element and every underobject should have all it's underobjects.
 */
bool cFibElement::updateAllValues(){

	/*go to the next higher branch element and update the values ther*/
	cFibElement * pActualElement = this;
	
	while (pActualElement != NULL){
		if ( pActualElement->isBranch() ){
			((cFibBranch*)(pActualElement))->updateAllCounters();
			return true;
		}
		pActualElement = pActualElement->pSuperiorElement;
	}
	return true;
}


/**
 * This method cuts the connections of this Fib element to the
 * given Fib element.
 *
 * @param pFibElement the Fib element to which to cut the connection
 */
void cFibElement::cutConnectionsTo( const cFibElement * pFibElement ){
	
	if ( pSuperiorElement == pFibElement ){
		pSuperiorElement = NULL;
	}
}


#else //FEATURE_FAST_UPDATE

/**
 * This method returns the numbers of all object points that contain the
 * elementPoint Fib element of the type cType.
 *
 * @see elementPointToObjectPoints()
 * @see getNumberOfElement()
 * @see getNumberOfElements()
 * @see getNumberOfObjectPoint()
 * @see getNumberOfObjectPoints()
 * @see getType()
 * @param referenceFibObject the Fib element for which the object points
 * 	are to returned
 * @param uiLastObjectPoint the number of the last object point to the
 * 	referenceFibObject
 * @return a list of the numbers of all object points that contain the
 * 	elementPoint Fib element of the type cType
 */
list<unsignedIntFib> cFibElement::elementPointToObjectPoints(
		const cFibElement *referenceFibObject,
		const unsignedIntFib uiLastObjectPoint  ) const{
	
	if ( (pNextFibElement != NULL) && (this != referenceFibObject) ){
	
		return pNextFibElement->elementPointToObjectPoints( referenceFibObject, uiLastObjectPoint );
	}//else this==referenceFibObject or no pSuperiorElement -> all object points found
	return list<unsignedIntFib>();
}


/**
 * This method updates the values/ properties off all Fib elements in
 * the whool Fib object this Fib element is part of.
 *
 * The highest Fib element needs to be reachebel from this
 * Fib element and every underobject should have all it's underobjects.
 */
bool cFibElement::updateAllValues(){

	/*go to the most top/ superior Fib element and call this method non
	absolute*/
	cFibElement * pActualElement = this;

	while ( (pActualElement->pSuperiorElement != NULL) ||
			(pActualElement->pPreviousFibElement != NULL) ){
		
		if ( pActualElement->pSuperiorElement != NULL ){
			if ( pActualElement->pSuperiorElement->pNextFibElement == NULL ){
				pActualElement->pSuperiorElement->pNextFibElement = pActualElement;
			}
			pActualElement = pActualElement->pSuperiorElement;
		}else{
			if ( pActualElement->pPreviousFibElement->pNextFibElement == NULL ){
				pActualElement->pPreviousFibElement->pNextFibElement = pActualElement;
			}
			pActualElement = pActualElement->pPreviousFibElement;
		}
	}
	cFibElement* pLastFibElement = pActualElement->updateValues( NULL );
	
	if ( pLastFibElement != NULL ){
		return true;
	}//else an error has occured
	return false;
}


/**
 * This method updates the values/ properties off all Fib elements in
 * this Fib object beginning with this Fib element.
 * Every underobject should have all it's underobjects.
 *
 * @param previosFibElement the prvios Fib element to this Fib element
 * 	in the order of Fib elements; if it is NULL ther is no previos
 * 	Fib element to this
 * @param pNextArm the next arm Fib object in the next higher
 * 	Fib brancheelement
 * @return a pointer to the last evalued Fib element;
 * 	if NULL an error has occured
 */
cFibElement* cFibElement::updateValues( cFibElement *previosFibElement,
		cFibElement * pNextArm ){
	//BEWARE: This method works yust updates this Fib element and not more
	if ( previosFibElement != NULL ){
		pPreviousFibElement = previosFibElement;
	}
	if ( pNextFibElement != NULL ){
		pNextFibElement->pPreviousFibElement = this;
	}
	if ( (pSuperiorElement != NULL) && (pPreviousFibElement == NULL) ){
		pPreviousFibElement = pSuperiorElement;
	}
	if ( pPreviousFibElement == NULL ){
		pNextRootElement = NULL;
		uINumberOfFibElement = 1;
	}else{
		if ( pSuperiorElement ){
			if ( pSuperiorElement->getType() == 'r' ){
				//superior Fib element is the next root element
				pNextRootElement = (cRoot*)pSuperiorElement;
			}else{
				pNextRootElement = (cRoot*)(pSuperiorElement->pNextRootElement);
			}
		}else{
			pNextRootElement = NULL;
		}
		uINumberOfFibElement = pPreviousFibElement->getNumberOfElement() + 1;
		
		pPreviousFibElement->pNextFibElement = this;
	}
	return this;
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
 * 		next- Fib element and the underobjects
 */
void cFibElement::cutConnections( edDirection direction ){
	
	if ( (direction == ED_ALL) || (direction == ED_HIGHER) ||
			(direction == ED_HIGHER_EQUAL) ){
		pSuperiorElement     = NULL;
		pPreviousFibElement  = NULL;
		uINumberOfFibElement = 1;
	}
	if ( (direction == ED_ALL) || (direction == ED_BELOW) ||
			(direction == ED_BELOW_EQUAL) ){
		pNextFibElement = NULL;
	}
}

#endif //FEATURE_FAST_UPDATE


/**
 * This method moves a Fib limb element (cFibLimb) on the specified
 * position over uiHowfar Fib elements up.
 * Moving is stoped if an invalid Fib object would result (e.g. no Fib
 * element can be moved over an Fib elements that defines a variable
 * the moved Fib element uses).
 * Moving an Fib element into an listelement will result in an
 * listelement with the moved element in everyone of it's underobjects.
 *
 * @see moveLimbElement()
 * @see isDeletableElement()
 * @see removeElement()
 * @see getType()
 * @param cType the type of the Fib element to move
 * @param elementPoint the number of the Fib element, in the order of
 * 	Fib elements of the given type cType, to move
 * @param uiHowfar the number of Fib elements over which the to move
 * 	Fib element should be moved up
 * @param bAbsolute if the elementPoint is an absolute value for the wool
 * 	Fib object
 * @return the number of Fib Elements over which the to move Fib
 * 	element was moved
 */
intFib cFibElement::moveLimbElementUp( const char cType, const unsignedIntFib
		elementPoint, const unsignedIntFib uiHowfar, bool bAbsolute ){
	
	if ( uiHowfar == 0 ){
		//moved enougth
		return 0;
	}

	cFibElement * pFibElementToMove = getFibElement( cType, elementPoint, bAbsolute );
	//check if the Fib element is moveble
	if ( (pFibElementToMove == NULL) ||
			( ! pFibElementToMove->isMovable() ) ){
		//can't move the Fib element
		return 0;
	}
	if ( pFibElementToMove->pSuperiorElement == NULL ){
		//no element to move up over
		return 0;
	}

	//evalue the position wher to move to
	unsignedIntFib uiRemainingElementsToMoveUp = uiHowfar;
	cFibElement * pFibElementToReplace = pFibElementToMove;
	set<cFibVariable*> liUsedVariables = pFibElementToMove->getUsedVariables();
	
	while ( uiRemainingElementsToMoveUp != 0 ){
		//check if the pFibElementToMove can be moved over the next superior Fib element
		if ( pFibElementToReplace->pSuperiorElement->pSuperiorElement == NULL ){
			//can't move pFibElementToMove to the topmost position
			break;
		}
		if ( pFibElementToReplace->pSuperiorElement->getType() == 'r' ){
			//can't to move up over an root element
			break;
		}
		//check if a used variable is defined an an element to move over
		if ( ! liUsedVariables.empty() ){
			set<cFibVariable*>::const_iterator itrVariable;
			for ( itrVariable = liUsedVariables.begin();
					itrVariable != liUsedVariables.end(); itrVariable++ ){
				
				if ( pFibElementToReplace->pSuperiorElement->isDefinedVariable(
						*itrVariable, ED_POSITION ) ){
					break;
				}
			}
			if ( itrVariable != liUsedVariables.end() ){
				/*some varibles used in the pFibElementToMove are defined in the
				next superior Fib element -> cant move over the superior Fib element*/
				break;
			}
		}
		//can move over the superior Fib element
		pFibElementToReplace = pFibElementToReplace->pSuperiorElement;
		uiRemainingElementsToMoveUp--;
	}
	if ( pFibElementToReplace == pFibElementToMove ){
		//can't move up
		return 0;
	}

	unsignedIntFib uiFibElementToMovePosition = pFibElementToMove->getNumberOfElement();
	//cut element on old position and insert it on the new
	
	cFibElement * pCutFibElement = pFibElementToMove->pSuperiorElement->
		cutElement( 'u', uiFibElementToMovePosition, true, false );
		
	if ( pCutFibElement == NULL ){
		return 0;
	}
	const bool bFibElementInserted = pFibElementToReplace->pSuperiorElement->
		insertElement( pCutFibElement, 'u', pFibElementToReplace->
			getNumberOfElement(), true, false );
	
	if ( ! bFibElementInserted ){
		//error on inserting -> try to insert the cuted Fib element on the old position
		insertElement( pCutFibElement, 'u', uiFibElementToMovePosition, true, false );
		return 0;
	}
	
	return uiHowfar - uiRemainingElementsToMoveUp;
}


/**
 * @return the highest Fib element in the wool Fib object this
 * 	Fib element is part of
 */
cFibElement * cFibElement::getMasterRoot(){
	/*go to the most top/ superior Fib element and call this method non
	absolute*/
	cFibElement * pActualElement = this;
	while ( pActualElement->pSuperiorElement != NULL ){
		pActualElement = pActualElement->pSuperiorElement;
	}
	return pActualElement;
}


/**
 * @return the highest Fib element in the wool Fib object this
 * 	Fib element is part of
 */
cFibElement * cFibElement::getMasterRoot() const{
	/*go to the most top/ superior Fib element and call this method non
	absolute*/
	cFibElement * pActualElement = const_cast<cFibElement *>( this );
	while ( pActualElement->pSuperiorElement != NULL ){
		pActualElement = pActualElement->pSuperiorElement;
	}
	return pActualElement;
}


/**
 * This method will evalue if the needed variables can be replaced with
 * equal variables, which are defined for this Fib element.
 * If possible it will return a list (liOutVariablesToReplace) of
 * variable pairs, which have to be replaced.
 *
 * @see assignValues()
 * @see cFibVariable::equal()
 * @param setNeededVariables a set with the variables needed for this
 * 	Fib element
 * @param liOutVariablesToReplace a list to output the variables to replace:
 * 		first: the original needed variable to replace
 * 		second: the new variable to replace the original variable with
 * 	(Fib variables already defined for this Fib element won't be added
 * 	to this list.)
 * @return true if all variables can be replaced with for this Fib element
 * 	defined variables, else false
 */
bool cFibElement::getVariablesToReplace(
		const set< cFibVariable* > & setNeededVariables,
		list< pair< cFibVariable * ,cFibVariable * > > & liOutVariablesToReplace ){
	
	
	if ( setNeededVariables.empty() ){
		//no variables needed -> don't need to replace anything
		return true;
	}//else needed variables exists
	list< cFibVariable* > liDefinedVariables = getDefinedVariables( ED_HIGHER );
	set< cFibVariable* > setDefinedVariables(
		liDefinedVariables.begin(), liDefinedVariables.end() );
	
	/*for every needed variable in the given Fib element:
	- check if it is not defined above
	- for all needed but not defined above variables:
	-- try to find equivalent defined variable in Fib element above
		check with equal( const cFibVariable &variable, false )
	*/
	list< cFibVariable* > liVariablesNeededButNotDefined;
	for ( set< cFibVariable* >::const_iterator
			itrUsedVariable = setNeededVariables.begin();
			itrUsedVariable != setNeededVariables.end(); itrUsedVariable++ ){
		
		if ( setDefinedVariables.find( *itrUsedVariable ) ==
				setDefinedVariables.end() ){
			//variable needed but not defined above
			liVariablesNeededButNotDefined.push_back( *itrUsedVariable );
		}
	}//end for find all needed but not defined above variables
	
	list< cFibVariable* >::const_reverse_iterator itrDefVariable;
	for ( list< cFibVariable* >::const_iterator
			itrUsedVariable = liVariablesNeededButNotDefined.begin();
			itrUsedVariable != liVariablesNeededButNotDefined.end();
			itrUsedVariable++ ){
		
		for ( itrDefVariable = liDefinedVariables.rbegin();
				itrDefVariable != liDefinedVariables.rend();
				itrDefVariable++ ){
			if ( (*itrUsedVariable)->equal( **itrDefVariable ) ){
				//equal defined variable found -> add pair
				liOutVariablesToReplace.push_back(
					pair< cFibVariable * ,cFibVariable * >(
						*itrUsedVariable, *itrDefVariable ) );
				break;
			}
			
		}//end for all defined variables
		if ( itrDefVariable == liDefinedVariables.rend() ){
			/*can't find equivalent defined variable for needed variable above
			 -> can't assign values*/
			return false;
		}
	}//end for all needed but not defined above variables
	return true;
}














