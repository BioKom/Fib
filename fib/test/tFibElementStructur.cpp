/**
 * @file tFibElementStructur
 * file name: tFibElementStructur.cpp
 * @author Betti Oesterholz
 * @date 20.12.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the structur of Fib objects.
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
 * This test is for testing the structur of Fib objects.
 * The methods building, change and evalue the structur of Fib elements
 * in Fib objects are tested.
 *
 *
 * What's tested of class cFibElement -classes:
 * 	- cFibElement * getSuperiorFibElement();
 * 	- cFibElement *getNextFibElement();
 * 	- cFibElement *getNextFibElement( char cType );
 * 	- cFibElement *getConstFibElement( longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( longFib lNumber, bool bAbsolute=false );
 * 	- cFibElement *getConstFibElement( char cType, longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( char cType, longFib lNumber, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfSubobjects() const = 0;
 * 	- cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 )
 * 	- const cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 ) const
 * 	- list< cFibElement * > getSubobjects()
 * 	- list< const cFibElement * > getSubobjects() const
 * 	- cRoot * getSuperiorRootElement()
 * 	- const cRoot * getSuperiorRootElement() const
 * 	- unsignedIntFib getNumberOfElement( bool bOfType=false ) const;
 * 	- unsignedIntFib getNumberOfMovePoint( ) const;
 * 	- unsignedIntFib getNumberOfObjectPoint() const;
 * 	- list<cFibElement*> getAllFibElements( char cTypeBasis='u', longFib lNumber=1, char cType='u', edDirection direction=ED_ALL, unsignedLongFib lNumberOfMaxReturnedElements=0, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfElements( char cType='u' ) const;
 * 	- unsignedIntFib getNumberOfMovePoints() const;
 * 	- unsignedIntFib getNumberOfObjectPoints() const;
 * 	- unsignedIntFib typeElementPointToElementPoint( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- list<unsignedIntFib> elementPointToObjectPoints( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- unsignedIntFib objectPointToElementPoint( const unsignedIntFib uiObjectPoint, bool bAbsolute=false ) const;
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType='u', const unsignedIntFib elementPoint=0, bool bDeleteOld=true, bool bAbsolute=false );
 * 	--(TODO) check when the subobject to overwrite is NULL
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=true, bool bAbsolute=false );
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType='u', const unsignedIntFib elementPoint=0, bool first=true, bool bAbsolute=false );
 * 	--(TODO) check when the subobject to overwrite is NULL
 * 	- bool hasUnderAllObjects() const;
 * 	--TODO? for branch elements wher subobjects are removed
 * 	- bool insertElement( cFibElement *fibElement, const char cType='u', const unsignedIntFib elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true, bool bCheckVariables=true );
 * 	- bool isRemovableElement( const char cType='u', const unsignedIntFib elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true ) const;
 * 	- bool removeElement(  const char cType='u', const unsignedIntFib  elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );
 * 	- cFibElement *cutElement( const char cType='u', const unsignedIntFib elementPoint=0, bool bAbsolute=false, bool bCheckVariables=true );
 * 	- bool equal( const cFibElement & fibObject ) const;
 * 	- intFib moveLimbElement( const char cType='u', const unsignedIntFib  elementPoint=0, const intFib iHowfar=1, bool bAbsolute=false );
 * 	- cFibElement *clone( ) const;
 * 	- cFibElement *copy( const unsignedIntFib iObjectPoint=0 ) const;
 * 	- cFibElement *copyElement( const char cType='u', const unsignedIntFib elementPoint=0, bool bAbsolute=true ) const;
 * 	- bool assignValues( const cFibElement & fibElement );
 *
 * 	-(TODO: when other variable definers are defined) bool equalValuesSet( const cFibVariable * variableOwn, const cFibElement & fibElement, const cFibVariable * variable ) const;
 * 	- void deleteObject( cFibElement * fibObject );
 *
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 *
 * call: tFibElementStructur [MAX_SIZE] [ITERATIONS]
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
25.04.2010  Oesterholz  cFunction added
01.08.2010  Oesterholz  cComment added
01.08.2010  Oesterholz  cIf added
25.08.2011  Oesterholz  underarea to subarea
06.10.2011  Oesterholz  cExtObject included
07.11.2011  Oesterholz  ExternUnderObjects to ExternSubobjects
19.11.2011  Oesterholz  cExtSubobject included; cFibSet and cFibMatrix prepared
18.01.2012  Oesterholz  cFibSet and cFibMatrix included
25.01.2012  Oesterholz  input values changed to input vector
04.02.2012  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR implemented:
	the input values are now a vector of values
10.07.2013  Oesterholz  test for *Subobject* methods and
	getSuperiorRootElement() implemented
01.08.2013  Oesterholz  FEATURE_EXT_SUBOBJECT_INPUT_VECTOR as default (not case removed)
01.08.2013  Oesterholz  test for assignValues() added
01.10.2013  Oesterholz  memory error fixed: not initialized counter in for loop
14.11.2013  Oesterholz  FEATURE_INSERT_OBJECT_IN_ELEMENT implemented
*/



#include "version.h"

#include "cRoot.h"
#include "cList.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cArea.h"
#include "cFunction.h"
#include "cIf.h"
#include "cComment.h"
#include "cExtObject.h"
#include "cExtSubobject.h"
#include "cFibSet.h"
#include "cFibMatrix.h"
#include "cFunctionVariable.h"
#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"


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


int testStructurRandom( unsigned long &ulTestphase, unsigned int uiMaxSize, unsigned int uiIterations, unsigned int uiTestType, unsigned int uiStepSize );
int testOnTwoEqualStructurRandom( unsigned long &ulTestphase, unsigned int uiMaxSize, unsigned int uiIterations, unsigned int uiTestType, unsigned int uiStepSize );
int testRandFunInRow( unsigned long &ulTestphase, unsigned int uiMaxSize, unsigned int uiIterations, unsigned int uiStepSize );

int testStructurOnObject( cFibElement * fibObject, bool bPrintMessages=true );
int testGetNumberOfCountOnObject( cFibElement * pFibObject );
int testGetAllFibElementsOnObject( cFibElement * pFibObject );
int testTypeElementPointToElementPointOnObject( cFibElement * pFibObject );
int testObjectPointOnObject( cFibElement * pFibObject );
int testOverwriteObjectWithObjectOnObject( cFibElement * pFibObject, bool bDeleteOld=true );
int testOverwriteObjectWithObjectAbsoluteOnObject( cFibElement * pFibObject, bool bDeleteOld=true );
int testRemoveObjectOnObject( cFibElement * pFibObject, bool bDeleteOld=true );
int testRemoveObjectAbsoluteOnObject( cFibElement * pFibObject, bool bDeleteOld=true );
int testInsertObjectInElementObjectFirstOnObject( cFibElement * pFibObject );
int testInsertObjectInElementObjectFirstAbsoluteOnObject( cFibElement * pFibObject );
int testInsertObjectInElementObjectSecondOnObject( cFibElement * pFibObject );
int testInsertObjectInElementObjectSecondAbsoluteOnObject( cFibElement * pFibObject );
int testHasUnderAllObjectsForLimbOnObject( cFibElement * pFibObject );
int testInsertElementOnObject( cFibElement * pFibObject, bool bCheckVariables=true );
int testInsertElementAbsoluteOnObject( cFibElement * pFibObject, bool bCheckVariables=true );
int testInsertElementNullOnObject( cFibElement * pFibObject, bool bCheckVariables=true );
int testRemoveElementOnObject( cFibElement * pFibObject, bool bCut=true, bool bCheckVariables=true );
int testRemoveElementAbsoluteOnObject( cFibElement * pFibObject, bool bCut=true, bool bCheckVariables=true );
int testMoveLimbElementUpOnObject( cFibElement * pFibObject, bool bAbsolute );
int testMoveLimbElementDownOnObject( cFibElement * pFibObject, bool bAbsolute );
int testCopyElementOnObject( cFibElement * pFibObject, bool bAbsolute );
int testCopyOnObject( cFibElement * pFibObject );
int testAssignValues( cFibElement * pFibObject );

int testEqualOnTwoObject( cFibElement * pFibObject1, cFibElement * pFibObject2 );
int testMoveLimbElementOnNonMovebelOnObject( cFibElement * pFibObject1, cFibElement * pFibObject2 );
int testCloneOnObject( cFibElement * pFibObject1, cFibElement * pFibObject2 );


//parameters for the generator
const unsigned int uiNumberOfDimensions = 2;

list< cTypeProperty > liPossiblePropertytyps;
const unsigned int uiMaxVectorElementNumber = 1023;

list< pair< char, double > > liFractionOfFibElements;


int main(int argc, char* argv[]){

	unsigned long ulTestphase = 0;//actual phase of the test 
	int iReturn = 0;//return value of the test; the number of occured errors
	
	srand( time(NULL) );
	const time_t timeStart = time( 0 );
	
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::COLOR_RGB, uiNumberOfDimensions ) );
	liPossiblePropertytyps.push_back( cTypeProperty( cTypeProperty::SOUND, uiNumberOfDimensions ) );
	
	liFractionOfFibElements.push_back( make_pair( 'p', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'y', 1.0 ) );
	liFractionOfFibElements.push_back( make_pair( 'a', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'f', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'i', 0.3 ) );
	liFractionOfFibElements.push_back( make_pair( 'l', 0.5 ) );
	liFractionOfFibElements.push_back( make_pair( 'c', 0.2 ) );
	liFractionOfFibElements.push_back( make_pair( 'o', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 's', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'v', 0.1 ) );
	liFractionOfFibElements.push_back( make_pair( 'm', 0.1 ) );
	//TODO: more Fib elements

	
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

	cout<<endl<<"Running Test for structurs of Fib objects"<<endl;
	cout<<      "========================================="<<endl;
	
/*TODO comment in:
*/
	//test basic structure
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 1, 2 );
	
	//test overwriteObjectWithObject()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 5, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 6, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 7, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 8, 4  );

	//test removeObject()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 10, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 11, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 12, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 13, 4  );

	//test insertObjectInElement()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 20, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 21, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 22, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 23, 4  );

	//hasUnderAllObjects()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 30, 4  );

	//test insertElement()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 40, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 41, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 42, 8  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 43, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 44, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 45, 8  );

	//test cutElement()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 50, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 51, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 52, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 53, 4  );
	//test removeElement()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 55, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 56, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 57, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 58, 4  );
	
	//test equal()
	iReturn += testOnTwoEqualStructurRandom( ulTestphase, uiMaxSize, uiIterations, 1, 4 );

	//test moveLimbElement();
	iReturn += testOnTwoEqualStructurRandom( ulTestphase, uiMaxSize, uiIterations, 10, 4 );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 60, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 61, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 62, 2  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 63, 4  );
	
	//clone()
	iReturn += testOnTwoEqualStructurRandom( ulTestphase, uiMaxSize, uiIterations, 20, 2 );
	//copyElement()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 70, 4  );
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 71, 8  );
	
	//copy()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 72, 8 );
	
	//assignValues()
	iReturn += testStructurRandom( ulTestphase, uiMaxSize, uiIterations, 73, 8 );
	
	//test to call some random functions in in a row
	iReturn += testRandFunInRow( ulTestphase, uiMaxSize, uiIterations, 8 );
	
	
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
 * This function chooses a randon Fib element type and gives it character back.
 * Fib elements implemented:
 * 	- 'u': all
 * 	- 'r': cRoot
 * 	- 'p': cPoint
 * 	- 'y': cProperty
 * 	- 'l': cList
 * 	- 'a': cArea
 * 	- 'f': cFunction
 * 	- 'i': cIf
 * 	- 'c': cComment
 * 	- 'o': cExtObject
 * 	- 'e': cExtSubobject
 * 	- 'v': cFibSet
 * 	- 'm': cFibMatrix
 *
 * @param szRetNameActualType in this string the name of the type if given back
 *	@return a character for the choosen type
 */
char choosRandomType( string & szRetNameActualType ){

	int iRandom = rand() % 13;

	char cActualType = 'u';
	switch ( iRandom ){
		case 1:{
			cActualType = 'r';
			szRetNameActualType = "root";
		}break;
		case 2:{
			cActualType = 'p';
			szRetNameActualType = "point";
		}break;
		case 3:{
			cActualType = 'y';
			szRetNameActualType = "property";
		}break;
		case 4:{
			cActualType = 'l';
			szRetNameActualType = "list";
		}break;
		case 5:{
			cActualType = 'a';
			szRetNameActualType = "area";
		}break;
		case 6:{
			cActualType = 'f';
			szRetNameActualType = "function";
		}break;
		case 7:{
			cActualType = 'i';
			szRetNameActualType = "if";
		}break;
		case 8:{
			cActualType = 'c';
			szRetNameActualType = "comment";
		}break;
		case 9:{
			cActualType = 'o';
			szRetNameActualType = "external object";
		}break;
		case 10:{
			cActualType = 's';
			szRetNameActualType = "external subobject";
		}break;
		case 11:{
			cActualType = 'v';
			szRetNameActualType = "set-element";
		}break;
		case 12:{
			cActualType = 'm';
			szRetNameActualType = "matrix element";
		}break;
		default:{//0
			cActualType = 'u';
			szRetNameActualType = "all";
		}break;
	}
	return cActualType;
}


/**
 * This function chooses a randon Fib element type and gives it character back.
 *
 * @see choosRandomType();
 * @return a character for the choosen type
 */
char choosRandomType(){

	string szNameActualType( "all" );
	return choosRandomType( szNameActualType );
}


/**
 * This function tests the Fib structur methods in random generated Fib objects.
 *
 * methods tested with uiTestType=1 :
 * 	- cFibElement * getSuperiorFibElement();
 * 	- cFibElement *getNextFibElement();
 * 	- cFibElement *getNextFibElement( char cType );
 * 	- cFibElement *getConstFibElement( longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( longFib lNumber, bool bAbsolute=false );
 * 	- cFibElement *getConstFibElement( char cType, longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( char cType, longFib lNumber, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfSubobjects() const = 0;
 * 	- cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 )
 * 	- const cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 ) const
 * 	- list< cFibElement * > getSubobjects()
 * 	- list< const cFibElement * > getSubobjects() const
 * 	- cRoot * getSuperiorRootElement()
 * 	- const cRoot * getSuperiorRootElement() const
 * 	- list<cFibElement*> getAllFibElements( char cTypeBasis='u', longFib lNumber=1, char cType='u', edDirection direction=ED_ALL, unsignedLongFib lNumberOfMaxReturnedElements=0, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfElement( bool bOfType=false ) const;
 * 	- unsignedIntFib getNumberOfMovePoint( ) const;
 * 	- unsignedIntFib getNumberOfObjectPoint() const;
 * 	- unsignedIntFib getNumberOfElements( char cType='u' ) const;
 * 	- unsignedIntFib getNumberOfMovePoints() const;
 * 	- unsignedIntFib getNumberOfObjectPoints() const;
 * 	- unsignedIntFib typeElementPointToElementPoint( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- list<unsignedIntFib> elementPointToObjectPoints( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- unsignedIntFib objectPointToElementPoint( const unsignedIntFib uiObjectPoint, bool bAbsolute=false ) const;
 * 	- bool hasUnderAllObjects() const;
 * 	- bool assignValues( const cFibElement & fibElement );
 *
 *
 * methods tested with uiTestType=5 :
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=true, bool bAbsolute=false );
 *
 * methods tested with uiTestType=6 :
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=false, bool bAbsolute=false );
 *
 * methods tested with uiTestType=7 :
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=true, bool bAbsolute=true );
 *
 * methods tested with uiTestType=8 :
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=false, bool bAbsolute=true );
 *
 *
 * methods tested with uiTestType=10 :
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=true, bool bAbsolute=false );
 *
 * methods tested with uiTestType=11 :
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=false, bool bAbsolute=false );
 *
 * methods tested with uiTestType=12 :
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=true, bool bAbsolute=true );
 *
 * methods tested with uiTestType=13 :
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=false, bool bAbsolute=true );
 *
 *
 * methods tested with uiTestType=20 :
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=false );
 *
 * methods tested with uiTestType=21 :
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=true );
 *
 * methods tested with uiTestType=22 :
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=false );
 *
 * methods tested with uiTestType=23 :
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=true );
 *
 *
 * methods tested with uiTestType=30 :
 * 	- bool hasUnderAllObjects(); wher a limbelement is missing it's subobject
 *
 *
 * methods tested with uiTestType=40 :
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true )
 *
 * methods tested with uiTestType=41 :
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=true )
 *
 * methods tested with uiTestType=42 :
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true ); where the inserted Fib element sould replace a NULL subobject
 *
 * methods tested with uiTestType=43 :
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false )
 *
 * methods tested with uiTestType=44 :
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=false )
 *
 * methods tested with uiTestType=45 :
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false ); where the inserted Fib element sould replace a NULL subobject
 *
 *
 * methods tested with uiTestType=50 till 53 :
 * 	-  bool isRemovableElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables ) const;
 *
 * methods tested with uiTestType=50 :
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true );
 *
 * methods tested with uiTestType=51 :
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false );
 *
 * methods tested with uiTestType=52 :
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true );
 *
 * methods tested with uiTestType=53 :
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false );
 *
 * methods tested with uiTestType=55 till 58 :
 * 	-  bool isRemovableElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables ) const;
 *
 * methods tested with uiTestType=55 :
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=true );
 *
 * methods tested with uiTestType=56 :
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=false );
 *
 * methods tested with uiTestType=57 :
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=true );
 *
 * methods tested with uiTestType=58 :
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=false );
 *
 *
 * methods tested with uiTestType=60 :
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar<=0, bool bAbsolute=false ); on an limbelement
 *
 * methods tested with uiTestType=61 :
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar<=0, bool bAbsolute=true ); on an limbelement
 *
 * methods tested with uiTestType=62 :
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar>=0, bool bAbsolute=false ); on an limbelement
 *
 * methods tested with uiTestType=63 :
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar>=0, bool bAbsolute=true ); on an limbelement
 *
 *
 * methods tested with uiTestType=70 :
 * 	- cFibElement *copyElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 *
 * methods tested with uiTestType=71 :
 * 	- cFibElement *copyElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true ) const;
 *
 * methods tested with uiTestType=72 :
 * 	-  cFibElement *copy( const unsignedIntFib iObjectPoint ) const;
 *
 * methods tested with uiTestType=73 :
 * 	- bool assignValues( const cFibElement & fibElement );
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiMaxSize a number for the till wich size the Fib object
 * 	generator should generate Fib objects
 * @param uiIterations how mony Fib objects should be generated for each
 * 	set of parameters for the Fib object generator
 * @param uiTestType the type of thest that should be performed (see above)
 * @param uiStepSize the number with which the to generate size is multiplyted each step
 * @return the number of erros occured in the test
 */
int testStructurRandom( unsigned long &ulTestphase, unsigned int uiMaxSize,
		unsigned int uiIterations, unsigned int uiTestType = 1,
		unsigned int uiStepSize = 2 ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	switch ( uiTestType ){
		case 1:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing methods to check the Fib object structur on random generated Fib objects"<<endl;
		}break;
		case 5:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=false)"<<endl;
		}break;
		case 6:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=false)"<<endl;
		}break;
		case 7:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=true)"<<endl;
		}break;
		case 8:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=true)"<<endl;
		}break;
		case 10:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=false)"<<endl;
		}break;
		case 11:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=false)"<<endl;
		}break;
		case 12:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=true)"<<endl;
		}break;
		case 13:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=true)"<<endl;
		}break;
		case 20:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=true and bAbsolute=false)"<<endl;
		}break;
		case 21:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=true and bAbsolute=true)"<<endl;
		}break;
		case 22:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=false and bAbsolute=false)"<<endl;
		}break;
		case 23:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=false and bAbsolute=true)"<<endl;
		}break;
		case 30:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the hasUnderAllObjects() method on random generated Fib objects wher a limbelement is missing it's subobject"<<endl;
		}break;
		case 40:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=false)"<<endl;
		}break;
		case 41:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects(with bCheckVariables=true and bAbsolute=true)"<<endl;
		}break;
		case 42:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects, where the inserted Fib element sould replace a NULL subobject (with bCheckVariables=true and bAbsolute=true)"<<endl;
		}break;
		case 43:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=false)"<<endl;
		}break;
		case 44:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects(with bCheckVariables=false and bAbsolute=true)"<<endl;
		}break;
		case 45:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects, where the inserted Fib element sould replace a NULL subobject (with bCheckVariables=false and bAbsolute=true)"<<endl;
		}break;
		case 50:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=false)"<<endl;
		}break;
		case 51:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=false)"<<endl;
		}break;
		case 52:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=false)"<<endl;
		}break;
		case 53:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=false)"<<endl;
		}break;
		case 55:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=true)"<<endl;
		}break;
		case 56:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=true)"<<endl;
		}break;
		case 57:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=true)"<<endl;
		}break;
		case 58:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=true)"<<endl;
		}break;
		case 60:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement up (with bAbsolute=false)"<<endl;
		}break;
		case 61:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement up (with bAbsolute=true)"<<endl;
		}break;
		case 62:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement down (with bAbsolute=false)"<<endl;
		}break;
		case 63:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement down (with bAbsolute=true)"<<endl;
		}break;
		case 70:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the copyElement() method on random generated Fib objects (with bAbsolute=false)"<<endl;
		}break;
		case 71:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the copyElement() method on random generated Fib objects (with bAbsolute=true)"<<endl;
		}break;
		case 72:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the copy() method on random generated Fib objects"<<endl;
		}break;
		
		case 73:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the assignValues() method on random generated Fib objects"<<endl;
		}break;
		
		default:
			cerr<<"No test to evalue choosen"<<endl;
			iReturn++;
			return iReturn;
	}

	//generate random objects

	cout<<"The maximal size for generated Fib objects is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameterset is: "<< uiIterations <<endl;
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth *= 2 ){// * 3
	for ( unsigned int uiNumberOfAverageInputVariables = 3; uiNumberOfAverageInputVariables <= 15;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 3
	for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.5 ){// * 3
	for ( unsigned int uiSize = pow( uiAverageSubRoots, uiAverageSubRootsDepth ) * 4; uiSize < uiMaxSize; uiSize *= uiStepSize ){
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
			cout<<" generated "<<flush<<endl;
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
				" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<flush<<endl;
			iReturn++;
			
			continue;
		}
		unsigned int uiErrorsInTests = 0;
		switch ( uiTestType ){
			case 1:{
				uiErrorsInTests += testStructurOnObject( pGeneratedFibObject );
				uiErrorsInTests += testGetNumberOfCountOnObject( pGeneratedFibObject );
				uiErrorsInTests += testGetAllFibElementsOnObject( pGeneratedFibObject );
				uiErrorsInTests += testTypeElementPointToElementPointOnObject( pGeneratedFibObject );
				uiErrorsInTests += testObjectPointOnObject( pGeneratedFibObject);
			}break;
			case 5:{
				uiErrorsInTests += testOverwriteObjectWithObjectOnObject( pGeneratedFibObject, true );
			}break;
			case 6:{
				uiErrorsInTests += testOverwriteObjectWithObjectOnObject( pGeneratedFibObject, false );
			}break;
			case 7:{
				uiErrorsInTests += testOverwriteObjectWithObjectAbsoluteOnObject( pGeneratedFibObject, true );
			}break;
			case 8:{
				uiErrorsInTests += testOverwriteObjectWithObjectAbsoluteOnObject( pGeneratedFibObject, false );
			}break;
			case 10:{
				uiErrorsInTests += testRemoveObjectOnObject( pGeneratedFibObject, true );
			}break;
			case 11:{
				uiErrorsInTests += testRemoveObjectOnObject( pGeneratedFibObject, false );
			}break;
			case 12:{
				uiErrorsInTests += testRemoveObjectAbsoluteOnObject( pGeneratedFibObject, true );
			}break;
			case 13:{
				uiErrorsInTests += testRemoveObjectAbsoluteOnObject( pGeneratedFibObject, false );
			}break;
			case 20:{
				uiErrorsInTests += testInsertObjectInElementObjectFirstOnObject( pGeneratedFibObject );
			}break;
			case 21:{
				uiErrorsInTests += testInsertObjectInElementObjectFirstAbsoluteOnObject( pGeneratedFibObject );
			}break;
			case 22:{
				uiErrorsInTests += testInsertObjectInElementObjectSecondOnObject( pGeneratedFibObject );
			}break;
			case 23:{
				uiErrorsInTests += testInsertObjectInElementObjectSecondAbsoluteOnObject( pGeneratedFibObject );
			}break;
			case 30:{
				uiErrorsInTests += testHasUnderAllObjectsForLimbOnObject( pGeneratedFibObject );
			}break;
			case 40:{
				uiErrorsInTests += testInsertElementOnObject( pGeneratedFibObject, true );
			}break;
			case 41:{
				uiErrorsInTests += testInsertElementAbsoluteOnObject( pGeneratedFibObject, true );
			}break;
			case 42:{
				uiErrorsInTests += testInsertElementNullOnObject( pGeneratedFibObject, true );
			}break;
			case 43:{
				uiErrorsInTests += testInsertElementOnObject( pGeneratedFibObject, false );
			}break;
			case 44:{
				uiErrorsInTests += testInsertElementAbsoluteOnObject( pGeneratedFibObject, false );
			}break;
			case 45:{
				uiErrorsInTests += testInsertElementNullOnObject( pGeneratedFibObject, false );
			}break;
			case 50:{
				uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, true, true );
			}break;
			case 51:{
				uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, true, false );
			}break;
			case 52:{
				uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, false, true );
			}break;
			case 53:{
				uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, false, false );
			}break;
			case 55:{
				uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, true, true );
			}break;
			case 56:{
				uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, true, false );
			}break;
			case 57:{
				uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, false, true );
			}break;
			case 58:{
				uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, false, false );
			}break;
			case 60:{
				uiErrorsInTests += testMoveLimbElementUpOnObject( pGeneratedFibObject, false );
			}break;
			case 61:{
				uiErrorsInTests += testMoveLimbElementUpOnObject( pGeneratedFibObject, true );
			}break;
			case 62:{
				uiErrorsInTests += testMoveLimbElementDownOnObject( pGeneratedFibObject, false );
			}break;
			case 63:{
				uiErrorsInTests += testMoveLimbElementDownOnObject( pGeneratedFibObject, true );
			}break;
			case 70:{
				uiErrorsInTests += testCopyElementOnObject( pGeneratedFibObject, false );
			}break;
			case 71:{
				uiErrorsInTests += testCopyElementOnObject( pGeneratedFibObject, true );
			}break;
			case 72:{
				uiErrorsInTests += testCopyOnObject( pGeneratedFibObject );
			}break;
			case 73:{
				uiErrorsInTests += testAssignValues( pGeneratedFibObject );
			}break;
		}

		iReturn += uiErrorsInTests;

		if ( uiErrorsInTests != 0 ){
			//write Fib object wher orror occured to folder
			char szFileNameBuffer[256];
			sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%uTT%u%s",
				DIR_OUTPUT, "structurError", uiSize,
				uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
				uiMaxVectorElementNumber, uiIteration, uiTestType ,".xml" );
				
			cerr<<"Error: The Fib object where the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
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




/**
 * This function tests the equal method in random generated Fib objects.
 *
 * methods tested with uiTestType=1 :
 * 	- bool equal( const cFibElement & fibObject ) const;
 *
 * methods tested with uiTestType=10 :
 * 	- bool intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar, bool bAbsolute );
 * 		with trying to move Fib element that are not movebel
 *
 * methods tested with uiTestType=20 :
 * 	- cFibElement *clone() const;
 *
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiMaxSize a number for the till wich size the Fib object
 * 	generator should generate Fib objects
 * @param uiIterations how mony Fib objects should be generated for each
 * 	set of parameters for the Fib object generator
 * @param uiTestType the type of thest that should be performed (see above)
 * @param uiStepSize the number with which the to generate size is multiplyted each step
 * @return the number of erros occured in the test
 */
int testOnTwoEqualStructurRandom( unsigned long &ulTestphase, unsigned int uiMaxSize,
		unsigned int uiIterations, unsigned int uiTestType = 1,
		unsigned int uiStepSize = 2 ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	
	unsigned long uiActualRandomInit = time(NULL);

	switch ( uiTestType ){
		case 1:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the equal() method on two equal random generated Fib objects"<<endl;
		}break;
		case 10:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method, with trying to move Fib element that are not movebel"<<endl;
		}break;
		case 20:{
			cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the clone() method"<<endl;
		}break;
		
		default:
			cerr<<"No test to evalue choosen"<<endl;
			iReturn++;
			return iReturn;
	}

	//generate random objects

	cout<<"The maximal size for generated Fib objects is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameterset is: "<< uiIterations <<endl;
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth *= 2 ){// * 3
	for ( unsigned int uiNumberOfAverageInputVariables = 3; uiNumberOfAverageInputVariables <= 15;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 3
	for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.5 ){// * 3
	for ( unsigned int uiSize = pow( uiAverageSubRoots, uiAverageSubRootsDepth ) * 4; uiSize < uiMaxSize; uiSize *= uiStepSize ){
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
		
		srand( uiActualRandomInit );
		
		cFibElement * pGeneratedFibObject1 = generateFibObject( uiSize,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		srand( uiActualRandomInit );
		
		cFibElement * pGeneratedFibObject2 = generateFibObject( uiSize,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		uiActualRandomInit++;
		
		
		if ( pGeneratedFibObject1 && pGeneratedFibObject2 ){
			if ( pGeneratedFibObject1 ){
				cout<<" object 1 generated";
			}
			if ( pGeneratedFibObject2 ){
				cout<<" object 2 generated";
			}
			cout<<endl;
			
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
		unsigned int uiErrorsInTests = 0;
		
		switch ( uiTestType ){
			case 1:{
				uiErrorsInTests += testEqualOnTwoObject( pGeneratedFibObject1, pGeneratedFibObject2 );
			}break;
			case 10:{
				uiErrorsInTests += testMoveLimbElementOnNonMovebelOnObject( pGeneratedFibObject1, pGeneratedFibObject2 );
			}break;
			case 20:{
				uiErrorsInTests += testCloneOnObject( pGeneratedFibObject1, pGeneratedFibObject2 );
			}break;

		}
		
		iReturn += uiErrorsInTests;

		if ( uiErrorsInTests != 0 ){
			//write Fib object wher orror occured to folder
			char szFileNameBuffer[256];
			sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%uTT%uOb1%s",
				DIR_OUTPUT, "structurError", uiSize,
				uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
				uiMaxVectorElementNumber, uiIteration, uiTestType ,".xml" );
				
			cerr<<"Error: The Fib object where the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
				
			ofstream * pFile = new ofstream( szFileNameBuffer );
				
			bool bStoreSuccesfull = pGeneratedFibObject1->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){

				cerr<<"Error: Storing the data of the generated Fib object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
				
			sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%uTT%uOb2%s",
				DIR_OUTPUT, "structurError", uiSize,
				uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
				uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
				uiMaxVectorElementNumber, uiIteration, uiTestType ,".xml" );
				
			cerr<<"Error: The Fib object where the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
			pFile = new ofstream( szFileNameBuffer );
			
			bStoreSuccesfull = pGeneratedFibObject2->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){

				cerr<<"Error: Storing the data of the generated Fib object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}

		}
		cFibElement::deleteObject( pGeneratedFibObject1 );
		cFibElement::deleteObject( pGeneratedFibObject2 );

	}}}}}}
	
	return iReturn;
}



/**
 * This function tests the Fib structur methods in random generated
 * Fib objects with some random structur functions test in a row.
 *
 * methods tested:
 * 	- cFibElement * getSuperiorFibElement();
 * 	- cFibElement *getNextFibElement();
 * 	- cFibElement *getNextFibElement( char cType );
 * 	- cFibElement *getConstFibElement( longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( longFib lNumber, bool bAbsolute=false );
 * 	- cFibElement *getConstFibElement( char cType, longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( char cType, longFib lNumber, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfSubobjects() const = 0;
 * 	- cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 )
 * 	- const cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 ) const
 * 	- list< cFibElement * > getSubobjects()
 * 	- list< const cFibElement * > getSubobjects() const
 * 	- cRoot * getSuperiorRootElement()
 * 	- const cRoot * getSuperiorRootElement() const
 * 	- list<cFibElement*> getAllFibElements( char cTypeBasis='u', longFib lNumber=1, char cType='u', edDirection direction=ED_ALL, unsignedLongFib lNumberOfMaxReturnedElements=0, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfElement( bool bOfType=false ) const;
 * 	- unsignedIntFib getNumberOfMovePoint( ) const;
 * 	- unsignedIntFib getNumberOfObjectPoint() const;
 * 	- unsignedIntFib getNumberOfElements( char cType='u' ) const;
 * 	- unsignedIntFib getNumberOfMovePoints() const;
 * 	- unsignedIntFib getNumberOfObjectPoints() const;
 * 	- unsignedIntFib typeElementPointToElementPoint( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- list<unsignedIntFib> elementPointToObjectPoints( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- unsignedIntFib objectPointToElementPoint( const unsignedIntFib uiObjectPoint, bool bAbsolute=false ) const;
 * 	- bool hasUnderAllObjects() const;
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=true, bool bAbsolute=false );
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=false, bool bAbsolute=false );
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=true, bool bAbsolute=true );
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld=false, bool bAbsolute=true );
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=true, bool bAbsolute=false );
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=false, bool bAbsolute=false );
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=true, bool bAbsolute=true );
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld=false, bool bAbsolute=true );
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=false );
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=true );
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=false );
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=true );
 * 	- bool hasUnderAllObjects(); wher a limbelement is missing it's subobject
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true )
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=true )
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false )
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=false )
 * 	-  bool isRemovableElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables ) const;
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true );
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false );
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=true );
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables=false );
 * 	-  bool isRemovableElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables ) const;
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=true );
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=false );
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=true );
 * 	- bool removeElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables=false );
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar<=0, bool bAbsolute=false ); on an limbelement
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar<=0, bool bAbsolute=true ); on an limbelement
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar>=0, bool bAbsolute=false ); on an limbelement
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar>=0, bool bAbsolute=true ); on an limbelement
 * 	- cFibElement *copyElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- cFibElement *copyElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true ) const;
 * 	-  cFibElement *copy( const unsignedIntFib iObjectPoint ) const;
 *
 *
 * @param ulTestphase a reference to the number for the testphase
 * @param uiMaxSize a number for the till wich size the Fib object
 * 	generator should generate Fib objects
 * @param uiIterations how mony Fib objects should be generated for each
 * 	set of parameters for the Fib object generator
 * @param uiStepSize the number with which the to generate size is multiplyted each step
 * @return the number of erros occured in the test
 */
int testRandFunInRow( unsigned long &ulTestphase, unsigned int uiMaxSize,
		unsigned int uiIterations, unsigned int uiStepSize = 8 ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	ulTestphase++;
	cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing Fib structur methods in random generated Fib objects with some random structur functions test in a row"<<endl;
	

	//generate random objects

	cout<<"The maximal size for generated Fib object is: "<< uiMaxSize <<endl;
	cout<<"The number of iterations per parameter set is: "<< uiIterations <<endl;
	
	for ( unsigned int uiAverageSubRoots = 1 ; uiAverageSubRoots <= 16; uiAverageSubRoots *= 4 ){// * 3
	for ( unsigned int uiAverageSubRootsDepth = 1; uiAverageSubRootsDepth <= 4 ; uiAverageSubRootsDepth *= 2 ){// * 3
	for ( unsigned int uiNumberOfAverageInputVariables = 3; uiNumberOfAverageInputVariables <= 15;
			uiNumberOfAverageInputVariables = (unsigned int)(uiNumberOfAverageInputVariables * 2 + 1) ){// * 3
	for ( double dFractionsOfUsedVariables = 0.0; dFractionsOfUsedVariables <= 1.0; dFractionsOfUsedVariables += 0.5 ){// * 3
	for ( unsigned int uiSize = pow( uiAverageSubRoots, uiAverageSubRootsDepth ) * 4; uiSize < uiMaxSize; uiSize *= uiStepSize ){
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
			cout<<" generated"<<flush<<endl;
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
				" uiMaxVectorElementNumber="<<uiMaxVectorElementNumber<<" . "<<flush<<endl;
			iReturn++;
			
			continue;
		}
		
		unsigned int uiErrorsInTests = 0;
		const unsigned int uiFunctionsToCall = 32 + log( uiSize );
		for ( unsigned int uiActualFunctionCall = 0;
				uiActualFunctionCall < uiFunctionsToCall; uiActualFunctionCall++ ){
			
			const unsigned int uiTestType = rand() % 26;
			
			switch ( uiTestType ){
				case 0:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing methods to check the Fib object structur on random generated Fib objects"<<endl;
					uiErrorsInTests += testStructurOnObject( pGeneratedFibObject );
					uiErrorsInTests += testGetNumberOfCountOnObject( pGeneratedFibObject );
					uiErrorsInTests += testGetAllFibElementsOnObject( pGeneratedFibObject );
					uiErrorsInTests += testTypeElementPointToElementPointOnObject( pGeneratedFibObject );
					uiErrorsInTests += testObjectPointOnObject( pGeneratedFibObject);
				}break;
				case 1:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=false)"<<endl;
					uiErrorsInTests += testOverwriteObjectWithObjectOnObject( pGeneratedFibObject, true );
				}break;
				case 2:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=false)"<<endl;
					uiErrorsInTests += testOverwriteObjectWithObjectOnObject( pGeneratedFibObject, false );
				}break;
				case 3:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=true)"<<endl;
					uiErrorsInTests += testOverwriteObjectWithObjectAbsoluteOnObject( pGeneratedFibObject, true );
				}break;
				case 4:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the overwriteObjectWithObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=true)"<<endl;
					uiErrorsInTests += testOverwriteObjectWithObjectAbsoluteOnObject( pGeneratedFibObject, false );
				}break;
				case 5:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=false)"<<endl;
					uiErrorsInTests += testRemoveObjectOnObject( pGeneratedFibObject, true );
				}break;
				case 6:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=false)"<<endl;
					uiErrorsInTests += testRemoveObjectOnObject( pGeneratedFibObject, false );
				}break;
				case 7:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=true and bAbsolute=true)"<<endl;
					uiErrorsInTests += testRemoveObjectAbsoluteOnObject( pGeneratedFibObject, true );
				}break;
				case 8:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeObject() method on random generated Fib objects (with bDeleteOld=false and bAbsolute=true)"<<endl;
					uiErrorsInTests += testRemoveObjectAbsoluteOnObject( pGeneratedFibObject, false );
				}break;
				case 9:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=true and bAbsolute=false)"<<endl;
					uiErrorsInTests += testInsertObjectInElementObjectFirstOnObject( pGeneratedFibObject );
				}break;
				case 10:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=true and bAbsolute=true)"<<endl;
					uiErrorsInTests += testInsertObjectInElementObjectFirstAbsoluteOnObject( pGeneratedFibObject );
				}break;
				case 11:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=false and bAbsolute=false)"<<endl;
					uiErrorsInTests += testInsertObjectInElementObjectSecondOnObject( pGeneratedFibObject );
				}break;
				case 12:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertObjectInElement() method on random generated Fib objects (with first=false and bAbsolute=true)"<<endl;
					uiErrorsInTests += testInsertObjectInElementObjectSecondAbsoluteOnObject( pGeneratedFibObject );
				}break;
				case 13:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=false)"<<endl;
					uiErrorsInTests += testInsertElementOnObject( pGeneratedFibObject, true );
				}break;
				case 14:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects(with bCheckVariables=true and bAbsolute=true)"<<endl;
					uiErrorsInTests += testInsertElementAbsoluteOnObject( pGeneratedFibObject, true );
				}break;
				case 15:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=false)"<<endl;
					uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, true, true );
				}break;
				case 16:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=false)"<<endl;
					uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, false, true );
				}break;
				case 17:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=true)"<<endl;
					uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, true, true );
				}break;
				case 18:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=true and bAbsolute=true)"<<endl;
					uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, false, true );
				}break;
				case 19:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement up (with bAbsolute=false)"<<endl;
					uiErrorsInTests += testMoveLimbElementUpOnObject( pGeneratedFibObject, false );
				}break;
				case 20:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement up (with bAbsolute=true)"<<endl;
					uiErrorsInTests += testMoveLimbElementUpOnObject( pGeneratedFibObject, true );
				}break;
				case 21:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement down (with bAbsolute=false)"<<endl;
					uiErrorsInTests += testMoveLimbElementDownOnObject( pGeneratedFibObject, false );
				}break;
				case 22:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the moveLimbElement() method on random generated Fib objects for moving a limbelement down (with bAbsolute=true)"<<endl;
					uiErrorsInTests += testMoveLimbElementDownOnObject( pGeneratedFibObject, true );
				}break;
				case 23:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the copyElement() method on random generated Fib objects (with bAbsolute=false)"<<endl;
					uiErrorsInTests += testCopyElementOnObject( pGeneratedFibObject, false );
				}break;
				case 24:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the copyElement() method on random generated Fib objects (with bAbsolute=true)"<<endl;
					uiErrorsInTests += testCopyElementOnObject( pGeneratedFibObject, true );
				}break;
				case 25:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the copy() method on random generated Fib objects"<<endl;
					uiErrorsInTests += testCopyOnObject( pGeneratedFibObject );
				}break;
				
				/*don't use bCheckVariables=false variable test could fail afterwards
				case 15:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=false)"<<endl;
					uiErrorsInTests += testInsertElementOnObject( pGeneratedFibObject, false );
				}break;
				case 16:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the insertElement() method on random generated Fib objects(with bCheckVariables=false and bAbsolute=true)"<<endl;
					uiErrorsInTests += testInsertElementAbsoluteOnObject( pGeneratedFibObject, false );
				}break;
				case 18:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=false)"<<endl;
					uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, true, false );
				}break;
				case 20:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=false)"<<endl;
					uiErrorsInTests += testRemoveElementOnObject( pGeneratedFibObject, false, false );
				}break;
				case 22:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the cutElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=true)"<<endl;
					uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, true, false );
				}break;
				case 24:{
					cout<<endl<<"TEST PHASE "<<ulTestphase<<" : Testing the removeElement() method on random generated Fib objects (with bCheckVariables=false and bAbsolute=true)"<<endl;
					uiErrorsInTests += testRemoveElementAbsoluteOnObject( pGeneratedFibObject, false, false );
				}break;
				*/
				default:
					cerr<<"No test to evalue choosen"<<endl;
					uiErrorsInTests++;
				break;
			}
			if ( uiErrorsInTests != 0 ){
				cerr<<"Errors in test occured stopping evaluation ."<<endl;
				break;
			}
		}
		iReturn += uiErrorsInTests;

		if ( uiErrorsInTests != 0 ){
			//write Fib object wher orror occured to folder
		char szFileNameBuffer[256];
		sprintf ( szFileNameBuffer, "%s%sS%uD%uSR%uSRD%uIV%uVF%uMV%uR%uTTRandFun%s",
			DIR_OUTPUT, "structurError", uiSize,
			uiNumberOfDimensions, uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, uiFractionsOfUsedVariables,
			uiMaxVectorElementNumber, uiIteration, ".xml" );
			
			cerr<<"Error: The Fib object where the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
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








/**
 * This function returns, if the given Fib element pFibElement is an
 * branchelement.
 *
 * @param pFibElement a pointer to the Fib element to check
 * @return if pFibElement is an branchelement (cFibBranch) true, else false
 */
bool isBranchElement( cFibElement * pFibElement ){
	
	if ( pFibElement == NULL ){
		return false;
	}
	const char cType = pFibElement->getType();
	if ( (cType == 'r') || (cType == 'l') || (cType == 'o') || (cType == 'i') ){
		return true;
	}
	return false;
}


/**
 * This function copies a Fib limbelement without it's pointers to
 * other Fib elements.
 *
 * Fib elements implemented:
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cComment
 *
 * @param pFibLimb the Fib limbelement to copy
 * @return a copy of the Fib limbelement pFibLimb without it's pointers
 * 	to other Fib elements
 */
cFibLimb * copyFibLimbWithoutStructur( cFibLimb * pFibLimb ){
	
	switch ( pFibLimb->getType() ){
		case 'y':{
			return new cProperty( *(((cProperty*)pFibLimb)->getProperty()) );
		}break;
		case 'a':{
			cArea * pArea = (cArea*)pFibLimb;
			cArea * pAreaCopy = new cArea( *(pArea->getSubarea( 1 )) );
			for ( unsigned int uiSubarea = 2;
					uiSubarea <= pArea->getNumberOfSubareas(); uiSubarea++ ){
				
				pAreaCopy->addSubarea( *(pArea->getSubarea( uiSubarea )) );
			}
			return pAreaCopy;
		}break;
		case 'f':{
			return new cFunction( *(((cFunction*)pFibLimb)->getUnderFunction()) );
		}break;
		case 'c':{
			return new cComment( ((cComment*)pFibLimb)->getKey(),
				((cComment*)pFibLimb)->getValue() );
		}break;
		case 'v':{
			return new cFibSet( *((cFibSet*)pFibLimb) );
		}break;
		case 'm':{
			return new cFibMatrix( *((cFibMatrix*)pFibLimb) );
		}break;
	}
	return NULL;
}


/**
 * This function copies a Fib leaf element without it's pointers to
 * other Fib elements.
 *
 * Fib elements implemented:
 * 	- cPoint
 *
 * @param pFibLeaf the Fib leaf element to copy
 * @return a copy of the Fib leaf element pFibLeaf without it's pointers
 * 	to other Fib elements
 */
cFibLeaf * copyFibLeafWithoutStructur( cFibLeaf * pFibLeaf ){
	
	switch ( pFibLeaf->getType() ){
		case 'p':{
			return new cPoint( ((cPoint*)pFibLeaf)->getPosition() );
		}break;
		case 's':{
			return new cExtSubobject( ((cExtSubobject*)pFibLeaf)->getNumberSubobject(),
				*(((cExtSubobject*)pFibLeaf)->getOutputVector()) );
		}break;
	}
	return NULL;
}


/**
 * This function copies a Fib branchelement without it's pointers to
 * other Fib elements.
 *
 * Fib elements implemented:
 * 	- cRoot
 * 	- cList
 * 	- cIf
 * 	- cExtObject
 *
 * @param pFibBranch the Fib branchelement to copy
 * @return a copy of the Fib branchelement pFibBranch without it's pointers
 * 	to other Fib elements
 */
cFibBranch * copyFibBranchWithoutStructur( cFibBranch * pFibBranch ){
	
	cFibBranch * pFibBranchCopy = NULL;
	
	switch ( pFibBranch->getType() ){
		case 'r':{
			cRoot * pRoot = (cRoot*)pFibBranch;
			
			cRoot * pRootCopy = new cRoot();
			
			(*(pRootCopy->getMultimediaInfo())) = (*(pRoot->getMultimediaInfo()));
			(*(pRootCopy->getOptionalPart()))   = (*(pRoot->getOptionalPart() ) );
			
			(*(pRootCopy->getDomains())) = (*(pRoot->getDomains()));
			(*(pRootCopy->getValueDomains())) = (*(pRoot->getValueDomains()));
			
			unsignedIntFib uiNumberOfInVar = pRoot->getNumberOfInputVariables();
			pRootCopy->setNumberOfInputVariables( uiNumberOfInVar );
			for ( unsignedIntFib uiActualInVar = 1;
					uiActualInVar <= uiNumberOfInVar; uiActualInVar++ ){
				
				pRootCopy->setStandardValueOfInputVariable( uiActualInVar,
					pRoot->getStandardValueOfInputVariable( uiActualInVar ) );
			}
			
			pRootCopy->setChecksum( pRoot->getChecksum() );
			
			return pRootCopy;
		}break;
		
		case 'l':{
			return new cList( NULL, NULL );
		}break;
		case 'i':{
			return new cIf( *(((cIf*)(pFibBranch))->getCondition()), NULL, NULL );
		}break;
		case 'o':{
			return new cExtObject( ((cExtObject*)(pFibBranch))->getIdentifier(),
				*(((cExtObject*)(pFibBranch))->getInputVector()) );
		}break;
	}
	return pFibBranchCopy;
}


/**
 * This function copies a Fib element without it's pointers to
 * other Fib elements.
 *
 * @param pFibElement the Fib element to copy
 * @return a copy of the Fib element pFibElement without it's pointers
 * 	to other Fib elements
 */
cFibElement * copyFibElementWithoutStructur( cFibElement * pFibElement ){
	
	if ( pFibElement == NULL ){
		return NULL;
	}
	
	if ( pFibElement->isLimb() ){
		return copyFibLimbWithoutStructur( (cFibLimb*)pFibElement );
	}
	if ( pFibElement->isLeaf() ){
		return copyFibLeafWithoutStructur( (cFibLeaf*)pFibElement );
	}
	if ( pFibElement->isBranch() ){
		return copyFibBranchWithoutStructur( (cFibBranch*)pFibElement );
	}
	
	return NULL;
}


/**
 * This function tests simple methods for the structur of a Fib object on
 * a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- cFibElement * getSuperiorFibElement();
 * 	- cFibElement *getNextFibElement();
 * 	- cFibElement *getNextFibElement( char cType );
 * 	- cFibElement *getConstFibElement( longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( longFib lNumber, bool bAbsolute=false );
 * 	- cFibElement *getConstFibElement( char cType, longFib lNumber, bool bAbsolute=false ) const;
 * 	- cFibElement *getFibElement( char cType, longFib lNumber, bool bAbsolute=false );
 * 	- unsignedIntFib getNumberOfSubobjects() const = 0;
 * 	- cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 )
 * 	- const cFibElement * getSubobject( const unsignedIntFib uiNumberOfSubobject = 1 ) const
 * 	- list< cFibElement * > getSubobjects()
 * 	- list< const cFibElement * > getSubobjects() const
 * 	- cRoot * getSuperiorRootElement()
 * 	- const cRoot * getSuperiorRootElement() const
 * 	- unsignedIntFib getNumberOfElement( bool bOfType=false ) const;
 * 	- unsignedIntFib getNumberOfMovePoint() const;
 * 	- unsignedIntFib getNumberOfObjectPoint() const;
 * methods tested for entire Fib object:
 * 	- unsignedIntFib getNumberOfElements( char cType='u' ) const;
 * 	- unsignedIntFib getNumberOfMovePoints() const;
 * 	- unsignedIntFib getNumberOfObjectPoints() const;
 * 	- bool hasUnderAllObjects() const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bPrintMessages if true some messages about the Fib object will be written
 * @return the number of erros occured in the test
 */
int testStructurOnObject( cFibElement * pFibObject, bool bPrintMessages ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//data of the Fib objects
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfAllRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfAllPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfAllPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAllAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfAllFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfAllIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfAllCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfAllListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfAllExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfAllExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfAllSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfAllMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	const unsigned int uiNumberOfAllMovePoints =
		pFibObject->getNumberOfMovePoints();
	const unsigned int uiNumberOfAllObjectPoints =
		pFibObject->getNumberOfObjectPoints();
	
	if ( bPrintMessages ){
		cout<<"The given Fib objects has:"<<endl;
		cout<<"   "<< uiNumberOfAllFibElements <<" Fib elements"<<endl;
		cout<<"   "<< uiNumberOfAllRootElements <<" rootelements"<<endl;
		cout<<"   "<< uiNumberOfAllPointElements <<" point elements"<<endl;
		cout<<"   "<< uiNumberOfAllPropertyElements <<" property elements"<<endl;
		cout<<"   "<< uiNumberOfAllAreaElements <<" area elements"<<endl;
		cout<<"   "<< uiNumberOfAllFunctionElements <<" function elements"<<endl;
		cout<<"   "<< uiNumberOfAllIfElements <<" if elements"<<endl;
		cout<<"   "<< uiNumberOfAllCommentElements <<" comment elements"<<endl;
		cout<<"   "<< uiNumberOfAllListElements <<" list elements"<<endl;
		cout<<"   "<< uiNumberOfAllExtObjectElements <<" external object elements"<<endl;
		cout<<"   "<< uiNumberOfAllExtSubobjectElements <<" external subobject elements"<<endl;
		cout<<"   "<< uiNumberOfAllSetElements <<" set elements"<<endl;
		cout<<"   "<< uiNumberOfAllMatrixElements <<" matrix elements"<<endl;
		cout<<"   "<< uiNumberOfAllMovePoints <<" movepoints"<<endl;
		cout<<"   "<< uiNumberOfAllObjectPoints <<" objectpoins"<<endl;
	}
	
	if ( uiNumberOfAllFibElements == 0 ){
		cerr<<"Error: No Fib elements in the Fib Object."<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( uiNumberOfAllFibElements != ( uiNumberOfAllRootElements +
			uiNumberOfAllPointElements + uiNumberOfAllPropertyElements +
			uiNumberOfAllAreaElements + uiNumberOfAllFunctionElements +
			uiNumberOfAllListElements + uiNumberOfAllCommentElements +
			uiNumberOfAllIfElements + uiNumberOfAllExtObjectElements +
			uiNumberOfAllExtSubobjectElements + uiNumberOfAllSetElements +
			uiNumberOfAllMatrixElements ) ){
		cerr<<"Error: Ther are different values for number of all Fib elements"<<
			"given back, counted over all Fib elements and seperatly."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllMovePoints != ( uiNumberOfAllPropertyElements +
			uiNumberOfAllAreaElements + uiNumberOfAllFunctionElements +
			uiNumberOfAllCommentElements + uiNumberOfAllSetElements +
			uiNumberOfAllMatrixElements ) ){
		cerr<<"Error: Ther are different values for number of all movepoints "<<
			"given back, counted over all Fib elements and seperatly over the Fib elements."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllObjectPoints != (uiNumberOfAllPointElements + uiNumberOfAllExtSubobjectElements +
			uiNumberOfAllListElements + uiNumberOfAllIfElements +
			uiNumberOfAllExtObjectElements + (uiNumberOfAllRootElements - 1)) ){
		cerr<<"Error: Ther are different values for number of all objectpoints "<<
			"given back, counted over all Fib elements and seperatly over the Fib elements."<<endl;
		iReturn++;
	}

	const cFibElement * pConstFibObject = pFibObject;

	//data of the actual Fib element
	unsigned int uiNumberOfActualFibElement = 0;
	unsigned int uiNumberOfLastRoot  = 0;
	unsigned int uiNumberOfLastPoint = 0;
	unsigned int uiNumberOfLastProperty = 0;
	unsigned int uiNumberOfLastArea  = 0;
	unsigned int uiNumberOfLastFunction = 0;
	unsigned int uiNumberOfLastIf    = 0;
	unsigned int uiNumberOfLastComment  = 0;
	unsigned int uiNumberOfLastList  = 0;
	unsigned int uiNumberOfLastExtObject     = 0;
	unsigned int uiNumberOfLastExtSubobject  = 0;
	unsigned int uiNumberOfLastSet   = 0;
	unsigned int uiNumberOfLastMatrix   = 0;
	
	unsigned int uiNumberOfLastMovePoint  = 0;
	unsigned int uiNumberOfLastObjectPoint  = 0;
	
	cFibElement * pNextRoot  = pFibObject->getNextFibElement( 'r' );
	cFibElement * pNextPoint = pFibObject->getNextFibElement( 'p' );
	cFibElement * pNextProperty = pFibObject->getNextFibElement( 'y' );
	cFibElement * pNextArea  = pFibObject->getNextFibElement( 'a' );
	cFibElement * pNextFunction = pFibObject->getNextFibElement( 'f' );
	cFibElement * pNextIf    = pFibObject->getNextFibElement( 'i' );
	cFibElement * pNextComment  = pFibObject->getNextFibElement( 'c' );
	cFibElement * pNextList  = pFibObject->getNextFibElement( 'l' );
	cFibElement * pNextExtObject    = pFibObject->getNextFibElement( 'o' );
	cFibElement * pNextExtSubobject = pFibObject->getNextFibElement( 's' );
	cFibElement * pNextSet   = pFibObject->getNextFibElement( 'v' );
	cFibElement * pNextMatrix   = pFibObject->getNextFibElement( 'm' );
	
	/*check getFibElement(longFib lNumber, false) for random coosen
	Fib element with random choosen lNumber*/
	unsigned int uiNumberOfNextFibElement = (rand() % (uiNumberOfAllFibElements / 100 + 5)) + 1;
	cFibElement * pNextNumberFibElement = pFibObject->getFibElement( uiNumberOfNextFibElement );
	
	/*check if getConstFibElement(longFib lNumber, false) is equal to
	getFibElement(longFib lNumber, false)*/
	cFibElement * pConstNextNumberFibElement =
		pConstFibObject->getConstFibElement( uiNumberOfNextFibElement );
		
	if ( pConstNextNumberFibElement != pNextNumberFibElement ){
		cerr<<"Error: The first next const "<< uiNumberOfNextFibElement <<
			"'th Fib element from the "<< uiNumberOfActualFibElement <<
			"'th next Fib element is not equal to the next "<<
			uiNumberOfNextFibElement <<"'th Fib element"<<
			" (getFibElement() != getConstFibElement())"<<endl;
		iReturn++;
	}
	
	/*check getFibElement(longFib lNumber, true) for random coosen Fib element;
	choos some random absolute Fib elements and check later if the same
	Fib elements are given back*/
	unsigned int uiElementsTillNextGetFibElementAbsolutCheck =
		(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
	//generate list of absolute Fib elements to check later
	list< pair<cFibElement *, unsigned int> > liAbsolutNextFibElements;
	for ( unsigned int uiActualAbsolutFibElement = 0;
			uiActualAbsolutFibElement <= uiNumberOfAllFibElements / 100 + 3;
			uiActualAbsolutFibElement++ ){
		
		unsigned int uiNumberOfNextAbsoluteFib = rand() % (uiNumberOfAllFibElements + 2) + 1;
		cFibElement * pNextNumberAbsoluteFibElement = pFibObject->getFibElement(
			uiNumberOfNextAbsoluteFib, true );
		/*check if getConstFibElement(longFib lNumber, true) is equal to
		getFibElement(longFib lNumber, false)*/
		unsigned int uiNumberOfCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pCallingFibElement = pFibObject->getFibElement(
			uiNumberOfCallingFibElement );
		
		cFibElement * pConstNextNumberAbsoluteFibElement =
			pConstFibObject->getConstFibElement(
			uiNumberOfNextAbsoluteFib, true );
		if ( pConstNextNumberAbsoluteFibElement != pNextNumberAbsoluteFibElement ){
			cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteFib <<
				"'th Fib element from the "<< uiNumberOfActualFibElement <<
				"'th next Fib element is not equal to the next "<<
				uiNumberOfNextAbsoluteFib <<"'th Fib element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
				
			if ( pNextNumberAbsoluteFibElement ){
				cerr<<"   getFibElement() = "<<pNextNumberAbsoluteFibElement->getNumberOfElement()<<endl;
			}else{
				cerr<<"   getFibElement() = NULL"<<endl;
			}
			if ( pConstNextNumberAbsoluteFibElement ){
				cerr<<"   getConstFibElement() = "<<pConstNextNumberAbsoluteFibElement->getNumberOfElement()<<endl;
			}else{
				cerr<<"   getConstFibElement() = NULL"<<endl;
			}
			iReturn++;
		}
		pConstNextNumberAbsoluteFibElement =
			pCallingFibElement->getConstFibElement(
			uiNumberOfNextAbsoluteFib, true );
		if ( pConstNextNumberAbsoluteFibElement != pNextNumberAbsoluteFibElement ){
			cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteFib <<
				"'th Fib element from the "<< uiNumberOfActualFibElement <<
				"'th next Fib element is not equal to the next "<<
				uiNumberOfNextAbsoluteFib <<"'th Fib element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			if ( pNextNumberAbsoluteFibElement ){
				cerr<<"   getFibElement() = "<<pNextNumberAbsoluteFibElement->getNumberOfElement()<<endl;
			}else{
				cerr<<"   getFibElement() = NULL"<<endl;
			}
			if ( pConstNextNumberAbsoluteFibElement ){
				cerr<<"   getConstFibElement() = "<<pConstNextNumberAbsoluteFibElement->getNumberOfElement()<<endl;
			}else{
				cerr<<"   getConstFibElement() = NULL"<<endl;
			}
			iReturn++;
		}
		
		cFibElement * pNextNumberAbsoluteFibElementU =
			pFibObject->getFibElement( 'u', uiNumberOfNextAbsoluteFib, true );
		if ( pNextNumberAbsoluteFibElementU != pNextNumberAbsoluteFibElement ){
			cerr<<"Error: The next absolute "<< uiNumberOfNextAbsoluteFib <<
				"'th Fib element from the "<< uiNumberOfActualFibElement <<
				"'th next Fib element of type 'u' is not equal to the next "<<
				uiNumberOfNextAbsoluteFib <<"'th Fib element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		pNextNumberAbsoluteFibElementU =
			pCallingFibElement->getFibElement( 'u', uiNumberOfNextAbsoluteFib, true );
		if ( pNextNumberAbsoluteFibElementU != pNextNumberAbsoluteFibElement ){
			cerr<<"Error: The next absolute "<< uiNumberOfNextAbsoluteFib <<
				"'th Fib element from the "<< uiNumberOfActualFibElement <<
				"'th next Fib element of type 'u' is not equal to the next "<<
				uiNumberOfNextAbsoluteFib <<"'th Fib element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}

		pConstNextNumberAbsoluteFibElement = pConstFibObject->getConstFibElement(
			'u', uiNumberOfNextAbsoluteFib, true );
		if ( pConstNextNumberAbsoluteFibElement != pNextNumberAbsoluteFibElement ){
			cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteFib <<
				"'th Fib element from the "<< uiNumberOfActualFibElement <<
				"'th next Fib element of type 'u' is not equal to the next "<<
				uiNumberOfNextAbsoluteFib <<"'th Fib element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		pConstNextNumberAbsoluteFibElement = pCallingFibElement->getConstFibElement(
			'u', uiNumberOfNextAbsoluteFib, true );
		if ( pConstNextNumberAbsoluteFibElement != pNextNumberAbsoluteFibElement ){
			cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteFib <<
				"'th Fib element from the "<< uiNumberOfActualFibElement <<
				"'th next Fib element of type 'u' is not equal to the next "<<
				uiNumberOfNextAbsoluteFib <<"'th Fib element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		liAbsolutNextFibElements.push_back( make_pair(
			pNextNumberAbsoluteFibElement, uiNumberOfNextAbsoluteFib) );
	}

	
	/*check getFibElement( char cType, longFib lNumber, false) for random
	coosen Fib element with random choosen lNumber; check this like for
	getFibElement( longFib lNumber, false) but for all possible Fib elementtyps*/
	//for point
	unsigned int uiNumberOfNextPointElement = 0;
	cFibElement * pNextNumberPointElement = NULL;
	unsigned int uiElementsTillNextGetPointElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextPointElements;
	if ( 0 < uiNumberOfAllPointElements ){
		
		uiNumberOfNextPointElement = (rand() % (uiNumberOfAllPointElements / 100 + 5)) + 1;
		pNextNumberPointElement = pFibObject->getFibElement( 'p', uiNumberOfNextPointElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberPointElement =
			pConstFibObject->getConstFibElement( 'p', uiNumberOfNextPointElement );
			
		if ( pConstNextNumberPointElement != pNextNumberPointElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextPointElement <<
				"'th point element from the "<< uiNumberOfActualFibElement <<
				" next point element is not equal to the next "<<
					uiNumberOfNextPointElement <<"'th point element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetPointElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate list of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutPointElement = 0;
				uiActualAbsolutPointElement <= uiNumberOfAllPointElements / 100 + 3;
				uiActualAbsolutPointElement++ ){
			
			unsigned int uiNumberOfNextAbsolutePointElement = rand() % (uiNumberOfAllPointElements + 2) + 1;
			cFibElement * pNextNumberAbsolutePointElement = pFibObject->getFibElement( 'p',
				uiNumberOfNextAbsolutePointElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsolutePointElement =
				pConstFibObject->getConstFibElement( 'p',
				uiNumberOfNextAbsolutePointElement, true );
				
			if ( pConstNextNumberAbsolutePointElement != pNextNumberAbsolutePointElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsolutePointElement <<
					"'th point element from the "<< uiNumberOfActualFibElement <<
					" next point element is not equal to the next "<<
					uiNumberOfNextAbsolutePointElement <<"'th point element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextPointElements.push_back( make_pair(
				pNextNumberAbsolutePointElement, uiNumberOfNextAbsolutePointElement) );
		}
	}
	
	//for list
	unsigned int uiNumberOfNextListElement = 0;
	cFibElement * pNextNumberListElement = NULL;
	unsigned int uiElementsTillNextGetListElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextListElements;
	if ( 0 < uiNumberOfAllListElements ){
		
		uiNumberOfNextListElement = (rand() % (uiNumberOfAllListElements / 100 + 5)) + 1;
		pNextNumberListElement = pFibObject->getFibElement( 'l', uiNumberOfNextListElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberListElement =
			pConstFibObject->getConstFibElement( 'l', uiNumberOfNextListElement );
			
		if ( pConstNextNumberListElement != pNextNumberListElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextListElement <<
				"'th list element from the "<< uiNumberOfActualFibElement <<
				" next list element is not equal to the next "<<
					uiNumberOfNextListElement <<"'th list element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetListElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate list of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutListElement = 0;
				uiActualAbsolutListElement <= uiNumberOfAllListElements / 100 + 3;
				uiActualAbsolutListElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteListElement = rand() % (uiNumberOfAllListElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteListElement = pFibObject->getFibElement( 'l',
				uiNumberOfNextAbsoluteListElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteListElement =
				pConstFibObject->getConstFibElement( 'l',
				uiNumberOfNextAbsoluteListElement, true );
				
			if ( pConstNextNumberAbsoluteListElement != pNextNumberAbsoluteListElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteListElement <<
					"'th list element from the "<< uiNumberOfActualFibElement <<
					" next list element is not equal to the next "<<
					uiNumberOfNextAbsoluteListElement <<"'th list element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextListElements.push_back( make_pair(
				pNextNumberAbsoluteListElement, uiNumberOfNextAbsoluteListElement) );
		}
	}

	//for property
	unsigned int uiNumberOfNextPropertyElement = 0;
	cFibElement * pNextNumberPropertyElement = NULL;
	unsigned int uiElementsTillNextGetPropertyElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextPropertyElements;
	if ( 0 < uiNumberOfAllPropertyElements ){
		
		uiNumberOfNextPropertyElement = (rand() % (uiNumberOfAllPropertyElements / 100 + 5)) + 1;
		pNextNumberPropertyElement = pFibObject->getFibElement( 'y', uiNumberOfNextPropertyElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberPropertyElement =
			pConstFibObject->getConstFibElement( 'y', uiNumberOfNextPropertyElement );
			
		if ( pConstNextNumberPropertyElement != pNextNumberPropertyElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextPropertyElement <<
				"'th property element from the "<< uiNumberOfActualFibElement <<
				" next property element is not equal to the next "<<
					uiNumberOfNextPropertyElement <<"'th property element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetPropertyElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate property of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutPropertyElement = 0;
				uiActualAbsolutPropertyElement <= uiNumberOfAllPropertyElements / 100 + 3;
				uiActualAbsolutPropertyElement++ ){
			
			unsigned int uiNumberOfNextAbsolutePropertyElement = rand() % (uiNumberOfAllPropertyElements + 2) + 1;
			cFibElement * pNextNumberAbsolutePropertyElement = pFibObject->getFibElement( 'y',
				uiNumberOfNextAbsolutePropertyElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsolutePropertyElement =
				pConstFibObject->getConstFibElement( 'y',
				uiNumberOfNextAbsolutePropertyElement, true );
				
			if ( pConstNextNumberAbsolutePropertyElement != pNextNumberAbsolutePropertyElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsolutePropertyElement <<
					"'th property element from the "<< uiNumberOfActualFibElement <<
					" next property element is not equal to the next "<<
					uiNumberOfNextAbsolutePropertyElement <<"'th property element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextPropertyElements.push_back( make_pair(
				pNextNumberAbsolutePropertyElement, uiNumberOfNextAbsolutePropertyElement) );
		}
	}

	//for area
	unsigned int uiNumberOfNextAreaElement = 0;
	cFibElement * pNextNumberAreaElement = NULL;
	unsigned int uiElementsTillNextGetAreaElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextAreaElements;
	if ( 0 < uiNumberOfAllAreaElements ){
		
		uiNumberOfNextAreaElement = (rand() % (uiNumberOfAllAreaElements / 100 + 5)) + 1;
		pNextNumberAreaElement = pFibObject->getFibElement( 'a', uiNumberOfNextAreaElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberAreaElement =
			pConstFibObject->getConstFibElement( 'a', uiNumberOfNextAreaElement );
			
		if ( pConstNextNumberAreaElement != pNextNumberAreaElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextAreaElement <<
				"'th area element from the "<< uiNumberOfActualFibElement <<
				" next area element is not equal to the next "<<
					uiNumberOfNextAreaElement <<"'th area element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetAreaElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate area of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutAreaElement = 0;
				uiActualAbsolutAreaElement <= uiNumberOfAllAreaElements / 100 + 3;
				uiActualAbsolutAreaElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteAreaElement = rand() % (uiNumberOfAllAreaElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteAreaElement = pFibObject->getFibElement( 'a',
				uiNumberOfNextAbsoluteAreaElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteAreaElement =
				pConstFibObject->getConstFibElement( 'a',
				uiNumberOfNextAbsoluteAreaElement, true );
				
			if ( pConstNextNumberAbsoluteAreaElement != pNextNumberAbsoluteAreaElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteAreaElement <<
					"'th area element from the "<< uiNumberOfActualFibElement <<
					" next area element is not equal to the next "<<
					uiNumberOfNextAbsoluteAreaElement <<"'th area element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextAreaElements.push_back( make_pair(
				pNextNumberAbsoluteAreaElement, uiNumberOfNextAbsoluteAreaElement) );
		}
	}

	//for function
	unsigned int uiNumberOfNextFunctionElement = 0;
	cFibElement * pNextNumberFunctionElement = NULL;
	unsigned int uiElementsTillNextGetFunctionElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextFunctionElements;
	if ( 0 < uiNumberOfAllFunctionElements ){
		
		uiNumberOfNextFunctionElement = (rand() % (uiNumberOfAllFunctionElements / 100 + 5)) + 1;
		pNextNumberFunctionElement = pFibObject->getFibElement( 'f', uiNumberOfNextFunctionElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberFunctionElement =
			pConstFibObject->getConstFibElement( 'f', uiNumberOfNextFunctionElement );
			
		if ( pConstNextNumberFunctionElement != pNextNumberFunctionElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextFunctionElement <<
				"'th function element from the "<< uiNumberOfActualFibElement <<
				" next function element is not equal to the next "<<
				uiNumberOfNextFunctionElement <<"'th function element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetFunctionElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate function of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutFunctionElement = 0;
				uiActualAbsolutFunctionElement <= uiNumberOfAllFunctionElements / 100 + 3;
				uiActualAbsolutFunctionElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteFunctionElement = rand() % (uiNumberOfAllFunctionElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteFunctionElement = pFibObject->getFibElement( 'f',
				uiNumberOfNextAbsoluteFunctionElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteFunctionElement =
				pConstFibObject->getConstFibElement( 'f',
				uiNumberOfNextAbsoluteFunctionElement, true );
				
			if ( pConstNextNumberAbsoluteFunctionElement != pNextNumberAbsoluteFunctionElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteFunctionElement <<
					"'th function element from the "<< uiNumberOfActualFibElement <<
					" next function element is not equal to the next "<<
					uiNumberOfNextAbsoluteFunctionElement <<"'th function element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextFunctionElements.push_back( make_pair(
				pNextNumberAbsoluteFunctionElement, uiNumberOfNextAbsoluteFunctionElement) );
		}
	}
	
	
	//for if
	unsigned int uiNumberOfNextIfElement = 0;
	cFibElement * pNextNumberIfElement = NULL;
	unsigned int uiElementsTillNextGetIfElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextIfElements;
	if ( 0 < uiNumberOfAllIfElements ){
		
		uiNumberOfNextIfElement = (rand() % (uiNumberOfAllIfElements / 100 + 5)) + 1;
		pNextNumberIfElement = pFibObject->getFibElement( 'i', uiNumberOfNextIfElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberIfElement =
			pConstFibObject->getConstFibElement( 'i', uiNumberOfNextIfElement );
			
		if ( pConstNextNumberIfElement != pNextNumberIfElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextIfElement <<
				"'th if-element from the "<< uiNumberOfActualFibElement <<
				" next if-element is not equal to the next "<<
				uiNumberOfNextIfElement <<"'th if-element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetIfElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate if of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutIfElement = 0;
				uiActualAbsolutIfElement <= uiNumberOfAllIfElements / 100 + 3;
				uiActualAbsolutIfElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteIfElement = rand() % (uiNumberOfAllIfElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteIfElement = pFibObject->getFibElement( 'i',
				uiNumberOfNextAbsoluteIfElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteIfElement =
				pConstFibObject->getConstFibElement( 'i',
				uiNumberOfNextAbsoluteIfElement, true );
				
			if ( pConstNextNumberAbsoluteIfElement != pNextNumberAbsoluteIfElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteIfElement <<
					"'th if-element from the "<< uiNumberOfActualFibElement <<
					" next if-element is not equal to the next "<<
					uiNumberOfNextAbsoluteIfElement <<"'th if-element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextIfElements.push_back( make_pair(
				pNextNumberAbsoluteIfElement, uiNumberOfNextAbsoluteIfElement) );
		}
	}
	
	//for comment
	unsigned int uiNumberOfNextCommentElement = 0;
	cFibElement * pNextNumberCommentElement = NULL;
	unsigned int uiElementsTillNextGetCommentElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextCommentElements;
	if ( 0 < uiNumberOfAllCommentElements ){
		
		uiNumberOfNextCommentElement = (rand() % (uiNumberOfAllCommentElements / 100 + 5)) + 1;
		pNextNumberCommentElement = pFibObject->getFibElement( 'c', uiNumberOfNextCommentElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberCommentElement =
			pConstFibObject->getConstFibElement( 'c', uiNumberOfNextCommentElement );
			
		if ( pConstNextNumberCommentElement != pNextNumberCommentElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextCommentElement <<
				"'th comment element from the "<< uiNumberOfActualFibElement <<
				" next comment element is not equal to the next "<<
				uiNumberOfNextCommentElement <<"'th comment element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetCommentElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate comment of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutCommentElement = 0;
				uiActualAbsolutCommentElement <= uiNumberOfAllCommentElements / 100 + 3;
				uiActualAbsolutCommentElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteCommentElement = rand() % (uiNumberOfAllCommentElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteCommentElement = pFibObject->getFibElement( 'c',
				uiNumberOfNextAbsoluteCommentElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteCommentElement =
				pConstFibObject->getConstFibElement( 'c',
				uiNumberOfNextAbsoluteCommentElement, true );
				
			if ( pConstNextNumberAbsoluteCommentElement != pNextNumberAbsoluteCommentElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteCommentElement <<
					"'th comment element from the "<< uiNumberOfActualFibElement <<
					" next comment element is not equal to the next "<<
					uiNumberOfNextAbsoluteCommentElement <<"'th comment element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextCommentElements.push_back( make_pair(
				pNextNumberAbsoluteCommentElement, uiNumberOfNextAbsoluteCommentElement) );
		}
	}
	
	//for external object elements
	unsigned int uiNumberOfNextExtObjectElement = 0;
	cFibElement * pNextNumberExtObjectElement = NULL;
	unsigned int uiElementsTillNextGetExtObjectElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextExtObjectElements;
	if ( 0 < uiNumberOfAllExtObjectElements ){
		
		uiNumberOfNextExtObjectElement = (rand() % (uiNumberOfAllExtObjectElements / 100 + 5)) + 1;
		pNextNumberExtObjectElement = pFibObject->getFibElement( 'o', uiNumberOfNextExtObjectElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberExtObjectElement =
			pConstFibObject->getConstFibElement( 'o', uiNumberOfNextExtObjectElement );
			
		if ( pConstNextNumberExtObjectElement != pNextNumberExtObjectElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextExtObjectElement <<
				"'th external object element from the "<< uiNumberOfActualFibElement <<
				" next external object element is not equal to the next "<<
				uiNumberOfNextExtObjectElement <<"'th external object element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetExtObjectElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate external object of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutExtObjectElement = 0;
				uiActualAbsolutExtObjectElement <= uiNumberOfAllExtObjectElements / 100 + 3;
				uiActualAbsolutExtObjectElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteExtObjectElement = rand() % (uiNumberOfAllExtObjectElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteExtObjectElement = pFibObject->getFibElement( 'o',
				uiNumberOfNextAbsoluteExtObjectElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteExtObjectElement =
				pConstFibObject->getConstFibElement( 'o',
				uiNumberOfNextAbsoluteExtObjectElement, true );
				
			if ( pConstNextNumberAbsoluteExtObjectElement != pNextNumberAbsoluteExtObjectElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteExtObjectElement <<
					"'th external object element from the "<< uiNumberOfActualFibElement <<
					" next external object element is not equal to the next "<<
					uiNumberOfNextAbsoluteExtObjectElement <<"'th external object element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextExtObjectElements.push_back( make_pair(
				pNextNumberAbsoluteExtObjectElement, uiNumberOfNextAbsoluteExtObjectElement) );
		}
	}
	
	
	//for external subobject elements
	unsigned int uiNumberOfNextExtSubobjectElement = 0;
	cFibElement * pNextNumberExtSubobjectElement = NULL;
	unsigned int uiElementsTillNextGetExtSubobjectElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextExtSubobjectElements;
	if ( 0 < uiNumberOfAllExtSubobjectElements ){
		
		uiNumberOfNextExtSubobjectElement = (rand() % (uiNumberOfAllExtSubobjectElements / 100 + 5)) + 1;
		pNextNumberExtSubobjectElement = pFibObject->getFibElement( 's', uiNumberOfNextExtSubobjectElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberExtSubobjectElement =
			pConstFibObject->getConstFibElement( 's', uiNumberOfNextExtSubobjectElement );
			
		if ( pConstNextNumberExtSubobjectElement != pNextNumberExtSubobjectElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextExtSubobjectElement <<
				"'th external subobject element from the "<< uiNumberOfActualFibElement <<
				" next external subobject element is not equal to the next "<<
				uiNumberOfNextExtSubobjectElement <<"'th external subobject element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetExtSubobjectElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate external subobject of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutExtSubobjectElement = 0;
				uiActualAbsolutExtSubobjectElement <= uiNumberOfAllExtSubobjectElements / 100 + 3;
				uiActualAbsolutExtSubobjectElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteExtSubobjectElement = rand() % (uiNumberOfAllExtSubobjectElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteExtSubobjectElement = pFibObject->getFibElement( 's',
				uiNumberOfNextAbsoluteExtSubobjectElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteExtSubobjectElement =
				pConstFibObject->getConstFibElement( 's',
				uiNumberOfNextAbsoluteExtSubobjectElement, true );
				
			if ( pConstNextNumberAbsoluteExtSubobjectElement != pNextNumberAbsoluteExtSubobjectElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteExtSubobjectElement <<
					"'th external subobject element from the "<< uiNumberOfActualFibElement <<
					" next external subobject element is not equal to the next "<<
					uiNumberOfNextAbsoluteExtSubobjectElement <<"'th external subobject element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextExtSubobjectElements.push_back( make_pair(
				pNextNumberAbsoluteExtSubobjectElement, uiNumberOfNextAbsoluteExtSubobjectElement) );
		}
	}
	
	//for set elements
	unsigned int uiNumberOfNextSetElement = 0;
	cFibElement * pNextNumberSetElement = NULL;
	unsigned int uiElementsTillNextGetSetElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextSetElements;
	if ( 0 < uiNumberOfAllSetElements ){
		
		uiNumberOfNextSetElement = (rand() % (uiNumberOfAllSetElements / 100 + 5)) + 1;
		pNextNumberSetElement = pFibObject->getFibElement( 'v', uiNumberOfNextSetElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberSetElement =
			pConstFibObject->getConstFibElement( 'v', uiNumberOfNextSetElement );
			
		if ( pConstNextNumberSetElement != pNextNumberSetElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextSetElement <<
				"'th set element from the "<< uiNumberOfActualFibElement <<
				" next set element is not equal to the next "<<
				uiNumberOfNextSetElement <<"'th set element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetSetElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate set of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutSetElement = 0;
				uiActualAbsolutSetElement <= uiNumberOfAllSetElements / 100 + 3;
				uiActualAbsolutSetElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteSetElement = rand() % (uiNumberOfAllSetElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteSetElement = pFibObject->getFibElement( 'v',
				uiNumberOfNextAbsoluteSetElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteSetElement =
				pConstFibObject->getConstFibElement( 'v',
				uiNumberOfNextAbsoluteSetElement, true );
				
			if ( pConstNextNumberAbsoluteSetElement != pNextNumberAbsoluteSetElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteSetElement <<
					"'th set element from the "<< uiNumberOfActualFibElement <<
					" next set element is not equal to the next "<<
					uiNumberOfNextAbsoluteSetElement <<"'th set element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextSetElements.push_back( make_pair(
				pNextNumberAbsoluteSetElement, uiNumberOfNextAbsoluteSetElement) );
		}
	}
	
	//for matrix elements
	unsigned int uiNumberOfNextMatrixElement = 0;
	cFibElement * pNextNumberMatrixElement = NULL;
	unsigned int uiElementsTillNextGetMatrixElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextMatrixElements;
	if ( 0 < uiNumberOfAllMatrixElements ){
		
		uiNumberOfNextMatrixElement = (rand() % (uiNumberOfAllMatrixElements / 100 + 5)) + 1;
		pNextNumberMatrixElement = pFibObject->getFibElement( 'm', uiNumberOfNextMatrixElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberMatrixElement =
			pConstFibObject->getConstFibElement( 'm', uiNumberOfNextMatrixElement );
			
		if ( pConstNextNumberMatrixElement != pNextNumberMatrixElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextMatrixElement <<
				"'th matrix element from the "<< uiNumberOfActualFibElement <<
				" next matrix element is not equal to the next "<<
				uiNumberOfNextMatrixElement <<"'th matrix element"<<
				" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetMatrixElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate matrix of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutMatrixElement = 0;
				uiActualAbsolutMatrixElement <= uiNumberOfAllMatrixElements / 100 + 3;
				uiActualAbsolutMatrixElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteMatrixElement = rand() % (uiNumberOfAllMatrixElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteMatrixElement = pFibObject->getFibElement( 'm',
				uiNumberOfNextAbsoluteMatrixElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteMatrixElement =
				pConstFibObject->getConstFibElement( 'm',
				uiNumberOfNextAbsoluteMatrixElement, true );
				
			if ( pConstNextNumberAbsoluteMatrixElement != pNextNumberAbsoluteMatrixElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteMatrixElement <<
					"'th matrix element from the "<< uiNumberOfActualFibElement <<
					" next matrix element is not equal to the next "<<
					uiNumberOfNextAbsoluteMatrixElement <<"'th matrix element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextMatrixElements.push_back( make_pair(
				pNextNumberAbsoluteMatrixElement, uiNumberOfNextAbsoluteMatrixElement) );
		}
	}
	
	//for root
	unsigned int uiNumberOfNextRootElement = 0;
	cFibElement * pNextNumberRootElement = NULL;
	unsigned int uiElementsTillNextGetRootElementAbsolutCheck = 0;
	list< pair<cFibElement *, unsigned int> > liAbsolutNextRootElements;
	if ( 0 < uiNumberOfAllRootElements ){
		
		uiNumberOfNextRootElement = (rand() % (uiNumberOfAllRootElements / 100 + 5)) + 1;
		pNextNumberRootElement = pFibObject->getFibElement( 'r', uiNumberOfNextRootElement );
		
		/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
		getFibElement( char cType, longFib lNumber, false)*/
		cFibElement * pConstNextNumberRootElement =
			pConstFibObject->getConstFibElement( 'r', uiNumberOfNextRootElement );
			
		if ( pConstNextNumberRootElement != pNextNumberRootElement ){
			cerr<<"Error: The next const "<< uiNumberOfNextRootElement <<
				"'th rootelement from the "<< uiNumberOfActualFibElement <<
				" next rootelement is not equal to the next "<<
					uiNumberOfNextRootElement <<"'th rootelement"<<
					" (getFibElement() != getConstFibElement())"<<endl;
			iReturn++;
		}
		
		/*check getFibElement( char cType, longFib lNumber, true) for random coosen Fib element;
		choos some random absolute Fib elements and check later if the same
		Fib elements are given back*/
		uiElementsTillNextGetRootElementAbsolutCheck =
			(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
		//generate root of absolute Fib elements to check later
		for ( unsigned int uiActualAbsolutRootElement = 0;
				uiActualAbsolutRootElement <= uiNumberOfAllRootElements / 100 + 3;
				uiActualAbsolutRootElement++ ){
			
			unsigned int uiNumberOfNextAbsoluteRootElement = rand() % (uiNumberOfAllRootElements + 2) + 1;
			cFibElement * pNextNumberAbsoluteRootElement = pFibObject->getFibElement( 'r',
				uiNumberOfNextAbsoluteRootElement, true );
			/*check if getConstFibElement( char cType, longFib lNumber, true) is equal to
			getFibElement(longFib lNumber, false)*/
			cFibElement * pConstNextNumberAbsoluteRootElement =
				pConstFibObject->getConstFibElement( 'r',
				uiNumberOfNextAbsoluteRootElement, true );
				
			if ( pConstNextNumberAbsoluteRootElement != pNextNumberAbsoluteRootElement ){
				cerr<<"Error: The next absolute const "<< uiNumberOfNextAbsoluteRootElement <<
					"'th rootelement from the "<< uiNumberOfActualFibElement <<
					" next rootelement is not equal to the next "<<
					uiNumberOfNextAbsoluteRootElement <<"'th rootelement"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
			
			liAbsolutNextRootElements.push_back( make_pair(
				pNextNumberAbsoluteRootElement, uiNumberOfNextAbsoluteRootElement) );
		}
	}

	//check highest root-element
	if ( pFibObject->getSuperiorFibElement() != NULL ){
			cerr<<"Error: The given Fib object has an superior Fib element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( -1 ) != NULL ){
			cerr<<"Error: The given Fib object has an previos Fib element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'r', -1 ) != NULL ){//Root
			cerr<<"Error: The given Fib object has an previos root-element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'p', -1 ) != NULL ){//Point
			cerr<<"Error: The given Fib object has an previos point element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'y', -1 ) != NULL ){//Property
			cerr<<"Error: The given Fib object has an previos property element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'a', -1 ) != NULL ){//Area
			cerr<<"Error: The given Fib object has an previos area element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'f', -1 ) != NULL ){//Function
			cerr<<"Error: The given Fib object has an previos function element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'i', -1 ) != NULL ){//if
			cerr<<"Error: The given Fib object has an previos if-element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'c', -1 ) != NULL ){//Comment
			cerr<<"Error: The given Fib object has an previos comment element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'l', -1 ) != NULL ){//List
			cerr<<"Error: The given Fib object has an previos list element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'o', -1 ) != NULL ){//external object element
			cerr<<"Error: The given Fib object has an previos external object element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 's', -1 ) != NULL ){//external subobject element
			cerr<<"Error: The given Fib object has an previos external subobject element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'v', -1 ) != NULL ){//set element
			cerr<<"Error: The given Fib object has an previos set element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getFibElement( 'm', -1 ) != NULL ){//matrix element
			cerr<<"Error: The given Fib object has an previos matrix element."<<endl;
			iReturn++;
	}
	if ( pFibObject->getType() != 'r' ){//Root
			cerr<<"Error: The given Fib object has not an root-element as it's top most Fib element."<<endl;
			iReturn++;
	}else{
		pNextRoot = pFibObject;
	}
	
	/*iterate over all Fib elements in the Fib object and check the values*/
	for ( cFibElement * pActualFibElement = pFibObject;
			pActualFibElement != NULL;
			pActualFibElement = pActualFibElement->getNextFibElement() ){

		//update values
		uiNumberOfActualFibElement++;
		
		if ( pActualFibElement->getNumberOfElement() !=
				uiNumberOfActualFibElement ){
			cerr<<"Error: The actual Fib element should be the Fib element number "<<
				uiNumberOfActualFibElement<<" , but returns the number "<<
				pActualFibElement->getNumberOfElement() <<" ."<<endl;
			iReturn++;
		}
		
		const char cTypeOfActualElement = pActualFibElement->getType();
		
		switch ( cTypeOfActualElement ){
			case 'r':{
				uiNumberOfLastRoot++;
				if ( pActualFibElement->getNumberOfElement( 'r' ) !=
						uiNumberOfLastRoot ){
					cerr<<"Error: The actual rootelement should be the rootelement number "<<
						uiNumberOfLastRoot<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'r' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextRoot != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an root-element but not the next root-element."<<endl;
					iReturn++;
				}
				pNextRoot  = pActualFibElement->getNextFibElement( 'r' );
			}break;
			case 'p':{
				uiNumberOfLastPoint++;
				if ( pActualFibElement->getNumberOfElement( 'p' ) !=
						uiNumberOfLastPoint ){
					cerr<<"Error: The actual point element should be the point element number "<<
						uiNumberOfLastPoint<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'p' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextPoint != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<" is an point element but not the next point element."<<endl;
					iReturn++;
				}
				pNextPoint = pActualFibElement->getNextFibElement( 'p' );
			}break;
			case 'y':{
				uiNumberOfLastProperty++;
				if ( pActualFibElement->getNumberOfElement( 'y' ) !=
						uiNumberOfLastProperty ){
					cerr<<"Error: The actual property element should be the property element number "<<
						uiNumberOfLastProperty<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'y' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextProperty != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an property element but not the next property element."<<endl;
					iReturn++;
				}
				pNextProperty = pActualFibElement->getNextFibElement( 'y' );
			}break;
			case 'a':{
				uiNumberOfLastArea++;
				if ( pActualFibElement->getNumberOfElement( 'a' ) !=
						uiNumberOfLastArea ){
					cerr<<"Error: The actual area element should be the area element number "<<
						uiNumberOfLastArea <<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'a' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextArea != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an area element but not the next area element."<<endl;
					iReturn++;
				}
				pNextArea = pActualFibElement->getNextFibElement( 'a' );
			}break;
			case 'f':{
				uiNumberOfLastFunction++;
				if ( pActualFibElement->getNumberOfElement( 'f' ) !=
						uiNumberOfLastFunction ){
					cerr<<"Error: The actual function element should be the function element number "<<
						uiNumberOfLastFunction <<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'f' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextFunction != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an function element but not the next function element."<<endl;
					iReturn++;
				}
				pNextFunction = pActualFibElement->getNextFibElement( 'f' );
			}break;
			case 'i':{
				uiNumberOfLastIf++;
				if ( pActualFibElement->getNumberOfElement( 'i' ) !=
						uiNumberOfLastIf ){
					cerr<<"Error: The actual if-element should be the if-element number "<<
						uiNumberOfLastIf <<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'i' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextIf != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an if-element but not the next if-element."<<endl;
					iReturn++;
				}
				pNextIf = pActualFibElement->getNextFibElement( 'i' );
			}break;
			case 'c':{
				uiNumberOfLastComment++;
				if ( pActualFibElement->getNumberOfElement( 'c' ) !=
						uiNumberOfLastComment ){
					cerr<<"Error: The actual comment element should be the comment element number "<<
						uiNumberOfLastComment <<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'c' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextComment != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an comment element but not the next comment element."<<endl;
					iReturn++;
				}
				pNextComment = pActualFibElement->getNextFibElement( 'c' );
			}break;
			case 'l':{
				uiNumberOfLastList++;
				if ( pActualFibElement->getNumberOfElement( 'l' ) !=
						uiNumberOfLastList ){
					cerr<<"Error: The actual list element should be the list element number "<<
						uiNumberOfLastList<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'l' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextList != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an list element but not the next list element."<<endl;
					iReturn++;
				}
				pNextList = pActualFibElement->getNextFibElement( 'l' );
			}break;
			case 'o':{
				uiNumberOfLastExtObject++;
				if ( pActualFibElement->getNumberOfElement( 'o' ) !=
						uiNumberOfLastExtObject ){
					cerr<<"Error: The actual external object element should be the external object element number "<<
						uiNumberOfLastExtObject<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'o' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextExtObject != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an external object element but not the next external object element."<<endl;
					iReturn++;
				}
				pNextExtObject = pActualFibElement->getNextFibElement( 'o' );
			}break;
			case 's':{
				uiNumberOfLastExtSubobject++;
				if ( pActualFibElement->getNumberOfElement( 's' ) !=
						uiNumberOfLastExtSubobject ){
					cerr<<"Error: The actual external subobject element should be the external subobject element number "<<
						uiNumberOfLastExtSubobject<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 's' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextExtSubobject != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an external subobject element but not the next external subobject element."<<endl;
					iReturn++;
				}
				pNextExtSubobject = pActualFibElement->getNextFibElement( 's' );
			}break;
			case 'v':{
				uiNumberOfLastSet++;
				if ( pActualFibElement->getNumberOfElement( 'v' ) !=
						uiNumberOfLastSet ){
					cerr<<"Error: The actual set element should be the set element number "<<
						uiNumberOfLastSet<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'v' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextSet != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an set element but not the next set element."<<endl;
					iReturn++;
				}
				pNextSet = pActualFibElement->getNextFibElement( 'v' );
			}break;
			case 'm':{
				uiNumberOfLastMatrix++;
				if ( pActualFibElement->getNumberOfElement( 'm' ) !=
						uiNumberOfLastMatrix ){
					cerr<<"Error: The actual matrix element should be the matrix element number "<<
						uiNumberOfLastMatrix<<" , but returns the number "<<
						pActualFibElement->getNumberOfElement( 'm' ) <<" ."<<endl;
					iReturn++;
				}
				if ( pNextMatrix != pActualFibElement ){
					cerr<<"Error: The actual Fib element (number="<< uiNumberOfActualFibElement
						<<") is an matrix element but not the next matrix element."<<endl;
					iReturn++;
				}
				pNextMatrix = pActualFibElement->getNextFibElement( 'm' );
			}break;
		}
		
		if ( pActualFibElement->isMovable() ){
			uiNumberOfLastMovePoint++;
			if ( pActualFibElement->getNumberOfMovePoint() !=
					uiNumberOfLastMovePoint ){
				cerr<<"Error: The actual Fib element (number="<<
					uiNumberOfActualFibElement<<") should be the movepoint number "<<
					uiNumberOfLastMovePoint <<" , but returns the number "<<
					pActualFibElement->getNumberOfMovePoint() <<" ."<<endl;
				iReturn++;
			}
		}else{
			if ( pActualFibElement->getNumberOfMovePoint() != 0 ){
				cerr<<"Error: The actual Fib element (number="<<
					uiNumberOfActualFibElement <<") should give back 0 as "<<
					"it's movepoint number, but returns the number "<<
					pActualFibElement->getNumberOfMovePoint() <<" ."<<endl;
				iReturn++;
			}
		}
		if ( isBranchElement( pActualFibElement->getSuperiorFibElement() ) ){
			uiNumberOfLastObjectPoint++;
		}
		if ( pActualFibElement->getNumberOfObjectPoint() !=
				uiNumberOfLastObjectPoint ){
			cerr<<"Error: The actual Fib element (number="<<
				uiNumberOfActualFibElement<<") should have the objectpoint number "<<
				uiNumberOfLastObjectPoint <<" , but returns the number "<<
				pActualFibElement->getNumberOfObjectPoint() <<" ."<<endl;
			iReturn++;
		}
		if ( ! pActualFibElement->hasUnderAllObjects() ){
			cerr<<"Error: The actual Fib element (number="<<
				uiNumberOfActualFibElement <<") dosn't have all subobjects ."<<endl;
			iReturn++;
		}
		
		if ( uiNumberOfNextFibElement <= 1 ){
			if ( pActualFibElement != pNextNumberFibElement ){
				cerr<<"Error: The next Fib element (number="<<pNextNumberFibElement->getNumberOfElement()<<
					") for a number, should be the actual Fib element (number="<<
					pActualFibElement->getNumberOfElement()<<"="<<
					uiNumberOfActualFibElement <<") but isn't it  ."<<endl;
				iReturn++;
			}
			/*check getFibElement(longFib lNumber, false) for random coosen
			Fib element with random choosen lNumber*/
			uiNumberOfNextFibElement = (rand() % (uiNumberOfAllFibElements / 100 + 1)) + 2;
			pNextNumberFibElement = pActualFibElement->getFibElement( uiNumberOfNextFibElement );
			
			/*check if getConstFibElement(longFib lNumber, false) is equal to
			getFibElement(longFib lNumber, false)*/
			pConstNextNumberFibElement =
				pActualFibElement->getConstFibElement( uiNumberOfNextFibElement );
				
			if ( pConstNextNumberFibElement != pNextNumberFibElement ){
				cerr<<"Error: The next const "<< uiNumberOfNextFibElement <<
					"'th Fib element from the "<< uiNumberOfActualFibElement <<
					"'th next Fib element is not equal to the next "<<
					uiNumberOfNextFibElement <<"'th Fib element"<<
					" (getFibElement() != getConstFibElement())"<<endl;
				iReturn++;
			}
		}
		uiNumberOfNextFibElement--;
		
		uiElementsTillNextGetFibElementAbsolutCheck--;
		if ( uiElementsTillNextGetFibElementAbsolutCheck == 0 ){
			uiElementsTillNextGetFibElementAbsolutCheck =
				(rand() % (uiNumberOfAllFibElements / 100 + 1)) + 3;
			//check list of absolute Fib elements
			for ( list< pair<cFibElement *, unsigned int> >::const_iterator
					itrAbsolutElement = liAbsolutNextFibElements.begin();
					itrAbsolutElement != liAbsolutNextFibElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteFibElement = pActualFibElement->getFibElement(
					itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteFibElement ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th Fib element from the "<< uiNumberOfActualFibElement <<
						"'th next Fib element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th Fib element."<<endl;
					if ( pNextNumberAbsoluteFibElement == NULL){
						cerr<<"   The evalued Fib element is NULL."<<endl;
					}
					if ( itrAbsolutElement->first == NULL){
						cerr<<"   The stored Fib element is NULL."<<endl;
					}
					iReturn++;
				}
				/*check if getConstFibElement(longFib lNumber, true) is equal to
				getFibElement(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteFibElement =
					pConstFibElement->getConstFibElement(
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteFibElement != pNextNumberAbsoluteFibElement ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th Fib element from the "<< uiNumberOfActualFibElement <<
						"'th next Fib element is not equal to the next "<<
						itrAbsolutElement->second <<"'th Fib element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( lNumber, bAbsolute=false )
		switch ( cTypeOfActualElement ){
			case 'r':{
				if ( uiNumberOfNextRootElement == 1 ){
					if ( pNextNumberRootElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"root-element, but not the next evalued root-element for the number."<<endl;
						iReturn++;
					}
					//evalue new next root-element, but not from the actual root element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextRootElement = (rand() % uiNumberOfAllRootElements / 100 + 5) + 2;
						pNextNumberRootElement = pNextStartElement->getFibElement( 'r', uiNumberOfNextRootElement );
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberRootElement =
							pNextStartElement->getConstFibElement( 'r', uiNumberOfNextRootElement );
							
						if ( pConstNextNumberRootElement != pNextNumberRootElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextRootElement <<
								"'th rootelement from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextRootElement <<"'th rootelement"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of root-elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'r' ){
								uiNumberOfNextRootElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextRootElement ){
					uiNumberOfNextRootElement--;
				}
			}break;
			case 'p':{
				if ( uiNumberOfNextPointElement == 1 ){
					if ( pNextNumberPointElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"point -element, but not the next evalued point element for the number."<<endl;
						iReturn++;
					}
					//evalue new next point -element, but not from the actual point element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextPointElement = (rand() % uiNumberOfAllPointElements / 100 + 5) + 2;
						pNextNumberPointElement = pNextStartElement->getFibElement( 'p', uiNumberOfNextPointElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberPointElement =
							pNextStartElement->getConstFibElement( 'p', uiNumberOfNextPointElement );
							
						if ( pConstNextNumberPointElement != pNextNumberPointElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextPointElement <<
								"'th point element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextPointElement <<"'th point element"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of point elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'p' ){
								uiNumberOfNextPointElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextPointElement ){
					uiNumberOfNextPointElement--;
				}
			}break;
			case 'y':{
				if ( uiNumberOfNextPropertyElement == 1 ){
					if ( pNextNumberPropertyElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"property element, but not the next evalued property element for the number."<<endl;
						iReturn++;
					}
					//evalue new next property -element, but not from the actual property element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextPropertyElement = (rand() % uiNumberOfAllPropertyElements / 100 + 5) + 2;
						pNextNumberPropertyElement = pNextStartElement->getFibElement( 'y', uiNumberOfNextPropertyElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberPropertyElement =
							pNextStartElement->getConstFibElement( 'y', uiNumberOfNextPropertyElement );
							
						if ( pConstNextNumberPropertyElement != pNextNumberPropertyElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextPropertyElement <<
								"'th property element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextPropertyElement <<"'th property element"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of property elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'y' ){
								uiNumberOfNextPropertyElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextPropertyElement ){
					uiNumberOfNextPropertyElement--;
				}
			}break;
			case 'a':{
				if ( uiNumberOfNextAreaElement == 1 ){
					if ( pNextNumberAreaElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"area element, but not the next evalued area element for the number."<<endl;
						iReturn++;
					}
					//evalue new next area element, but not from the actual area element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextAreaElement = (rand() % uiNumberOfAllAreaElements / 100 + 5) + 2;
						pNextNumberAreaElement = pNextStartElement->getFibElement( 'a', uiNumberOfNextAreaElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberAreaElement =
							pNextStartElement->getConstFibElement( 'a', uiNumberOfNextAreaElement );
							
						if ( pConstNextNumberAreaElement != pNextNumberAreaElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextAreaElement <<
								"'th area element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextAreaElement <<"'th area element"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of area elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'a' ){
								uiNumberOfNextAreaElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextAreaElement ){
					uiNumberOfNextAreaElement--;
				}
			}break;
			case 'f':{
				if ( uiNumberOfNextFunctionElement == 1 ){
					if ( pNextNumberFunctionElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"function element, but not the next evalued function element for the number."<<endl;
						iReturn++;
					}
					//evalue new next function element, but not from the actual function element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextFunctionElement = (rand() % uiNumberOfAllFunctionElements / 100 + 5) + 2;
						pNextNumberFunctionElement = pNextStartElement->getFibElement( 'f', uiNumberOfNextFunctionElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberFunctionElement =
							pNextStartElement->getConstFibElement( 'f', uiNumberOfNextFunctionElement );
							
						if ( pConstNextNumberFunctionElement != pNextNumberFunctionElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextFunctionElement <<
								"'th function element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextFunctionElement <<"'th function element"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of function elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'f' ){
								uiNumberOfNextFunctionElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextFunctionElement ){
					uiNumberOfNextFunctionElement--;
				}
			}break;
			case 'i':{
				if ( uiNumberOfNextIfElement == 1 ){
					if ( pNextNumberIfElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"if-element, but not the next evalued if-element for the number."<<endl;
						iReturn++;
					}
					//evalue new next if-element, but not from the actual if-element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextIfElement = (rand() % uiNumberOfAllIfElements / 100 + 5) + 2;
						pNextNumberIfElement = pNextStartElement->getFibElement( 'i', uiNumberOfNextIfElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberIfElement =
							pNextStartElement->getConstFibElement( 'i', uiNumberOfNextIfElement );
							
						if ( pConstNextNumberIfElement != pNextNumberIfElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextIfElement <<
								"'th if-element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextIfElement <<"'th if-element"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of if-elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'i' ){
								uiNumberOfNextIfElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextIfElement ){
					uiNumberOfNextIfElement--;
				}
			}break;
			case 'c':{
				if ( uiNumberOfNextCommentElement == 1 ){
					if ( pNextNumberCommentElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"comment element, but not the next evalued comment element for the number."<<endl;
						iReturn++;
					}
					//evalue new next comment element, but not from the actual comment element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextCommentElement = (rand() % uiNumberOfAllCommentElements / 100 + 5) + 2;
						pNextNumberCommentElement = pNextStartElement->getFibElement( 'c', uiNumberOfNextCommentElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberCommentElement =
							pNextStartElement->getConstFibElement( 'c', uiNumberOfNextCommentElement );
							
						if ( pConstNextNumberCommentElement != pNextNumberCommentElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextCommentElement <<
								"'th comment element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
								uiNumberOfNextCommentElement <<"'th comment element"<<
								" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of comment elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'c' ){
								uiNumberOfNextCommentElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextCommentElement ){
					uiNumberOfNextCommentElement--;
				}
			}break;
			case 'l':{
				if ( uiNumberOfNextListElement == 1 ){
					if ( pNextNumberListElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"list -element, but not the next evalued list element for the number."<<endl;
						iReturn++;
					}
					//evalue new next list -element, but not from the actual list element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextListElement = (rand() % uiNumberOfAllListElements / 100 + 5) + 2;
						pNextNumberListElement = pNextStartElement->getFibElement( 'l', uiNumberOfNextListElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberListElement =
							pNextStartElement->getConstFibElement( 'l', uiNumberOfNextListElement );
							
						if ( pConstNextNumberListElement != pNextNumberListElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextListElement <<
								"'th list element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
									uiNumberOfNextListElement <<"'th list element"<<
									" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of list elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'l' ){
								uiNumberOfNextListElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextListElement ){
					uiNumberOfNextListElement--;
				}
			}break;
			case 'o':{
				if ( uiNumberOfNextExtObjectElement == 1 ){
					if ( pNextNumberExtObjectElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"external object  element, but not the next evalued external object element for the number."<<endl;
						iReturn++;
					}
					//evalue new next external object  element, but not from the actual external object  element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextExtObjectElement = (rand() % uiNumberOfAllExtObjectElements / 100 + 5) + 2;
						pNextNumberExtObjectElement = pNextStartElement->getFibElement( 'o', uiNumberOfNextExtObjectElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberExtObjectElement =
							pNextStartElement->getConstFibElement( 'o', uiNumberOfNextExtObjectElement );
							
						if ( pConstNextNumberExtObjectElement != pNextNumberExtObjectElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextExtObjectElement <<
								"'th external object  element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
								uiNumberOfNextExtObjectElement <<"'th external object element"<<
								" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of external object  elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'o' ){
								uiNumberOfNextExtObjectElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextExtObjectElement ){
					uiNumberOfNextExtObjectElement--;
				}
			}break;
			case 's':{
				if ( uiNumberOfNextExtSubobjectElement == 1 ){
					if ( pNextNumberExtSubobjectElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"external subobject  element, but not the next evalued external subobject element for the number."<<endl;
						iReturn++;
					}
					//evalue new next external subobject  element, but not from the actual external subobject  element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextExtSubobjectElement = (rand() % uiNumberOfAllExtSubobjectElements / 100 + 5) + 2;
						pNextNumberExtSubobjectElement = pNextStartElement->getFibElement( 's', uiNumberOfNextExtSubobjectElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberExtSubobjectElement =
							pNextStartElement->getConstFibElement( 's', uiNumberOfNextExtSubobjectElement );
							
						if ( pConstNextNumberExtSubobjectElement != pNextNumberExtSubobjectElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextExtSubobjectElement <<
								"'th external subobject  element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
								uiNumberOfNextExtSubobjectElement <<"'th external subobject element"<<
								" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of external subobject  elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 's' ){
								uiNumberOfNextExtSubobjectElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextExtSubobjectElement ){
					uiNumberOfNextExtSubobjectElement--;
				}
			}break;
			case 'v':{
				if ( uiNumberOfNextSetElement == 1 ){
					if ( pNextNumberSetElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"set  element, but not the next evalued set element for the number."<<endl;
						iReturn++;
					}
					//evalue new next set  element, but not from the actual set  element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextSetElement = (rand() % uiNumberOfAllSetElements / 100 + 5) + 2;
						pNextNumberSetElement = pNextStartElement->getFibElement( 'v', uiNumberOfNextSetElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberSetElement =
							pNextStartElement->getConstFibElement( 'v', uiNumberOfNextSetElement );
							
						if ( pConstNextNumberSetElement != pNextNumberSetElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextSetElement <<
								"'th set  element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
								uiNumberOfNextSetElement <<"'th set element"<<
								" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of set  elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'v' ){
								uiNumberOfNextSetElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextSetElement ){
					uiNumberOfNextSetElement--;
				}
			}break;
			case 'm':{
				if ( uiNumberOfNextMatrixElement == 1 ){
					if ( pNextNumberMatrixElement != pActualFibElement ){
						cerr<<"Error: The actual Fib element (number="<<
							uiNumberOfActualFibElement <<") is an number'th "<<
							"matrix  element, but not the next evalued matrix element for the number."<<endl;
						iReturn++;
					}
					//evalue new next matrix  element, but not from the actual matrix  element
					cFibElement * pNextStartElement = pActualFibElement->getFibElement( (rand() % 10) );
					if ( pNextStartElement ){
						uiNumberOfNextMatrixElement = (rand() % uiNumberOfAllMatrixElements / 100 + 5) + 2;
						pNextNumberMatrixElement = pNextStartElement->getFibElement( 'm', uiNumberOfNextMatrixElement );
						
						/*check if getConstFibElement( char cType, longFib lNumber, false) is equal to
						getFibElement( char cType, longFib lNumber, false)*/
						cFibElement * pConstNextNumberMatrixElement =
							pNextStartElement->getConstFibElement( 'm', uiNumberOfNextMatrixElement );
							
						if ( pConstNextNumberMatrixElement != pNextNumberMatrixElement ){
							cerr<<"Error: The next const "<< uiNumberOfNextMatrixElement <<
								"'th matrix  element from the "<< pNextStartElement->getNumberOfElement() <<
								"'th next Fib element is not equal to the next "<<
								uiNumberOfNextMatrixElement <<"'th matrix element"<<
								" (getFibElement() != getConstFibElement())"<<endl;
							iReturn++;
						}
						//incrase the number with the number of matrix  elements betwean the actual (inclusive) and start -element
						while ( pActualFibElement != pNextStartElement ){
							pNextStartElement = pNextStartElement->getFibElement( -1 );
							if ( pNextStartElement->getType() == 'm' ){
								uiNumberOfNextMatrixElement++;
							}
						}
					}
				}
				if ( 0 < uiNumberOfNextMatrixElement ){
					uiNumberOfNextMatrixElement--;
				}
			}break;
		}//end switch check getFibElement( lNumber, bAbsolute=false )
		
		//check getFibElement( 'p', lNumber, bAbsolute=true )
		uiElementsTillNextGetPointElementAbsolutCheck--;
		if ( uiElementsTillNextGetPointElementAbsolutCheck == 0 ){
			uiElementsTillNextGetPointElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check list of absolute point elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextPointElements.begin();
					itrAbsolutElement != liAbsolutNextPointElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsolutePoint = pActualFibElement->getFibElement(
					'p', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsolutePoint ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th point element from the "<< uiNumberOfActualFibElement <<
						" next point element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th point element."<<endl;
					iReturn++;
				}
				/*check if getConstPoint(longFib lNumber, true) is equal to
				getPoint(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsolutePoint =
					pConstFibElement->getConstFibElement( 'p',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsolutePoint != pNextNumberAbsolutePoint ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th point element from the "<< uiNumberOfActualFibElement <<
						" next point element is not equal to the next "<<
						itrAbsolutElement->second <<"'th point element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'l', lNumber, bAbsolute=true )
		uiElementsTillNextGetListElementAbsolutCheck--;
		if ( uiElementsTillNextGetListElementAbsolutCheck == 0 ){
			uiElementsTillNextGetListElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check list of absolute list elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextListElements.begin();
					itrAbsolutElement != liAbsolutNextListElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteList = pActualFibElement->getFibElement(
					'l', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteList ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th list element from the "<< uiNumberOfActualFibElement <<
						" next list element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th list element."<<endl;
					iReturn++;
				}
				/*check if getConstList(longFib lNumber, true) is equal to
				getList(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteList =
					pConstFibElement->getConstFibElement( 'l',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteList != pNextNumberAbsoluteList ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th list element from the "<< uiNumberOfActualFibElement <<
						" next list element is not equal to the next "<<
						itrAbsolutElement->second <<"'th list element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}

		//check getFibElement( 'y', lNumber, bAbsolute=true )
		uiElementsTillNextGetPropertyElementAbsolutCheck--;
		if ( uiElementsTillNextGetPropertyElementAbsolutCheck == 0 ){
			uiElementsTillNextGetPropertyElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check property of absolute property elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextPropertyElements.begin();
					itrAbsolutElement != liAbsolutNextPropertyElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteProperty = pActualFibElement->getFibElement(
					'y', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteProperty ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th property element from the "<< uiNumberOfActualFibElement <<
						" next property element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th property element."<<endl;
					iReturn++;
				}
				/*check if getConstProperty(longFib lNumber, true) is equal to
				getProperty(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteProperty =
					pConstFibElement->getConstFibElement( 'y',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteProperty != pNextNumberAbsoluteProperty ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th property element from the "<< uiNumberOfActualFibElement <<
						" next property element is not equal to the next "<<
						itrAbsolutElement->second <<"'th property element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'a', lNumber, bAbsolute=true )
		uiElementsTillNextGetAreaElementAbsolutCheck--;
		if ( uiElementsTillNextGetAreaElementAbsolutCheck == 0 ){
			uiElementsTillNextGetAreaElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check area of absolute area elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextAreaElements.begin();
					itrAbsolutElement != liAbsolutNextAreaElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteArea = pActualFibElement->getFibElement(
					'a', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteArea ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th area element from the "<< uiNumberOfActualFibElement <<
						" next area element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th area element."<<endl;
					iReturn++;
				}
				/*check if getConstArea(longFib lNumber, true) is equal to
				getArea(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteArea =
					pConstFibElement->getConstFibElement( 'a',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteArea != pNextNumberAbsoluteArea ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th area element from the "<< uiNumberOfActualFibElement <<
						" next area element is not equal to the next "<<
						itrAbsolutElement->second <<"'th area element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'f', lNumber, bAbsolute=true )
		uiElementsTillNextGetFunctionElementAbsolutCheck--;
		if ( uiElementsTillNextGetFunctionElementAbsolutCheck == 0 ){
			uiElementsTillNextGetFunctionElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check function of absolute function elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextFunctionElements.begin();
					itrAbsolutElement != liAbsolutNextFunctionElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteFunction = pActualFibElement->getFibElement(
					'f', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteFunction ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th function element from the "<< uiNumberOfActualFibElement <<
						" next function element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th function element."<<endl;
					iReturn++;
				}
				/*check if getConstFunction(longFib lNumber, true) is equal to
				getFunction(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteFunction =
					pConstFibElement->getConstFibElement( 'f',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteFunction != pNextNumberAbsoluteFunction ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th function element from the "<< uiNumberOfActualFibElement <<
						" next function element is not equal to the next "<<
						itrAbsolutElement->second <<"'th function element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'i', lNumber, bAbsolute=true )
		uiElementsTillNextGetIfElementAbsolutCheck--;
		if ( uiElementsTillNextGetIfElementAbsolutCheck == 0 ){
			uiElementsTillNextGetIfElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check if of absolute if-elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextIfElements.begin();
					itrAbsolutElement != liAbsolutNextIfElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteIf = pActualFibElement->getFibElement(
					'i', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteIf ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th if-element from the "<< uiNumberOfActualFibElement <<
						" next if-element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th if-element."<<endl;
					iReturn++;
				}
				/*check if getConstIf(longFib lNumber, true) is equal to
				getIf(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteIf =
					pConstFibElement->getConstFibElement( 'i',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteIf != pNextNumberAbsoluteIf ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th if-element from the "<< uiNumberOfActualFibElement <<
						" next if-element is not equal to the next "<<
						itrAbsolutElement->second <<"'th if-element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'c', lNumber, bAbsolute=true )
		uiElementsTillNextGetCommentElementAbsolutCheck--;
		if ( uiElementsTillNextGetCommentElementAbsolutCheck == 0 ){
			uiElementsTillNextGetCommentElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check comment of absolute comment elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextCommentElements.begin();
					itrAbsolutElement != liAbsolutNextCommentElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteComment = pActualFibElement->getFibElement(
					'c', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteComment ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th comment element from the "<< uiNumberOfActualFibElement <<
						" next comment element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th comment element."<<endl;
					iReturn++;
				}
				/*check if getConstComment(longFib lNumber, true) is equal to
				getComment(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteComment =
					pConstFibElement->getConstFibElement( 'c',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteComment != pNextNumberAbsoluteComment ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th comment element from the "<< uiNumberOfActualFibElement <<
						" next comment element is not equal to the next "<<
						itrAbsolutElement->second <<"'th comment element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}

		//check getFibElement( 'o', lNumber, bAbsolute=true )
		uiElementsTillNextGetExtObjectElementAbsolutCheck--;
		if ( uiElementsTillNextGetExtObjectElementAbsolutCheck == 0 ){
			uiElementsTillNextGetExtObjectElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check external object of absolute external object elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextExtObjectElements.begin();
					itrAbsolutElement != liAbsolutNextExtObjectElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteExtObject = pActualFibElement->getFibElement(
					'o', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteExtObject ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th external object element from the "<< uiNumberOfActualFibElement <<
						" next external object element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th external object element."<<endl;
					iReturn++;
				}
				/*check if getConstExtObject(longFib lNumber, true) is equal to
				getExtObject(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteExtObject =
					pConstFibElement->getConstFibElement( 'o',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteExtObject != pNextNumberAbsoluteExtObject ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th external object element from the "<< uiNumberOfActualFibElement <<
						" next external object element is not equal to the next "<<
						itrAbsolutElement->second <<"'th external object element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}

		//check getFibElement( 's', lNumber, bAbsolute=true )
		uiElementsTillNextGetExtSubobjectElementAbsolutCheck--;
		if ( uiElementsTillNextGetExtSubobjectElementAbsolutCheck == 0 ){
			uiElementsTillNextGetExtSubobjectElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check external subobject of absolute external subobject elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextExtSubobjectElements.begin();
					itrAbsolutElement != liAbsolutNextExtSubobjectElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteExtSubobject = pActualFibElement->getFibElement(
					's', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteExtSubobject ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th external subobject element from the "<< uiNumberOfActualFibElement <<
						" next external subobject element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th external subobject element."<<endl;
					iReturn++;
				}
				/*check if getConstExtSubobject(longFib lNumber, true) is equal to
				getExtSubobject(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteExtSubobject =
					pConstFibElement->getConstFibElement( 's',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteExtSubobject != pNextNumberAbsoluteExtSubobject ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th external subobject element from the "<< uiNumberOfActualFibElement <<
						" next external subobject element is not equal to the next "<<
						itrAbsolutElement->second <<"'th external subobject element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'v', lNumber, bAbsolute=true )
		uiElementsTillNextGetSetElementAbsolutCheck--;
		if ( uiElementsTillNextGetSetElementAbsolutCheck == 0 ){
			uiElementsTillNextGetSetElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check set of absolute set elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextSetElements.begin();
					itrAbsolutElement != liAbsolutNextSetElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteSet = pActualFibElement->getFibElement(
					'v', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteSet ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th set element from the "<< uiNumberOfActualFibElement <<
						" next set element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th set element."<<endl;
					iReturn++;
				}
				/*check if getConstSet(longFib lNumber, true) is equal to
				getSet(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteSet =
					pConstFibElement->getConstFibElement( 'v',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteSet != pNextNumberAbsoluteSet ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th set element from the "<< uiNumberOfActualFibElement <<
						" next set element is not equal to the next "<<
						itrAbsolutElement->second <<"'th set element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getFibElement( 'm', lNumber, bAbsolute=true )
		uiElementsTillNextGetMatrixElementAbsolutCheck--;
		if ( uiElementsTillNextGetMatrixElementAbsolutCheck == 0 ){
			uiElementsTillNextGetMatrixElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check matrix of absolute matrix elements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextMatrixElements.begin();
					itrAbsolutElement != liAbsolutNextMatrixElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteMatrix = pActualFibElement->getFibElement(
					'm', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteMatrix ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th matrix element from the "<< uiNumberOfActualFibElement <<
						" next matrix element is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th matrix element."<<endl;
					iReturn++;
				}
				/*check if getConstMatrix(longFib lNumber, true) is equal to
				getMatrix(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteMatrix =
					pConstFibElement->getConstFibElement( 'm',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteMatrix != pNextNumberAbsoluteMatrix ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th matrix element from the "<< uiNumberOfActualFibElement <<
						" next matrix element is not equal to the next "<<
						itrAbsolutElement->second <<"'th matrix element"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}

		//check getFibElement( 'r', lNumber, bAbsolute=true )
		uiElementsTillNextGetRootElementAbsolutCheck--;
		if ( uiElementsTillNextGetRootElementAbsolutCheck == 0 ){
			uiElementsTillNextGetRootElementAbsolutCheck =
				(rand() % uiNumberOfAllFibElements / 100 + 1) + 3;
			//check root of absolute rootelements
			for ( list< pair<cFibElement *, unsigned int> >::iterator
					itrAbsolutElement = liAbsolutNextRootElements.begin();
					itrAbsolutElement != liAbsolutNextRootElements.end();
					itrAbsolutElement++ ){
				
				cFibElement * pNextNumberAbsoluteRoot = pActualFibElement->getFibElement(
					'r', itrAbsolutElement->second, true );
				
				if ( itrAbsolutElement->first != pNextNumberAbsoluteRoot ){
					cerr<<"Error: The next absolute "<< itrAbsolutElement->second <<
						"'th rootelement from the "<< uiNumberOfActualFibElement <<
						" next rootelement is not equal to the stored next "<<
						itrAbsolutElement->second <<"'th rootelement."<<endl;
					iReturn++;
				}
				/*check if getConstRoot(longFib lNumber, true) is equal to
				getRoot(longFib lNumber, false)*/
				const cFibElement * pConstFibElement = pActualFibElement;
				cFibElement * pConstNextNumberAbsoluteRoot =
					pConstFibElement->getConstFibElement( 'r',
					itrAbsolutElement->second, true );
					
				if ( pConstNextNumberAbsoluteRoot != pNextNumberAbsoluteRoot ){
					cerr<<"Error: The next absolute const "<< itrAbsolutElement->second <<
						"'th rootelement from the "<< uiNumberOfActualFibElement <<
						" next rootelement is not equal to the next "<<
						itrAbsolutElement->second <<"'th rootelement"<<
						" (getFibElement() != getConstFibElement())"<<endl;
					iReturn++;
				}
			}
		}
		
		//check getSuperiorFibElement(); check for every Fib element type seperatly
		switch ( cTypeOfActualElement ){
			case 'r':{//Root
				//check main -Fib object
				if ( pActualFibElement->getNextFibElement() == NULL ){
					cerr<<"Error: The root-element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) has no next Fib element "<<
						"respectively main -Fib object."<< endl;
					iReturn++;
				}else if ( (pActualFibElement->getNextFibElement()->
						getSuperiorFibElement()) != pActualFibElement ){
					cerr<<"Error: The root-element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) next Fib element "<<
						"respectively main -Fib object has not the root-element as "<<
						"it's superior Fib element."<< endl;
					iReturn++;
				}
				cRoot * pActualRoot = (cRoot*)pActualFibElement;
				for ( unsigned int uiActualSubRoot = 1;
						uiActualSubRoot <= pActualRoot->getNumberOfSubRootObjects();
						uiActualSubRoot++ ){
						
					cFibElement * pActualSubRoot =
						pActualRoot->getSubRootObject( uiActualSubRoot ).second;
					
					if ( pActualSubRoot == NULL ){
						cerr<<"Error: The root-element (Fib element number="<<
							uiNumberOfActualFibElement <<" ) has no "<<
							uiActualSubRoot <<"'th sub -root object, but should have one."<< endl;
						iReturn++;
					}else if ( pActualSubRoot->getSuperiorFibElement() != pActualFibElement ){
						cerr<<"Error: The root-element (Fib element number="<<
							uiNumberOfActualFibElement <<" ) "<< uiActualSubRoot <<
							"'th sub -root object has not the root-element as "<<
							"it's superior Fib element."<< endl;
						iReturn++;
					}
				}
			}break;
			case 'a'://Area
			case 'f'://Function
			case 'c'://Comment
			case 'y'://Property
			case 'v'://set-element
			case 'm':{//matrix element
				if ( pActualFibElement->getNextFibElement() == NULL ){
					cerr<<"Error: The limb Fib element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) has no next Fib element "<<
						"respectively subobject."<< endl;
					iReturn++;
				}else if ( (pActualFibElement->getNextFibElement()->
						getSuperiorFibElement()) != pActualFibElement ){
					cerr<<"Error: The limb Fib element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) next Fib element "<<
						"respectively subobject has not the Fib element as "<<
						"it's superior Fib element."<< endl;
					iReturn++;
				}
			}break;
			case 'i':{//if-element
				cIf * pActualIf = (cIf*)pActualFibElement;
				
				cFibElement * pActualUnderobjectTrue =
					pActualIf->getTrueCase();
				
				if ( pActualUnderobjectTrue == NULL ){
					cerr<<"Error: The if-element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) has no true case "<<
						"subobject, but should have one."<< endl;
					iReturn++;
				}else if ( pActualUnderobjectTrue->getSuperiorFibElement() != pActualFibElement ){
					cerr<<"Error: The if-element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) true case subobject "<<
						"has not the if-element as "<<
						"it's superior Fib element."<< endl;
					iReturn++;
				}
				cFibElement * pActualUnderobjectFalse =
					pActualIf->getFalseCase();
				
				if ( pActualUnderobjectFalse == NULL ){
					cerr<<"Error: The if-element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) has no false case "<<
						"subobject, but should have one."<< endl;
					iReturn++;
				}else if ( pActualUnderobjectFalse->getSuperiorFibElement() != pActualFibElement ){
					cerr<<"Error: The if-element (Fib element number="<<
						uiNumberOfActualFibElement <<" ) false case subobject "<<
						"has not the if-element as "<<
						"it's superior Fib element."<< endl;
					iReturn++;
				}
				
			}break;
			case 'l':{//List
				cList * pActualList = (cList*)pActualFibElement;
				for ( unsigned int uiActualUnderobject = 1;
						uiActualUnderobject <= pActualList->getNumberOfUnderobjects();
						uiActualUnderobject++ ){
						
					cFibElement * pActualUnderobject =
						pActualList->getUnderobject( uiActualUnderobject );
					
					if ( pActualUnderobject == NULL ){
						cerr<<"Error: The list element (Fib element number="<<
							uiNumberOfActualFibElement <<" ) has no "<<
							uiActualUnderobject <<"'th subobject, but should have one."<< endl;
						iReturn++;
					}else if ( pActualUnderobject->getSuperiorFibElement() != pActualFibElement ){
						cerr<<"Error: The list element (Fib element number="<<
							uiNumberOfActualFibElement <<" ) "<< uiActualUnderobject <<
							"'th subobject has not the list element as "<<
							"it's superior Fib element."<< endl;
						iReturn++;
					}
				}
			}break;
			case 'o':{//external object
				cExtObject * pActualExtObject = (cExtObject*)pActualFibElement;
				const unsigned int uiNumberOfSubobjects =
					pActualExtObject->getNumberOfSubobjects();
				for ( unsigned int uiActualUnderobject = 1;
						uiActualUnderobject <= uiNumberOfSubobjects;
						uiActualUnderobject++ ){
						
					cFibElement * pActualUnderobject =
						pActualExtObject->getSubobject( uiActualUnderobject );
					
					if ( pActualUnderobject == NULL ){
						cerr<<"Error: The external object element (Fib element number="<<
							uiNumberOfActualFibElement <<" ) has no "<<
							uiActualUnderobject <<"'th subobject, but should have one."<< endl;
						iReturn++;
					}else if ( pActualUnderobject->getSuperiorFibElement() != pActualFibElement ){
						cerr<<"Error: The external object element (Fib element number="<<
							uiNumberOfActualFibElement <<" ) "<< uiActualUnderobject <<
							"'th subobject (with number "<<pActualUnderobject->getNumberOfElement()<<
							" and type "<<pActualUnderobject->getType()<<
							" ) has not the external object element as "<<
							"it's superior Fib element."<< endl;
						iReturn++;
					}
				}
			}break;
			//don't check leaf elements, they couldn't be superior to an other Fib element
		}//end switch getSuperiorFibElement(); check for every Fib element type seperatly
		
		//check the type of the element
		//branch: List
		if ( pActualFibElement->isBranch() != isBranchElement( pActualFibElement ) ){
			cerr<<"Error: The Fib element says it is "<<
				(pActualFibElement->isBranch()?"":"not ") <<
				"an branchelement, but that not true."<< endl;
			iReturn++;
		}
		//Limb: Property, Area, Function, Comment, set, matrix element
		if ( pActualFibElement->isLimb() != ( (pActualFibElement->getType() == 'y') ||
				(pActualFibElement->getType() == 'a') || (pActualFibElement->getType() == 'f') ||
				(pActualFibElement->getType() == 'c') || (pActualFibElement->getType() == 'v') ||
				(pActualFibElement->getType() == 'm') ) ){
			cerr<<"Error: The Fib element says it is "<<
				(pActualFibElement->isLimb()?"":"not ") <<
				"an limbelement, but that not true."<< endl;
			iReturn++;
		}
		//leaf: Point, external subobject
		if ( pActualFibElement->isLeaf() != ( (pActualFibElement->getType() == 'p') ||
				(pActualFibElement->getType() == 's') ) ){
			cerr<<"Error: The Fib element says it is "<<
				(pActualFibElement->isLeaf()?"":"not ") <<
				"an leaf element, but that not true."<< endl;
			iReturn++;
		}
		
		
		{//check the subobjects
			const cFibElement * pConstFibElement = pActualFibElement;
			
			if ( pActualFibElement->isLeaf() ){
				//test getNumberOfSubobjects()
				if ( pConstFibElement->getNumberOfSubobjects() != 0 ){
					cerr<<"Error: The Fib element is a leaf element, but returns it has "<<
						pConstFibElement->getNumberOfSubobjects()<<" subobjects and not 0 ."<< endl;
					iReturn++;
				}
				//test getSubobjects()
				list< cFibElement * > liSubobjects = pActualFibElement->getSubobjects();
				if ( liSubobjects.size() != 0 ){
					cerr<<"Error: The Fib element is a leaf element, but returns "<<
						liSubobjects.size()<<" subobjects and not non ."<< endl;
					iReturn++;
				}
				const list< cFibElement * > liSubobjectsConst =
					pConstFibElement->getSubobjects();
				if ( liSubobjectsConst.size() != 0 ){
					cerr<<"Error: The Fib element is a leaf element, but returns "<<
						liSubobjectsConst.size()<<" subobjects (const) and not non ."<< endl;
					iReturn++;
				}
				//test getSubobject()
				if ( pActualFibElement->getSubobject( 0 ) != NULL ){
					cerr<<"Error: The Fib element is a leaf element, but returns a 0'th "<<
						pActualFibElement->getSubobject( 0 )<<" subobject "<<
						"( pActualFibElement->getSubobject( 0 ) ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( 0 ) != NULL ){
					cerr<<"Error: The Fib element is a leaf element, but returns a 0'th "<<
						pConstFibElement->getSubobject( 0 )<<" subobject (const) "<<
						"( pConstFibElement->getSubobject( 0 ) ) ."<< endl;
					iReturn++;
				}
				if ( pActualFibElement->getSubobject( 1 ) != NULL ){
					cerr<<"Error: The Fib element is a leaf element, but returns a 1'th "<<
						pActualFibElement->getSubobject( 1 )<<" subobject "<<
						"( pActualFibElement->getSubobject( 1 ) ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( 1 ) != NULL ){
					cerr<<"Error: The Fib element is a leaf element, but returns a 1'th "<<
						pConstFibElement->getSubobject( 1 )<<" subobject (const) "<<
						"( pConstFibElement->getSubobject( 1 ) ) ."<< endl;
					iReturn++;
				}
				if ( pActualFibElement->getSubobject() != NULL ){
					cerr<<"Error: The Fib element is a leaf element, but returns default a "<<
						pActualFibElement->getSubobject()<<" subobject "<<
						"( pActualFibElement->getSubobject() ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject() != NULL ){
					cerr<<"Error: The Fib element is a leaf element, but returns default a "<<
						pConstFibElement->getSubobject()<<" subobject (const) "<<
						"( pConstFibElement->getSubobject() ) ."<< endl;
					iReturn++;
				}
				
			}else if ( pActualFibElement->isLimb() ){
				//test getNumberOfSubobjects()
				if ( pConstFibElement->getNumberOfSubobjects() != 1 ){
					cerr<<"Error: The Fib element is a limb element, but returns it has "<<
						pConstFibElement->getNumberOfSubobjects()<<" subobjects and not 1 ."<< endl;
					iReturn++;
				}
				//get correct subobject
				cFibElement * pCorrectSubobject = pActualFibElement->getNextFibElement();
				//test getSubobjects()
				list< cFibElement * > liSubobjects = pActualFibElement->getSubobjects();
				if ( liSubobjects.size() != 1 ){
					cerr<<"Error: The Fib element is a limb element, but returns "<<
						liSubobjects.size()<<" subobjects and not 1 ."<< endl;
					iReturn++;
				}else{
					if ( liSubobjects.front() != pCorrectSubobject ){
						cerr<<"Error: The Fib element is a limb element, it returns "<<
							liSubobjects.front()<<" as its subobject and not "<<
							pCorrectSubobject<<" ."<< endl;
						iReturn++;
					}
				}
				const list< cFibElement * > liSubobjectsConst =
					pConstFibElement->getSubobjects();
				if ( liSubobjectsConst.size() != 1 ){
					cerr<<"Error: The Fib element is a limb element, but returns "<<
						liSubobjectsConst.size()<<" subobjects (const) and not 1 ."<< endl;
					iReturn++;
				}else{
					if ( liSubobjectsConst.front() != pCorrectSubobject ){
						cerr<<"Error: The Fib element is a limb element, it returns "<<
							liSubobjectsConst.front()<<" as its subobject (const) and not "<<
							pCorrectSubobject<<" ."<< endl;
						iReturn++;
					}
				}
				//test getSubobject()
				if ( pActualFibElement->getSubobject( 0 ) != NULL ){
					cerr<<"Error: The Fib element is a limb element, but returns a 0'th "<<
						pActualFibElement->getSubobject( 0 )<<" subobject "<<
						"( pActualFibElement->getSubobject( 0 ) ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( 0 ) != NULL ){
					cerr<<"Error: The Fib element is a limb element, but returns a 0'th "<<
						pConstFibElement->getSubobject( 0 )<<" subobject (const) "<<
						"( pConstFibElement->getSubobject( 0 ) ) ."<< endl;
					iReturn++;
				}
				if ( pActualFibElement->getSubobject( 1 ) != pCorrectSubobject ){
					cerr<<"Error: The Fib element is a limb element, it returns "<<
						pActualFibElement->getSubobject( 1 )<<" as its first subobject and not "<<
						pCorrectSubobject<<" ( pActualFibElement->getSubobject( 1 ) )."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( 1 ) != pCorrectSubobject ){
					cerr<<"Error: The Fib element is a limb element, it returns "<<
						pConstFibElement->getSubobject( 1 )<<" as its first subobject (const) and not "<<
						pCorrectSubobject<<" ( pConstFibElement->getSubobject( 1 ) )."<< endl;
					iReturn++;
				}
				if ( pActualFibElement->getSubobject() != pCorrectSubobject ){
					cerr<<"Error: The Fib element is a limb element, it returns "<<
						pActualFibElement->getSubobject()<<" as its default subobject and not "<<
						pCorrectSubobject<<" ( pActualFibElement->getSubobject() )."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject() != pCorrectSubobject ){
					cerr<<"Error: The Fib element is a limb element, it returns "<<
						pConstFibElement->getSubobject()<<" as its default subobject (const) and not "<<
						pCorrectSubobject<<" ( pConstFibElement->getSubobject() )."<< endl;
					iReturn++;
				}
				if ( pActualFibElement->getSubobject( 2 ) != NULL ){
					cerr<<"Error: The Fib element is a limb element, but returns a 2'th "<<
						pActualFibElement->getSubobject( 2 )<<" subobject "<<
						"( pActualFibElement->getSubobject( 2 ) ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( 2 ) != NULL ){
					cerr<<"Error: The Fib element is a limb element, but returns a 2'th "<<
						pConstFibElement->getSubobject( 2 )<<" subobject (const) "<<
						"( pConstFibElement->getSubobject( 2 ) ) ."<< endl;
					iReturn++;
				}
			}else if ( pActualFibElement->isBranch() ){
				
				//evalue list with correct subobjects
				list< cFibElement * > liCorrectSubobjects;
				switch ( cTypeOfActualElement ){
					case 'l':{//list element
						liCorrectSubobjects = ((cList *)
							pActualFibElement)->getUnderobjects();
					}break;
					case 'r':{//root element
						cRoot * pActualRootElement =
							((cRoot *)pActualFibElement);
						
						//add main Fib object
						if ( 1 < pActualRootElement->getNumberOfElements() ){
							//subobjects exists
							cFibElement * pMainFibObject =
								pActualRootElement->getNextFibElement();
							liCorrectSubobjects.push_back( pMainFibObject );
						}
						//add all sub (root) objects
						const unsignedIntFib uiNumberOfSubRootObjects =
							pActualRootElement->getNumberOfSubRootObjects();
						for ( unsigned int uiActualSubobject = 1;
								uiActualSubobject <= uiNumberOfSubRootObjects;
								uiActualSubobject++ ){
							liCorrectSubobjects.push_back(
								pActualRootElement->getSubRootObject(
									uiActualSubobject ).second );
						}//end for all sub root objects
					}break;
					case 'i':{//if object element
						cIf * pActualIfElement = ((cIf *)pActualFibElement);
						liCorrectSubobjects.push_back(
							pActualIfElement->getTrueCase() );
						liCorrectSubobjects.push_back(
							pActualIfElement->getFalseCase() );
					}break;
					case 'o':{//external object element
						//add all subobjects
						cExtObject * pActualExtObject =
							((cExtObject *)pActualFibElement);
						const unsignedIntFib uiNumberOfSubobjects =
							pActualExtObject->getNumberOfSubobjects();
						for ( unsigned int uiActualSubobject = 1;
								uiActualSubobject <= uiNumberOfSubobjects;
								uiActualSubobject++ ){
							liCorrectSubobjects.push_back(
								pActualExtObject->getSubobject( uiActualSubobject ) );
						}//end for all subobjects
					}break;
					
					default:{//Error: unknown Fib element -> take first subobject (if existing)
						if ( 1 < pActualFibElement->getNumberOfElements() ){
							//subobjects exists
							cFibElement * pNextFibElement =
								pActualFibElement->getNextFibElement();
							liCorrectSubobjects.push_back( pNextFibElement );
						}
					}break;
				};
				
				//test getNumberOfSubobjects()
				if ( pConstFibElement->getNumberOfSubobjects() != liCorrectSubobjects.size() ){
					cerr<<"Error: The Fib element is a branch element, it returns it has "<<
						pConstFibElement->getNumberOfSubobjects()<<
						" subobjects and not "<<liCorrectSubobjects.size()<<" ."<< endl;
					iReturn++;
				}
				
				//test getSubobjects()
				list< cFibElement * > liSubobjects = pActualFibElement->getSubobjects();
				if ( liSubobjects.size() != liCorrectSubobjects.size() ){
					cerr<<"Error: The Fib element is a branch element, it returns "<<
						liSubobjects.size()<<" subobjects and not correctly "<<
						liCorrectSubobjects.size()<<" ."<< endl;
					iReturn++;
				}else{
					if ( liSubobjects != liCorrectSubobjects ){
						cerr<<"Error: The Fib element is a branch element, "<<
							"it returns the wrong subobjects."<< endl;
						iReturn++;
					}
				}
				const list< cFibElement * > liSubobjectsConst =
					pConstFibElement->getSubobjects();
				if ( liSubobjectsConst.size() != liCorrectSubobjects.size() ){
					cerr<<"Error: The Fib element is a branch element, it returns "<<
						liSubobjectsConst.size()<<" subobjects (const) and not correctly "<<
						liCorrectSubobjects.size()<<" ."<< endl;
					iReturn++;
				}else{
					if ( liSubobjectsConst != liCorrectSubobjects ){
						cerr<<"Error: The Fib element is a branch element, "<<
							"it returns the wrong subobjects (const)."<< endl;
						iReturn++;
					}
				}
				
				//test getSubobject(): check values outside borders (not existing subobjects)
				if ( pActualFibElement->getSubobject( 0 ) != NULL ){
					cerr<<"Error: The Fib element is a branch element, but returns a 0'th "<<
						pActualFibElement->getSubobject( 0 )<<" subobject "<<
						"( pActualFibElement->getSubobject( 0 ) ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( 0 ) != NULL ){
					cerr<<"Error: The Fib element is a branch element, but returns a 0'th "<<
						pConstFibElement->getSubobject( 0 )<<" subobject (const) "<<
						"( pConstFibElement->getSubobject( 0 ) ) ."<< endl;
					iReturn++;
				}
				const unsignedIntFib uiNotExistingSubobjectNumber =
					liSubobjectsConst.size() + 1;
				if ( pActualFibElement->getSubobject( uiNotExistingSubobjectNumber ) != NULL ){
					cerr<<"Error: The Fib element is a branch element, it returns a "<<
						uiNotExistingSubobjectNumber<<"'th "<<
						pActualFibElement->getSubobject( uiNotExistingSubobjectNumber )<<" subobject "<<
						"( pActualFibElement->getSubobject( "<<uiNotExistingSubobjectNumber<<" ) ) ."<< endl;
					iReturn++;
				}
				if ( pConstFibElement->getSubobject( uiNotExistingSubobjectNumber ) != NULL ){
					cerr<<"Error: The Fib element is a branch element, it returns a "<<
						uiNotExistingSubobjectNumber<<"'th "<<
						pConstFibElement->getSubobject( uiNotExistingSubobjectNumber )<<" subobject (const) "<<
						"( pConstFibElement->getSubobject( "<<uiNotExistingSubobjectNumber<<" ) ) ."<< endl;
					iReturn++;
				}
				if ( liSubobjectsConst.empty() ){
					//no subobjects exists
					if ( pActualFibElement->getSubobject() != NULL ){
						cerr<<"Error: The Fib element is a branch element, it returns default a "<<
							pActualFibElement->getSubobject()<<
							" subobject, but should return NULL "<<
							"( pActualFibElement->getSubobject() ) ."<< endl;
						iReturn++;
					}
					if ( pConstFibElement->getSubobject() != NULL ){
						cerr<<"Error: The Fib element is a branch element, it returns default a "<<
							pConstFibElement->getSubobject()<<
							" subobject (const), but should return NULL "<<
							"( pConstFibElement->getSubobject() ) ."<< endl;
						iReturn++;
					}
				}else{//subobjects exists
					if ( pActualFibElement->getSubobject() != liSubobjectsConst.front() ){
						cerr<<"Error: The Fib element is a branch element, it returns "<<
							pActualFibElement->getSubobject()<<" as its default subobject and not "<<
							liSubobjectsConst.front()<<" ( pActualFibElement->getSubobject() )."<< endl;
						iReturn++;
					}
					if ( pConstFibElement->getSubobject() != liSubobjectsConst.front() ){
						cerr<<"Error: The Fib element is a branch element, it returns "<<
							pConstFibElement->getSubobject()<<" as its default subobject (const) and not "<<
							liSubobjectsConst.front()<<" ( pConstFibElement->getSubobject() )."<< endl;
						iReturn++;
					}
				}
				//test getSubobject(): check existing subobjects
				unsignedIntFib uiActualSubobject = 1;
				for ( list< cFibElement * >::const_iterator
						itrSubobject = liCorrectSubobjects.begin();
						itrSubobject != liCorrectSubobjects.end();
						itrSubobject++, uiActualSubobject++ ){
					
					if ( pActualFibElement->getSubobject( uiActualSubobject ) != (*itrSubobject) ){
						cerr<<"Error: The Fib element is a branch element, it returns "<<
							pActualFibElement->getSubobject( uiActualSubobject )<<" as its first subobject and not "<<
							(*itrSubobject)<<" ( pActualFibElement->getSubobject( "<<uiActualSubobject<<" ) )."<< endl;
						iReturn++;
					}
					if ( pConstFibElement->getSubobject( uiActualSubobject ) != (*itrSubobject) ){
						cerr<<"Error: The Fib element is a branch element, it returns "<<
							pConstFibElement->getSubobject( uiActualSubobject )<<" as its first subobject (const) and not "<<
							(*itrSubobject)<<" ( pConstFibElement->getSubobject( "<<uiActualSubobject<<" ) )."<< endl;
						iReturn++;
					}
				}//end for all correct subobjects
			}//end if check Fib element structure type
		}//end check subobjects
		
		
		{//check getSuperiorRootElement()
			//get the correct superior root element
			cRoot * pCorrectSuperiorRoot = NULL;
			for ( cFibElement * pActualSuperiorElement =
						pActualFibElement->getSuperiorFibElement();
					pActualSuperiorElement != NULL;
					pActualSuperiorElement = pActualSuperiorElement->getSuperiorFibElement() ){
				
				if ( pActualSuperiorElement->getType() == 'r' ){
					//next superior root element found
					pCorrectSuperiorRoot = ((cRoot *)pActualSuperiorElement);
					break;//done
				}
			}
			if ( pActualFibElement->getSuperiorRootElement() != pCorrectSuperiorRoot ){
				cerr<<"Error: The next superior root element should be "<<
					pCorrectSuperiorRoot<<", but is "<<
					pActualFibElement->getSuperiorRootElement()<<"."<<endl;
				iReturn++;
			}
			const cFibElement * pConstFibElement = pActualFibElement;
			if ( pConstFibElement->getSuperiorRootElement() != pCorrectSuperiorRoot ){
				cerr<<"Error: The next const superior root element should be "<<
					pCorrectSuperiorRoot<<", but is "<<
					pConstFibElement->getSuperiorRootElement()<<"."<<endl;
				iReturn++;
			}
		}//end check getSuperiorRootElement()
		
	}//end for check all Fib elements of Fib object
	
	//check if the number of all values are reached
	if ( uiNumberOfAllFibElements != uiNumberOfActualFibElement ){
		cerr<<"Error: Ther are different values for number of all Fib elements "<<
			"given back ("<< uiNumberOfAllFibElements <<") and counted ("<<
			uiNumberOfActualFibElement <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllRootElements != uiNumberOfLastRoot ){
		cerr<<"Error: Ther are different values for number of all root-elements given "<<
			"given back ("<< uiNumberOfAllRootElements <<") and counted ("<<
			uiNumberOfLastRoot <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllPointElements != uiNumberOfLastPoint ){
		cerr<<"Error: Ther are different values for number of all point elements given "<<
			"given back ("<< uiNumberOfAllPointElements <<") and counted ("<<
			uiNumberOfLastPoint <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllPropertyElements != uiNumberOfLastProperty ){
		cerr<<"Error: Ther are different values for number of all property elements given "<<
			"given back ("<< uiNumberOfAllPropertyElements <<") and counted ("<<
			uiNumberOfLastProperty <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllAreaElements != uiNumberOfLastArea ){
		cerr<<"Error: Ther are different values for number of all area elements given "<<
			"given back ("<< uiNumberOfAllAreaElements <<") and counted ("<<
			uiNumberOfLastArea <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllFunctionElements != uiNumberOfLastFunction ){
		cerr<<"Error: Ther are different values for number of all function elements given "<<
			"given back ("<< uiNumberOfAllFunctionElements <<") and counted ("<<
			uiNumberOfLastFunction <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllIfElements != uiNumberOfLastIf ){
		cerr<<"Error: Ther are different values for number of all if-elements given "<<
			"given back ("<< uiNumberOfAllIfElements <<") and counted ("<<
			uiNumberOfLastIf <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllCommentElements != uiNumberOfLastComment ){
		cerr<<"Error: Ther are different values for number of all comment elements given "<<
			"given back ("<< uiNumberOfAllCommentElements <<") and counted ("<<
			uiNumberOfLastComment <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllListElements != uiNumberOfLastList ){
		cerr<<"Error: Ther are different values for number of all list elements given "<<
			"given back ("<< uiNumberOfAllListElements <<") and counted ("<<
			uiNumberOfLastList <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllExtObjectElements != uiNumberOfLastExtObject ){
		cerr<<"Error: Ther are different values for number of all external object elements given "<<
			"given back ("<< uiNumberOfAllExtObjectElements <<") and counted ("<<
			uiNumberOfLastExtObject <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllExtSubobjectElements != uiNumberOfLastExtSubobject ){
		cerr<<"Error: Ther are different values for number of all external subobject elements given "<<
			"given back ("<< uiNumberOfAllExtSubobjectElements <<") and counted ("<<
			uiNumberOfLastExtSubobject <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllSetElements != uiNumberOfLastSet ){
		cerr<<"Error: Ther are different values for number of all set elements given "<<
			"given back ("<< uiNumberOfAllSetElements <<") and counted ("<<
			uiNumberOfLastSet <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllMatrixElements != uiNumberOfLastMatrix ){
		cerr<<"Error: Ther are different values for number of all matrix elements given "<<
			"given back ("<< uiNumberOfAllMatrixElements <<") and counted ("<<
			uiNumberOfLastMatrix <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllMovePoints != uiNumberOfLastMovePoint ){
		cerr<<"Error: Ther are different values for the number of all movepoints "<<
			"given back ("<< uiNumberOfAllMovePoints <<") and counted ("<<
			uiNumberOfLastMovePoint <<")."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAllObjectPoints != uiNumberOfLastObjectPoint ){
		cerr<<"Error: Ther are different values for the number of all objectpoints "<<
			"given back ("<< uiNumberOfAllObjectPoints <<") and counted ("<<
			uiNumberOfLastObjectPoint <<")."<<endl;
		iReturn++;
	}


	/*check getFibElement( lNumber ) for (lNumber < 0);
	choos a random first Fib elements, get a random second Fib element
	relativ to the first with ( 0 < lNumber), then try to get the first
	Fib element from the second with (lNumber * -1) */
	
	for ( unsigned int uiActualAbsolutFibElement = 0;
			uiActualAbsolutFibElement <= uiNumberOfAllFibElements / 50 + 10;
			uiActualAbsolutFibElement++ ){
		
		cFibElement * pStartingPoint = pFibObject->getFibElement(
			rand() % uiNumberOfAllFibElements + 1 );
		if ( pStartingPoint == NULL ){
			continue;
		}
		long lDistance = rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pEndingPoint = pStartingPoint->getFibElement( lDistance );
		if ( pEndingPoint == NULL ){
			continue;
		}
		cFibElement * pStartingPointRevers = pEndingPoint->getFibElement(
			lDistance * -1 + 1 );
		if ( pStartingPointRevers == NULL ){
			cerr<<"Error: Traveling from the startingpoint Fib element ("<<
				pStartingPoint->getNumberOfElement() <<") to the endpoint ("<<
				pEndingPoint->getNumberOfElement() <<") the distance "<<
				lDistance <<" and back from the endpoint the distance "<<
				(lDistance * -1 + 1) <<" dosn't ends at the startingpoint, but on the "<<
				" the NULL -pointer."<<endl;
			iReturn++;
			continue;
		}
		if ( pStartingPoint != pStartingPointRevers ){
			cerr<<"Error: Traveling from the startingpoint Fib element ("<<
				pStartingPoint->getNumberOfElement() <<") to the endpoint ("<<
				pEndingPoint->getNumberOfElement() <<") the distance "<<
				lDistance <<" and back from the endpoint the distance "<<
				(lDistance * -1 + 1) <<" dosn't ends at the startingpoint, but on the "<<
				pStartingPointRevers->getNumberOfElement()<<"'th Fib element."<<endl;
			iReturn++;
		}
	}
	/*check getFibElement( lNumber ) for (lNumber < 0) for a choosen type;*/
	for ( unsigned int uiActualType = 0; uiActualType <= 12; uiActualType++ ){
		char cActualType = 'u';
		string szNameActualType( "unknown" );
		unsigned int uiNumberOfElementsOfActualType = 0;
		switch ( uiActualType ){
			case 1:{
				cActualType = 'r';
				szNameActualType = "root";
				uiNumberOfElementsOfActualType = uiNumberOfAllRootElements;
			}break;
			case 2:{
				cActualType = 'p';
				szNameActualType = "point";
				uiNumberOfElementsOfActualType = uiNumberOfAllPointElements;
			}break;
			case 3:{
				cActualType = 'y';
				szNameActualType = "property";
				uiNumberOfElementsOfActualType = uiNumberOfAllPropertyElements;
			}break;
			case 4:{
				cActualType = 'l';
				szNameActualType = "list";
				uiNumberOfElementsOfActualType = uiNumberOfAllListElements;
			}break;
			case 5:{
				cActualType = 'a';
				szNameActualType = "area";
				uiNumberOfElementsOfActualType = uiNumberOfAllAreaElements;
			}break;
			case 6:{
				cActualType = 'f';
				szNameActualType = "function";
				uiNumberOfElementsOfActualType = uiNumberOfAllFunctionElements;
			}break;
			case 7:{
				cActualType = 'i';
				szNameActualType = "if";
				uiNumberOfElementsOfActualType = uiNumberOfAllIfElements;
			}break;
			case 8:{
				cActualType = 'c';
				szNameActualType = "comment";
				uiNumberOfElementsOfActualType = uiNumberOfAllCommentElements;
			}break;
			case 9:{
				cActualType = 'o';
				szNameActualType = "external object";
				uiNumberOfElementsOfActualType = uiNumberOfAllExtObjectElements;
			}break;
			case 10:{
				cActualType = 's';
				szNameActualType = "external subobject";
				uiNumberOfElementsOfActualType = uiNumberOfAllExtSubobjectElements;
			}break;
			case 11:{
				cActualType = 'v';
				szNameActualType = "set-element";
				uiNumberOfElementsOfActualType = uiNumberOfAllSetElements;
			}break;
			case 12:{
				cActualType = 'm';
				szNameActualType = "matirx";
				uiNumberOfElementsOfActualType = uiNumberOfAllMatrixElements;
			}break;
		}
		if ( uiNumberOfElementsOfActualType == 0 ){
			//skip type
			continue;
		}
		/*choos a random first Fib elements, get a random second Fib element
		relativ to the first with ( 0 < lNumber), count the Fib elements of the type betwean and
		try to get the first Fib element from the second with the counted number */
		for ( unsigned int uiActualAbsolutFibElement = 0;
				uiActualAbsolutFibElement <= uiNumberOfElementsOfActualType / 50 + 10;
				uiActualAbsolutFibElement++ ){
			
			cFibElement * pStartingPoint = pFibObject->getFibElement(
				cActualType, rand() % uiNumberOfElementsOfActualType + 1 );
			if ( pStartingPoint == NULL ){
				continue;
			}
			long lDistance = rand() % uiNumberOfAllFibElements + 1;
			long lElementsOfTypeBetwean = 0;
			cFibElement * pEndingPoint = pStartingPoint;
			
			for ( long lActualDistance = 0;
				(lActualDistance <= lDistance) && ( pEndingPoint != NULL );
				lActualDistance++, pEndingPoint = pEndingPoint->getNextFibElement() ){
				
				if ( pEndingPoint->getType() == cActualType ){
					lElementsOfTypeBetwean++;
				}
			}
			if ( pEndingPoint == NULL ){
				continue;
			}
			cFibElement * pStartingPointRevers = pEndingPoint->getFibElement(
				cActualType, lElementsOfTypeBetwean * -1 );
			
			if ( pStartingPointRevers == NULL ){
				cerr<<"Error: Traveling from the startingpoint "<<
					szNameActualType <<"element (Fib elementnumber="<<
					pStartingPoint->getNumberOfElement() <<") to the endpoint ("<<
					pEndingPoint->getNumberOfElement() <<") the distance "<<
					lDistance <<" and back "<<
					"from the endpoint the distance "<< lElementsOfTypeBetwean <<
					" over "<<szNameActualType <<"elements dosn't ends at the "<<
					"startingpoint, but on the NULL -pointer."<<endl;
				iReturn++;
				continue;
			}
			if ( pStartingPoint != pStartingPointRevers ){
				cerr<<"Error: Traveling from the startingpoint "<<
					szNameActualType <<"element (Fib elementnumber="<<
					pStartingPoint->getNumberOfElement() <<") to the endpoint ("<<
					pEndingPoint->getNumberOfElement() <<") the distance "<<
					lDistance <<" over "<<szNameActualType <<"elements and back "<<
					"from the endpoint the distance "<< lElementsOfTypeBetwean <<
					" over "<<szNameActualType <<"elements dosn't ends at the "<<
					"startingpoint, but on the "<< pStartingPointRevers->getNumberOfElement() <<
					"'th Fib element."<<endl;
				iReturn++;
			}
		}
	}

	return iReturn;
}


/**
 * This function tests the methods for getting the number of, special or
 * not, Fib elements or points of a Fib object in a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- unsignedIntFib getNumberOfElements( char cType='u' ) const;
 * 	- unsignedIntFib getNumberOfMovePoints() const;
 * 	- unsignedIntFib getNumberOfObjectPoints() const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testGetNumberOfCountOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	
	/*choos a random Fib element; get the count values for it and check,
	with help of getSuperiorFibElement() of the last Fib element for each
	the counts, if the choosen Fib element is a superior and Fib elements,
	for the increased with one count, hasn't the choosen Fib element as
	it's superior*/
	for ( unsigned int uiActualIteration = 1;
			uiActualIteration <= uiNumberOfAllFibElements / 100 + 5;
			uiActualIteration++ ){
		//choos random Fib element
		const unsigned int uiNumberOfChoosenFibElement =
			rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pChoosenNumberFibElement =
			pFibObject->getFibElement( uiNumberOfChoosenFibElement );
		
		long lCountFibElements = pChoosenNumberFibElement->getNumberOfElements();
		cFibElement * pLastFibElementInObject =
			pChoosenNumberFibElement->getFibElement( lCountFibElements );
		/*check if the Fib element next to pLastFibElementInObject isn't in
		the choosen Fib object*/
		cFibElement * pNextToLastFibElementInObject =
			pLastFibElementInObject->getNextFibElement();
		for ( cFibElement * pActualElement = pNextToLastFibElementInObject;
				pActualElement != NULL;
				pActualElement = pActualElement->getSuperiorFibElement() ){
			
			if ( pActualElement == pChoosenNumberFibElement ){
				
				cerr<<"Error: The actual Fib element (number="<<
					pNextToLastFibElementInObject->getNumberOfElement() <<
					") shouldn't be in the subobject of the choosen Fib element "<<
					pChoosenNumberFibElement->getNumberOfElement() <<" , but it is."<<endl;
				iReturn++;
				break;
			}
		}
		
		long lCountRoots = pChoosenNumberFibElement->getNumberOfElements('r');
		long lCountPoints = pChoosenNumberFibElement->getNumberOfElements('p');
		long lCountProperties = pChoosenNumberFibElement->getNumberOfElements('y');
		long lCountAreas = pChoosenNumberFibElement->getNumberOfElements('a');
		long lCountFunctions  = pChoosenNumberFibElement->getNumberOfElements('f');
		long lCountIfs  = pChoosenNumberFibElement->getNumberOfElements('i');
		long lCountComments   = pChoosenNumberFibElement->getNumberOfElements('c');
		long lCountLists = pChoosenNumberFibElement->getNumberOfElements('l');
		long lCountExtObjects = pChoosenNumberFibElement->getNumberOfElements('o');
		long lCountExtSubobjects = pChoosenNumberFibElement->getNumberOfElements('s');
		long lCountSet = pChoosenNumberFibElement->getNumberOfElements('v');
		long lCountMatrix = pChoosenNumberFibElement->getNumberOfElements('m');
		
		long lCountMovePoints = pChoosenNumberFibElement->
			getNumberOfMovePoints();
		
		const unsignedIntFib uiCountObjectPoints = pChoosenNumberFibElement->
			getNumberOfObjectPoints();
		unsignedIntFib uiElementPointOfObjectPoint = 0;
		if ( ((unsignedIntFib)(0)) < uiCountObjectPoints ){
			uiElementPointOfObjectPoint = pChoosenNumberFibElement->
				objectPointToElementPoint( uiCountObjectPoints );
			if ( lCountFibElements < (longFib)uiElementPointOfObjectPoint ){
				cerr<<"Error: The objectpoint "<< uiCountObjectPoints <<
					" ,which is the "<< uiElementPointOfObjectPoint <<"'th Fib element, "<<
					" is not in the subobject of the choosen Fib element "<<
					pChoosenNumberFibElement->getNumberOfElement() <<" ."<<endl;
				iReturn++;
			}
		}
		
		const unsignedIntFib uiElementPointOfNextObjectPoint = pChoosenNumberFibElement->
			objectPointToElementPoint( uiCountObjectPoints + 1 );
		if ( ( ((unsignedIntFib)(1)) <= uiElementPointOfNextObjectPoint) &&
				(uiElementPointOfNextObjectPoint <= (unsignedIntFib)lCountFibElements) ){
			cerr<<"Error: The objectpoint (for Fib element="<<
				uiElementPointOfNextObjectPoint <<") next to the objectpoint "<<
				uiCountObjectPoints <<" , which is the "<< uiElementPointOfObjectPoint
				<<"'th Fib element, is in the subobject of the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<" ."<<endl;
			iReturn++;
		}

		cFibElement * pActualElement;
		for ( pActualElement = pLastFibElementInObject;
				pActualElement != NULL;
				pActualElement = pActualElement->getFibElement( -1 ) ){
			
			lCountFibElements--;
			
			const char cActualType = pActualElement->getType();
			
			switch ( cActualType ){
				case 'r':
					lCountRoots--;
				break;
				case 'p':
					lCountPoints--;
				break;
				case 'y':
					lCountProperties--;
					lCountMovePoints--;
				break;
				case 'a':
					lCountAreas--;
					lCountMovePoints--;
				break;
				case 'f':
					lCountFunctions--;
					lCountMovePoints--;
				break;
				case 'c':
					lCountComments--;
					lCountMovePoints--;
				break;
				case 'i':
					lCountIfs--;
				break;
				case 'l':
					lCountLists--;
				break;
				case 'o':
					lCountExtObjects--;
				break;
				case 's':
					lCountExtSubobjects--;
				break;
				case 'v':
					lCountSet--;
					lCountMovePoints--;
				break;
				case 'm':
					lCountMatrix--;
					lCountMovePoints--;
				break;
			}
			//stop when actual Fib element is reached
			if ( pActualElement == pChoosenNumberFibElement ){
				break;
			}
		}
		if (pActualElement == NULL){
			cerr<<"Error: While checking previos Fib elements of the "<<
				"Fib element, which should be the last in the subobject "<<
				"to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				", the choosen Fib element wasn't reached."<<endl;
			iReturn++;
		}
		if ( lCountFibElements != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountFibElements <<" Fib elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountMovePoints != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountMovePoints <<" movepoints counted to much."<<endl;
			iReturn++;
		}
		if ( lCountRoots != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountRoots <<" root-elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountPoints != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountPoints <<" point elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountProperties != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountProperties <<" property elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountAreas != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountAreas <<" area elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountFunctions != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountFunctions <<" function elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountIfs != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountIfs <<" if-elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountComments != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountComments <<" comment elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountLists != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountLists <<" list elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountExtObjects != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountExtObjects <<" external object elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountExtSubobjects != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountExtSubobjects <<" external subobject elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountSet != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountSet <<" set elements counted to much."<<endl;
			iReturn++;
		}
		if ( lCountMatrix != 0 ){
			cerr<<"Error: In the subobject to the choosen Fib element "<<
				pChoosenNumberFibElement->getNumberOfElement() <<
				" ther wher "<< lCountMatrix <<" matrix elements counted to much."<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}


/**
 * This method checked if the given list of Fib elements is a tree of
 * the given type with the pRootElement as the highest Fib element.
 * This means:
 * 	- all Fib elements in the given list are of the given type
 * 	- ther is no duplicate Fib element in the list
 * 	- all Fib elements from the list have the given pRootElement as
 * 	ther superior Fib element
 * 	- ther is no Fib element of the given type betwean two
 * 	Fib elements in the given list which is not in the list
 * 	- if given: every Fib element as the central node as it's superior
 * 	or is a superior of it
 *
 * @param liClusterElements a list with the Fib elements wich should form
 * 	the tree
 * @param cType the type of Fib elements the tree should consits of;
 * 	just Fib elements of the given type should be in the list;
 * 	every Fib element of the type betwean two Fib elements in the list
 * 	is also in the list
 * @param pRootElement the root-element which is a direct or indirect
 * 	superior Fib element of all Fib elements in the given list;
 * 	if NULL is given the Fib elements of the list have one Fib element
 * 	as ther superior, which is highest Fib element in the list
 * @param pCentralNode a central node of the Fib element
 * @param bRootInTree if the root element has the correct type cType, it
 * 	should be in the tree liClusterElements
 * @return the number of erros occured in the test
 */
int checkIsConnectedTypeTree( list<cFibElement*> liClusterElements,
		 char cType = 'u', cFibElement * pRootElement = NULL,
		 cFibElement * pCentralNode = NULL, bool bRootInTree = true ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( liClusterElements.empty() ){
		//no Fib elements could be wrong
		return iReturn;
	}
	
 	//check if all Fib elements in the given list are of the given type
	if ( cType != 'u'){
		for ( list< cFibElement * >::iterator
				itrActualFibElement = liClusterElements.begin();
				itrActualFibElement != liClusterElements.end();
				itrActualFibElement++ ){
			
			if ( (*itrActualFibElement)->getType() != cType ){
				cerr<<"Error: The type of the "<<
					(*itrActualFibElement)->getNumberOfElement()<<
					"'th Fib element in the given tree is not of the selected type "<<
					cType <<", but has the type "<< (*itrActualFibElement)->getType() <<" ."<<endl;
				iReturn++;
			}
		}
	}
	
	set<cFibElement*> setClusterElements( liClusterElements.begin(),
		liClusterElements.end() );
	
	//check if ther is no duplicate Fib element in the list
	if ( setClusterElements.size() != liClusterElements.size() ){
		cerr<<"Error: Ther are duplicate Fib elements in the Fib elementtree"<<
			" of type "<< cType <<" ."<<endl;
		iReturn++;
	}
	if ( pRootElement == NULL ){
		//if no pRootElement is given choose one
		pRootElement = liClusterElements.front();
		
		for ( cFibElement * pActualFibElement = pRootElement;
				pActualFibElement != NULL;
				pActualFibElement = pActualFibElement->getSuperiorFibElement() ){
			
			//if the superiorelement is in the given list choose it
			set<cFibElement*>::iterator itrFoundedElement = find(
				setClusterElements.begin(), setClusterElements.end(),
				pActualFibElement );
			
			if ( itrFoundedElement != setClusterElements.end() ){
				//element found in the tree
				pRootElement = pActualFibElement;
			}
		}
	}
	if ( bRootInTree ){
		//check root-element
		if ( (cType == 'u') || (pRootElement->getType() == cType) ){
			//if the superiorelement is in the given list choose it
			set<cFibElement*>::iterator itrFoundedElement = find(
				setClusterElements.begin(), setClusterElements.end(),
				pRootElement );
			
			if ( itrFoundedElement == setClusterElements.end() ){
				//root-element not found in the tree
				cerr<<"Error: The root-element with number "<<
					pRootElement->getNumberOfElement() <<
					" has the correct type "<< cType <<", but isn't in the tree."<<endl;
				iReturn++;
			}
		}
	}
	
	if ( (pCentralNode != NULL) && ( pCentralNode != pRootElement ) ){
		/*remove all Fib elements from the tree list which are superiors
		of the central node, because ther are in the tree and take the
		central root as the new root-element*/
		
		//take the central node as the root-element if it is higher
		for ( cFibElement * pActualFibElement = pRootElement;
				pActualFibElement->getSuperiorFibElement() != NULL;
				pActualFibElement = pActualFibElement->getSuperiorFibElement() ){
			
			if ( pCentralNode == pActualFibElement ){
				//element found in the tree
				pRootElement = pCentralNode;
				break;
			}
		}
		if ( pCentralNode != pRootElement ){
	
			for ( cFibElement * pActualSuperiorElement = pCentralNode;
					pActualSuperiorElement != NULL;
					pActualSuperiorElement = pActualSuperiorElement->getSuperiorFibElement() ){
				
				if ( ( ! bRootInTree ) && (pActualSuperiorElement == pRootElement) ){
					//all Fib elements bewean central node and root-element(exclusive) found
					
					set<cFibElement*>::iterator itrFoundedElement = find(
						setClusterElements.begin(), setClusterElements.end(),
						pActualSuperiorElement );
					if ( itrFoundedElement == setClusterElements.end() ){
						//if the root-element isn't in the tree -> don't check it
						break;
					}//if the root-element is in the tree -> check it
				}
				
				//if the superior is of the correct type it should be in the given tree
				if ( (cType == 'u') || (pActualSuperiorElement->getType() == cType) ){
					
					//if the superiorelement is in the given list choose it
					set<cFibElement*>::iterator itrFoundedElement = find(
						setClusterElements.begin(), setClusterElements.end(),
						pActualSuperiorElement );
					
					if ( itrFoundedElement != setClusterElements.end() ){
						//element found in the tree
						//cycle check: check if the found superior is higher the the source Fib element
						if ( pCentralNode->getNumberOfElement() <
								pActualSuperiorElement->getNumberOfElement() ){
							cerr<<"Error: The superior Fib element with number "<<
								pActualSuperiorElement->getNumberOfElement() <<
								" of the central node Fib element with number "<<
								pCentralNode->getNumberOfElement()<<" has higher number."<<endl;
							iReturn++;
						}
						//this Fib element is Ok -> don't check it later
						setClusterElements.erase( itrFoundedElement );
						
						list<cFibElement*>::iterator itrLiFoundedElement = find(
							liClusterElements.begin(), liClusterElements.end(),
							pActualSuperiorElement );
						if ( itrLiFoundedElement != liClusterElements.end() ){
							liClusterElements.erase( itrLiFoundedElement );
						}
					}else{
						//element not found in the tree
						cerr<<"Error: The superior Fib element with number "<<
							pActualSuperiorElement->getNumberOfElement() <<
							" of the central node Fib element with number "<<
							pCentralNode->getNumberOfElement()<<
							" has the correct type "<< cType <<", but isn't in the tree."<<endl;
						iReturn++;
					}
				}
				if ( pActualSuperiorElement == pRootElement ){
					//all Fib elements bewean central node and root-element(inclusive) found
					break;
				}

			}
			pRootElement = pCentralNode;
		}//else the central node is the highest root->nothing to check hear

	}
	
	/*check if all Fib elements from the list have the given pRootElement
	as ther superior Fib element and ther is no Fib element of the given
	type betwean two Fib elements in the given list which is not in the list*/
	for (list< cFibElement * >::iterator
			itrActualFibElement = liClusterElements.begin();
			itrActualFibElement != liClusterElements.end();
			itrActualFibElement++ ){
		
		if ( (*itrActualFibElement) == pRootElement ){
			continue;
		}
		cFibElement * pActualSuperiorElement;
		for ( pActualSuperiorElement = (*itrActualFibElement)->getSuperiorFibElement();
				pActualSuperiorElement != NULL;
				pActualSuperiorElement = pActualSuperiorElement->getSuperiorFibElement() ){
			
			/*if the superior Fib element is tht root-element the
			itrActualFibElement is in the tree -> check next tree Fib element*/
			if ( pActualSuperiorElement == pRootElement ){
				break;
			}
			
			//if the superior is of the correct type it should be in the given tree
			if ( (cType == 'u') || (pActualSuperiorElement->getType() == cType) ){
				
				//if the superiorelement is in the given list choose it
				set<cFibElement*>::iterator itrFoundedElement = find(
					setClusterElements.begin(), setClusterElements.end(),
					pActualSuperiorElement );
				
				if ( itrFoundedElement != setClusterElements.end() ){
					//element found in the tree
					//cycle check: check if the found superior is higher the the source Fib element
					if ( (*itrActualFibElement)->getNumberOfElement() <=
							pActualSuperiorElement->getNumberOfElement() ){
						cerr<<"Error: The superior Fib element with number "<<
							pActualSuperiorElement->getNumberOfElement() <<
							" of the Fib element with number "<<
							(*itrActualFibElement)->getNumberOfElement()<<" has higher number."<<endl;
						iReturn++;
					}
					break;
				}else{
					//element not found in the tree
					cerr<<"Error: The superior Fib element with number "<<
						pActualSuperiorElement->getNumberOfElement() <<
						" of the Fib element with number "<<
						(*itrActualFibElement)->getNumberOfElement()<<
						" has the correct type "<< cType <<", but isn't in the tree."<<endl;
					iReturn++;
				}
			}
		}
		if ( pActualSuperiorElement == NULL ){
			if ( pCentralNode == NULL){
				cerr<<"Error: The Fib element with number "<<
					(*itrActualFibElement)->getNumberOfElement()<<
					" should be in the tree, but hasn't the common root."<<endl;
				iReturn++;
			}else{
				cerr<<"Error: The Fib element with number "<<
					(*itrActualFibElement)->getNumberOfElement()<<
					" should be in the tree, but hasn't the central node as it's superior."<<endl;
				iReturn++;
			}
		}
	}
	
	return iReturn;
}


/**
 * This function tests the method getAllFibElements() on a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- list<cFibElement*> getAllFibElements( char cTypeBasis='u', longFib lNumber=1, char cType='u', edDirection direction=ED_ALL, unsignedLongFib lNumberOfMaxReturnedElements=0, bool bAbsolute=false )
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testGetAllFibElementsOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	cout<<"Checking getAllFibElements()"<<endl;

	/*choos some random Fib elements in the Fib object and test
	getAllFibElements() from ther for the different directions;
	all with getAllFibElements() found Fib elements needed to have one
	common superior, if the direction is ED_BELOW or ED_BELOW_EQUAL the
	common superior is the choosen Fib element;
	check if not to much or few Fib elements wher found;
	for the type selected: betwean all Fib elements and the common
	superior all Fib elements of the selected type are given back;
	if the lNumberOfMaxReturnedElements isn't reached: all Fib elements of
	the selected type, in the choosen direction are given back
	*/
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
		
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );

	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 100 + 20) ; uiIteration++){
		
		//choos a random calling Fib element
		char cTypeCallingElement = choosRandomType();
		unsigned int uiNumberOfElementsOfType = 0;
		switch ( cTypeCallingElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		if ( uiNumberOfElementsOfType == 0 ){
			//skip
			continue;
		}
		const unsigned int uiCallingFibElement = rand() % uiNumberOfElementsOfType + 1;
		cFibElement * pCallingFibElement = pFibObject->getFibElement(
			 cTypeCallingElement, uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element with the type "<< cTypeCallingElement <<
				"of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		switch ( cTypeBasisElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}

		long lBasisFibElement = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			lBasisFibElement = rand() % uiNumberOfElementsOfType;
		}
		cFibElement * pBasisFibElement = pFibObject->getFibElement(
			 cTypeBasisElement, lBasisFibElement );
		//check the getType() methode from cList
		if ( pBasisFibElement == NULL ){
			cerr<<"Error: The "<< lBasisFibElement <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			continue;
		}
		if ( lBasisFibElement != 0 ){
			if( cTypeBasisElement != 'u' ){
				if ( pBasisFibElement->getNumberOfElement() <
						pCallingFibElement->getNumberOfElement() ){
					/*count from previos Fib element from calling element as same type as basis*/
					lBasisFibElement -= pCallingFibElement->getFibElement(
						cTypeBasisElement, -1 )->getNumberOfElement( true );
					lBasisFibElement--;
				}else{
					/*count from next Fib element from calling element as same type as basis*/
					lBasisFibElement -= pCallingFibElement->getFibElement(
						cTypeBasisElement, 1 )->getNumberOfElement( true );
					lBasisFibElement++;
				}
			}else{//cTypeBasisElement == 'u'
				lBasisFibElement -= pCallingFibElement->getNumberOfElement();
				if ( 0 <= lBasisFibElement ){
					lBasisFibElement++;
				}
			}
		}
		if ( lBasisFibElement == 0 ){
			//the basis and calling Fib element is the same
			pBasisFibElement = pCallingFibElement;
		}

		char cTypeOfToReturnElements = choosRandomType();

	//*** get all
	//**check direction ED_POSITION
		list<cFibElement*> liAllPositionFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_POSITION );
		if ( (cTypeOfToReturnElements != 'u') && (pBasisFibElement->getType() != cTypeOfToReturnElements) ){
			if ( liAllPositionFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_POSITION ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllPositionFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liAllPositionFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_POSITION ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllPositionFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liAllPositionFibElements.size() != 0 ){
				if ( liAllPositionFibElements.front() != pBasisFibElement ){
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_POSITION ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<< pCallingFibElement->getNumberOfElement()<<
						") returned the wrong Fib element with number "<<
						liAllPositionFibElements.front()->getNumberOfElement() <<" and not with number "<<
						pBasisFibElement->getNumberOfElement() <<" ."<<endl;
					iReturn++;
				}
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_POSITION ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}

	//**check direction ED_HIGHER
		list<cFibElement*> liAllHigherFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_HIGHER );
		
		//check the number of returned Fib elements
		unsigned int uiNumberOfElementsHigher = 0;
		//count higher Fib elements of the type
		for ( cFibElement * pActualSuperiorElement = pBasisFibElement->getSuperiorFibElement();
				pActualSuperiorElement != NULL;
				pActualSuperiorElement = pActualSuperiorElement->getSuperiorFibElement() ){
			
			if ( (pActualSuperiorElement->getType() == cTypeOfToReturnElements) ||
					(cTypeOfToReturnElements == 'u') ){
				uiNumberOfElementsHigher++;
			}
		}
		if ( uiNumberOfElementsHigher != 0 ){
			if ( liAllHigherFibElements.size() != uiNumberOfElementsHigher ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllHigherFibElements.size() <<" Fib elements and not "<<
					uiNumberOfElementsHigher <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllHigherFibElements.begin();
						itrActualElement != liAllHigherFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liAllHigherFibElements, cTypeOfToReturnElements,
				pFibObject, pBasisFibElement->getSuperiorFibElement(), true );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllHigherFibElements.begin();
						itrActualElement != liAllHigherFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liAllHigherFibElements.empty()){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllHigherFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllHigherFibElements.begin();
						itrActualElement != liAllHigherFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}

	//**check direction ED_HIGHER_EQUAL with the Fib elements from ED_HIGHER and ED_POSITION
		list<cFibElement*> liAllHigherEqualFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
				cTypeOfToReturnElements, ED_HIGHER_EQUAL );
		
		//check the number of returned Fib elements
		unsigned int uiNumberOfElementsHigherEqual = uiNumberOfElementsHigher;
		//count higher Fib elements of the type
		if ( (cTypeOfToReturnElements == 'u') ||
				(pBasisFibElement->getType() == cTypeOfToReturnElements) ){
			uiNumberOfElementsHigherEqual++;
		}
		
		if ( uiNumberOfElementsHigherEqual != 0 ){
			if ( liAllHigherEqualFibElements.size() != uiNumberOfElementsHigherEqual ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllHigherEqualFibElements.size() <<" Fib elements and not "<<
					uiNumberOfElementsHigherEqual <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllHigherEqualFibElements.begin();
						itrActualElement != liAllHigherEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liAllHigherEqualFibElements, cTypeOfToReturnElements,
				pFibObject, pBasisFibElement, true );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllHigherEqualFibElements.begin();
						itrActualElement != liAllHigherEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liAllHigherEqualFibElements.empty() ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllHigherEqualFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllHigherEqualFibElements.begin();
						itrActualElement != liAllHigherEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}

	
	//**check direction ED_BELOW
		list<cFibElement*> liAllBelowFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
				cTypeOfToReturnElements, ED_BELOW );
		
		//check the number of returned Fib elements
		unsigned int uiNumberOfElementsBelowEqual = pBasisFibElement->
			getNumberOfElements( cTypeOfToReturnElements );
			
		unsigned int uiNumberOfElementsBelow = uiNumberOfElementsBelowEqual;
		if ( (pBasisFibElement->getType() == cTypeOfToReturnElements) ||
					(cTypeOfToReturnElements == 'u') ){
			//don't return the basis Fib element
			uiNumberOfElementsBelow--;
		}
		
		if ( uiNumberOfElementsBelow != 0 ){
			if ( liAllBelowFibElements.size() != uiNumberOfElementsBelow ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllBelowFibElements.size() <<" Fib elements and not "<<
					uiNumberOfElementsBelow <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllBelowFibElements.begin();
						itrActualElement != liAllBelowFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liAllBelowFibElements, cTypeOfToReturnElements,
				pBasisFibElement, pBasisFibElement, false );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllBelowFibElements.begin();
						itrActualElement != liAllBelowFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liAllBelowFibElements.empty() ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllBelowFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllBelowFibElements.begin();
						itrActualElement != liAllBelowFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}


	//**check direction ED_BELOW_EQUAL with the Fib elements from ED_BELOW_EQUAL and ED_POSITION
		list<cFibElement*> liAllBelowEqualFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
				cTypeOfToReturnElements, ED_BELOW_EQUAL );
		
		//the uiNumberOfElementsBelowEqual is known from befor
		
		if ( uiNumberOfElementsBelowEqual != 0 ){
			if ( liAllBelowEqualFibElements.size() != uiNumberOfElementsBelowEqual ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllBelowEqualFibElements.size() <<" Fib elements and not "<<
					uiNumberOfElementsBelowEqual <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllBelowEqualFibElements.begin();
						itrActualElement != liAllBelowEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liAllBelowEqualFibElements, cTypeOfToReturnElements,
				pBasisFibElement, pBasisFibElement, true );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllBelowEqualFibElements.begin();
						itrActualElement != liAllBelowEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liAllBelowEqualFibElements.empty() ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllBelowEqualFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllBelowEqualFibElements.begin();
						itrActualElement != liAllBelowEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}

	
	//**check direction ED_ALL
		list<cFibElement*> liAllFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
				cTypeOfToReturnElements, ED_ALL );
		
		//the uiNumberOfElementsAll is known from befor
		unsigned int uiNumberOfElementsAll = uiNumberOfElementsHigherEqual +
			uiNumberOfElementsBelow;
		
		if ( uiNumberOfElementsAll != 0 ){
			if ( liAllFibElements.size() != uiNumberOfElementsAll ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllFibElements.size() <<" Fib elements and not "<<
					uiNumberOfElementsAll <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllFibElements.begin();
						itrActualElement != liAllFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liAllFibElements, cTypeOfToReturnElements,
				pFibObject, pBasisFibElement, true );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllFibElements.begin();
						itrActualElement != liAllFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liAllFibElements.empty() ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liAllFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liAllFibElements.begin();
						itrActualElement != liAllFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}

	
	//*** get one
	//**check direction ED_POSITION
		list<cFibElement*> liOnePositionFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_POSITION, 1 );
		
		if ( (cTypeOfToReturnElements != 'u') && (pBasisFibElement->getType() != cTypeOfToReturnElements) ){
			if ( liOnePositionFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_POSITION, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOnePositionFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liOnePositionFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_POSITION, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOnePositionFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liOnePositionFibElements.size() != 0 ){
				if ( liAllPositionFibElements.front() != pBasisFibElement ){
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_POSITION, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<< pCallingFibElement->getNumberOfElement()<<
						") returned the wrong Fib element with number "<<
						liOnePositionFibElements.front()->getNumberOfElement() <<" and not with number "<<
						pBasisFibElement->getNumberOfElement() <<" ."<<endl;
					iReturn++;
				}
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_POSITION, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}

	
	//**check direction ED_HIGHER
		list<cFibElement*> liOneHigherFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_HIGHER, 1 );
		//search for the next Fib element of cTypeOfToReturnElements type in direction higher
		cFibElement * pNextHigherElement = NULL;
		for ( cFibElement * pActualSuperior = pBasisFibElement->getSuperiorFibElement();
				pActualSuperior != NULL;
				pActualSuperior = pActualSuperior->getSuperiorFibElement() ){
			if ( (cTypeOfToReturnElements == 'u') || (pActualSuperior->getType() == cTypeOfToReturnElements) ){
				pNextHigherElement = pActualSuperior;
				break;
			}
		}
		if ( pNextHigherElement == NULL ){
			//no next higher element of the type cTypeOfToReturnElements
			if ( liOneHigherFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneHigherFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liOneHigherFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneHigherFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liOneHigherFibElements.size() != 0 ){
				if ( liOneHigherFibElements.front() != pNextHigherElement ){
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_HIGHER, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<< pCallingFibElement->getNumberOfElement()<<
						") returned the wrong Fib element with number "<<
						liOneHigherFibElements.front()->getNumberOfElement() <<" and not with number "<<
						pNextHigherElement->getNumberOfElement() <<" ."<<endl;
					iReturn++;
				}
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_HIGHER, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}


	//**check direction ED_HIGHER_EQUAL with the Fib elements from ED_HIGHER and ED_POSITION
		list<cFibElement*> liOneHigherEqualFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_HIGHER_EQUAL, 1 );
		//search for the next Fib element of cTypeOfToReturnElements type in direction higher or on position
		cFibElement * pNextHigherEqualElement = NULL;
		if ( (cTypeOfToReturnElements == 'u') || (pBasisFibElement->getType() == cTypeOfToReturnElements) ){
			pNextHigherEqualElement = pBasisFibElement;
			break;
		}else{
			pNextHigherEqualElement = pNextHigherElement;
		}

		if ( pNextHigherEqualElement == NULL ){
			//no next higher element of the type cTypeOfToReturnElements
			if ( liOneHigherEqualFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneHigherEqualFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liOneHigherEqualFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneHigherEqualFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liOneHigherEqualFibElements.size() != 0 ){
				if ( liOneHigherFibElements.front() != pNextHigherEqualElement ){
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<< pCallingFibElement->getNumberOfElement()<<
						") returned the wrong Fib element with number "<<
						liOneHigherEqualFibElements.front()->getNumberOfElement() <<" and not with number "<<
						pNextHigherEqualElement->getNumberOfElement() <<" ."<<endl;
					iReturn++;
				}
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}

	
	//**check direction ED_BELOW
		list<cFibElement*> liOneBelowFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_BELOW, 1 );

		if ( uiNumberOfElementsBelow == 0 ){
			//no next below element of the type cTypeOfToReturnElements
			if ( liOneBelowFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneBelowFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liOneBelowFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneBelowFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liOneBelowFibElements.size() != 0 ){
				const int iReturnConnectedCheck = checkIsConnectedTypeTree(
					liOneBelowFibElements, cTypeOfToReturnElements,
					pBasisFibElement, pBasisFibElement, false );
				if ( iReturnConnectedCheck != 0 ){
					cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_BELOW, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
						pCallingFibElement->getNumberOfElement()<<") ."<<endl;
					cerr<<"The numbers of the returned Fib elements are: ";
					for ( list<cFibElement*>::iterator itrActualElement =
							liAllBelowFibElements.begin();
							itrActualElement != liAllBelowFibElements.end();
							itrActualElement++ ){
						cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
					}
					cerr<<endl;
				}
				iReturn += iReturnConnectedCheck;
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_BELOW, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}


	//**check direction ED_BELOW_EQUAL with the Fib elements from ED_BELOW and ED_POSITION
		list<cFibElement*> liOneBelowEqualFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_BELOW_EQUAL, 1 );

		if ( uiNumberOfElementsBelowEqual == 0 ){
			//no next below element of the type cTypeOfToReturnElements
			if ( liOneBelowEqualFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneBelowEqualFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liOneBelowEqualFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneBelowEqualFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liOneBelowEqualFibElements.size() != 0 ){
				const int iReturnConnectedCheck = checkIsConnectedTypeTree(
					liOneBelowEqualFibElements, cTypeOfToReturnElements,
					pBasisFibElement, pBasisFibElement, true );
				if ( iReturnConnectedCheck != 0 ){
					cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_BELOW_EQUAL, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
						pCallingFibElement->getNumberOfElement()<<") ."<<endl;
					cerr<<"The numbers of the returned Fib elements are: ";
					for ( list<cFibElement*>::iterator itrActualElement =
							liAllBelowEqualFibElements.begin();
							itrActualElement != liAllBelowEqualFibElements.end();
							itrActualElement++ ){
						cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
					}
					cerr<<endl;
				}
				iReturn += iReturnConnectedCheck;
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_BELOW_EQUAL, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}
		
	
	//**check direction ED_ALL
		list<cFibElement*> liOneAllFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement, cTypeOfToReturnElements, ED_ALL, 1 );

		if ( uiNumberOfElementsAll == 0 ){
			//no next below element of the type cTypeOfToReturnElements
			if ( liOneAllFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneAllFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liOneAllFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL, 1 ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liOneAllFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liOneAllFibElements.size() != 0 ){
				if ( (liOneAllFibElements != liOneBelowEqualFibElements)
						&& (liOneAllFibElements != liOneHigherFibElements) ){
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_ALL, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
						pCallingFibElement->getNumberOfElement()<<") returned "<<
						liOneAllFibElements.size() <<" Fib elements that is "<<
						"not the same Fib element as from belower -equal or higher, but it should."<<endl;
					iReturn++;
				}
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_ALL, 1 ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}
		
	//*** get fixed number
		switch ( cTypeOfToReturnElements ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		unsigned int uiElementsToReturn = 1;
		if ( uiNumberOfElementsOfType != 0 ){
			uiElementsToReturn = rand() % (uiNumberOfElementsOfType + 10) + 1;
		}
	
	//**check direction ED_POSITION
		list<cFibElement*> liNumberPositionFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
			cTypeOfToReturnElements, ED_POSITION, uiElementsToReturn );
		if ( (cTypeOfToReturnElements != 'u') && (pBasisFibElement->getType() != cTypeOfToReturnElements) ){
			if ( liNumberPositionFibElements.size() != 0 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_POSITION, "<<
					uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberPositionFibElements.size() <<" Fib elements and not 0 "<<
					"because ther are no Fib elements of the type."<<endl;
				iReturn++;
			}
		}else{
			if ( liNumberPositionFibElements.size() != 1 ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_POSITION, "<<
					uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberPositionFibElements.size() <<" Fib elements and not 1."<<endl;
				iReturn++;
			}
			if ( liNumberPositionFibElements.size() != 0 ){
				if ( liNumberPositionFibElements.front() != pBasisFibElement ){
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_POSITION, "<<
						uiElementsToReturn<<" ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<< pCallingFibElement->getNumberOfElement()<<
						") returned the wrong Fib element with number "<<
						liNumberPositionFibElements.front()->getNumberOfElement() <<" and not with number "<<
						pBasisFibElement->getNumberOfElement() <<" ."<<endl;
					iReturn++;
				}
			}else{
					cerr<<"Error: While calling getAllFibElements( "<<
						cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
						cTypeOfToReturnElements <<", ED_POSITION, "<<
						uiElementsToReturn<<" ) from the "<<
						uiCallingFibElement <<"'th Fib element with the type "<<
						cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") no Fib elements wher returned ."<<endl;
					iReturn++;
			}
		}
	
	//**check direction ED_HIGHER
		list<cFibElement*> liNumberHigherFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
			cTypeOfToReturnElements, ED_HIGHER, uiElementsToReturn );
		
		if ( uiNumberOfElementsHigher != 0 ){
			if ( liNumberHigherFibElements.size() !=
					std::min( uiNumberOfElementsHigher, uiElementsToReturn ) ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberHigherFibElements.size() <<" Fib elements and not "<<
					std::min( uiNumberOfElementsHigher, uiElementsToReturn ) <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberHigherFibElements.begin();
						itrActualElement != liNumberHigherFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liNumberHigherFibElements, cTypeOfToReturnElements,
				NULL, pBasisFibElement->getSuperiorFibElement() );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberHigherFibElements.begin();
						itrActualElement != liNumberHigherFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liNumberHigherFibElements.empty()){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberHigherFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberHigherFibElements.begin();
						itrActualElement != liNumberHigherFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}


	//**check direction ED_HIGHER_EQUAL with the Fib elements from ED_HIGHER and ED_POSITION
		list<cFibElement*> liNumberHigherEqualFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
			cTypeOfToReturnElements, ED_HIGHER_EQUAL, uiElementsToReturn );
		
		if ( uiNumberOfElementsHigherEqual != 0 ){
			if ( liNumberHigherEqualFibElements.size() !=
					std::min( uiNumberOfElementsHigherEqual, uiElementsToReturn ) ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberHigherEqualFibElements.size() <<" Fib elements and not "<<
					std::min( uiNumberOfElementsHigherEqual, uiElementsToReturn ) <<"."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberHigherEqualFibElements.begin();
						itrActualElement != liNumberHigherEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liNumberHigherEqualFibElements, cTypeOfToReturnElements,
				NULL, pBasisFibElement );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberHigherEqualFibElements.begin();
						itrActualElement != liNumberHigherEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liNumberHigherEqualFibElements.empty()){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_HIGHER_EQUAL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberHigherEqualFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberHigherEqualFibElements.begin();
						itrActualElement != liNumberHigherEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}

	
	//**check direction ED_BELOW
		list<cFibElement*> liNumberBelowFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
			cTypeOfToReturnElements, ED_BELOW, uiElementsToReturn );
		
		if ( uiNumberOfElementsBelow != 0 ){
			if ( liNumberBelowFibElements.size() !=
					std::min( uiNumberOfElementsBelow, uiElementsToReturn ) ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberBelowFibElements.size() <<" Fib elements and not "<<
					std::min( uiNumberOfElementsBelow, uiElementsToReturn ) <<
					" (number below="<< uiNumberOfElementsBelow <<")."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberBelowFibElements.begin();
						itrActualElement != liNumberBelowFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liNumberBelowFibElements, cTypeOfToReturnElements,
				pBasisFibElement, pBasisFibElement, false );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberBelowFibElements.begin();
						itrActualElement != liNumberBelowFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liNumberBelowFibElements.empty()){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberBelowFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberBelowFibElements.begin();
						itrActualElement != liNumberBelowFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}


	//**check direction ED_BELOW_EQUAL with the Fib elements from ED_BELOW and ED_POSITION
		list<cFibElement*> liNumberBelowEqualFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
			cTypeOfToReturnElements, ED_BELOW_EQUAL, uiElementsToReturn );
		
		if ( uiNumberOfElementsBelowEqual != 0 ){
			if ( liNumberBelowEqualFibElements.size() !=
					std::min( uiNumberOfElementsBelowEqual, uiElementsToReturn ) ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberBelowEqualFibElements.size() <<" Fib elements and not "<<
					std::min( uiNumberOfElementsBelowEqual, uiElementsToReturn ) <<
					" (number below equal="<< uiNumberOfElementsBelowEqual <<")."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberBelowEqualFibElements.begin();
						itrActualElement != liNumberBelowEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liNumberBelowEqualFibElements, cTypeOfToReturnElements,
				pBasisFibElement, pBasisFibElement, true );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberBelowEqualFibElements.begin();
						itrActualElement != liNumberBelowEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liNumberBelowEqualFibElements.empty()){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_BELOW_EQUAL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberBelowEqualFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberBelowEqualFibElements.begin();
						itrActualElement != liNumberBelowEqualFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}

	
	//**check direction ED_ALL
		list<cFibElement*> liNumberAllFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
			cTypeOfToReturnElements, ED_ALL, uiElementsToReturn );
		
		if ( uiNumberOfElementsAll != 0 ){
			if ( liNumberAllFibElements.size() !=
					std::min( uiNumberOfElementsAll, uiElementsToReturn ) ){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberAllFibElements.size() <<" Fib elements and not "<<
					std::min( uiNumberOfElementsAll, uiElementsToReturn ) <<
					" (number all="<< uiNumberOfElementsAll <<")."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberAllFibElements.begin();
						itrActualElement != liNumberAllFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
			
			const int iReturnConnectedCheck = checkIsConnectedTypeTree(
				liNumberAllFibElements, cTypeOfToReturnElements,
				NULL, pBasisFibElement );
			if ( iReturnConnectedCheck != 0 ){
				cerr<<"Error: This Error(s) occured after calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") ."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberAllFibElements.begin();
						itrActualElement != liNumberAllFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;

			}
			iReturn += iReturnConnectedCheck;
		}else{
			if ( ! liNumberAllFibElements.empty()){
				cerr<<"Error: While calling getAllFibElements( "<<
					cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
					cTypeOfToReturnElements <<", ED_ALL, "<<
						uiElementsToReturn<<" ) from the "<<
					uiCallingFibElement <<"'th Fib element with the type "<<
					cTypeCallingElement <<" (number="<<
					pCallingFibElement->getNumberOfElement()<<") returned "<<
					liNumberAllFibElements.size() <<" Fib elements and not 0 "<<
					" because ther are no Fib elements of the type."<<endl;
				cerr<<"The numbers of the returned Fib elements are: ";
				for ( list<cFibElement*>::iterator itrActualElement =
						liNumberAllFibElements.begin();
						itrActualElement != liNumberAllFibElements.end();
						itrActualElement++ ){
					cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
				}
				cerr<<endl;
				iReturn++;
			}
		}
	}
	/*test getAllFibElements() for bAbsolute=true*/
	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 100 + 10) ; uiIteration++){
		
		/*choos parameters for calling getAllFibElements()*/
		
		//choos a random calling Fib element
		char cTypeCallingElement = choosRandomType();
		unsigned int uiNumberOfElementsOfType = 0;
		switch ( cTypeCallingElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		if ( uiNumberOfElementsOfType == 0 ){
			//skip
			continue;
		}
		const unsigned int uiCallingFibElement = rand() % uiNumberOfElementsOfType + 1;
		cFibElement * pCallingFibElement = pFibObject->getFibElement(
			 cTypeCallingElement, uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element with the type "<< cTypeCallingElement <<
				"of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		switch ( cTypeBasisElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}

		long lBasisFibElement = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			lBasisFibElement = rand() % uiNumberOfElementsOfType;
		}

		/*choos type of the elements to return*/
		char cTypeOfToReturnElements = choosRandomType();
		
		/*choos number of Fib elements to return*/
		switch ( cTypeOfToReturnElements ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		unsigned int uiElementsToReturn = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			uiElementsToReturn = rand() % (uiNumberOfElementsOfType + 10);
		}

		/*choos random direction from which the Fib elements are to return*/
		edDirection direction = ED_POSITION;
		string szDirection = "ED_POSITION";
		switch ( rand() % 6 ){
			case 0:direction = ED_POSITION;
				szDirection = "ED_POSITION";
			break;
			case 1:direction = ED_ALL;
				szDirection = "ED_ALL";
			break;
			case 2:direction = ED_HIGHER;
				szDirection = "ED_HIGHER";
			break;
			case 3:direction = ED_HIGHER_EQUAL;
				szDirection = "ED_HIGHER_EQUAL";
			break;
			case 4:direction = ED_BELOW;
				szDirection = "ED_BELOW";
			break;
			case 5:direction = ED_BELOW_EQUAL;
				szDirection = "ED_BELOW_EQUAL";
			break;
		}
		/*call getAllFibElements() from the master -root-element and
		getAllFibElements( bAbsolute=true ) from the calling element,
		the results should be the same*/
		list<cFibElement*> liMasterRootAllFibElements = pFibObject->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
				cTypeOfToReturnElements, direction, uiElementsToReturn );

		list<cFibElement*> liCallingElementAllFibElements = pCallingFibElement->
			getAllFibElements( cTypeBasisElement, lBasisFibElement,
				cTypeOfToReturnElements, direction, uiElementsToReturn, true );

		if ( liMasterRootAllFibElements != liCallingElementAllFibElements ){
			cerr<<"Error: After calling getAllFibElements( "<<
				cTypeBasisElement <<", "<< lBasisFibElement <<", "<<
				cTypeOfToReturnElements <<", "<< szDirection <<", "<<
				uiElementsToReturn <<" ) from the "<<
				uiCallingFibElement <<"'th Fib element with the type "<<
				cTypeCallingElement <<" (number="<<
				pCallingFibElement->getNumberOfElement()<<
				") absolut and from the master -root-element, "<<
				"the returned lists are not equal."<<endl;
			cerr<<"The numbers of the returned Fib elements from the master -root are: ";
			for ( list<cFibElement*>::iterator itrActualElement =
						liMasterRootAllFibElements.begin();
					itrActualElement != liMasterRootAllFibElements.end();
					itrActualElement++ ){
				cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
			}
			cerr<<endl;
			cerr<<"The numbers of the returned Fib elements from a Fib element absolut are: ";
			for ( list<cFibElement*>::iterator itrActualElement =
						liCallingElementAllFibElements.begin();
					itrActualElement != liCallingElementAllFibElements.end();
					itrActualElement++ ){
				cerr<< (*itrActualElement)->getNumberOfElement()<<" ;";
			}
			cerr<<endl;
			iReturn++;
		}
	}
	return iReturn;
}



/**
 * This function tests the typeElementPointToElementPoint() method on a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- unsignedIntFib typeElementPointToElementPoint( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testTypeElementPointToElementPointOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cout<<"Checking typeElementPointToElementPoint()"<<endl;

	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
		
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );

	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 100 + 20) ; uiIteration++){
		
		//choos a random calling Fib element
		char cTypeCallingElement = choosRandomType();
		unsigned int uiNumberOfElementsOfType = 0;
		switch ( cTypeCallingElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		if ( uiNumberOfElementsOfType == 0 ){
			//skip
			continue;
		}
		const unsigned int uiCallingFibElement = rand() % uiNumberOfElementsOfType + 1;
		cFibElement * pCallingFibElement = pFibObject->getFibElement(
			 cTypeCallingElement, uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element with the type "<< cTypeCallingElement <<
				"of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		uiNumberOfElementsOfType = pCallingFibElement->getNumberOfElements(
			cTypeBasisElement );

		unsignedIntFib uiBasisFibElement = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			uiBasisFibElement = rand() % uiNumberOfElementsOfType;
		}
		cFibElement * pBasisFibElement = pCallingFibElement->getFibElement(
			 cTypeBasisElement, uiBasisFibElement );
		//check the getType() methode from cList
		if ( pBasisFibElement == NULL ){
			cerr<<"Error: The "<< uiBasisFibElement <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			continue;
		}

		//convert the point with typeElementPointToElementPoint()
		longFib uiElementPoint = pCallingFibElement->
			typeElementPointToElementPoint( cTypeBasisElement, uiBasisFibElement );
		
		//check if the converted point is correct
		cFibElement * pReturnedFibElement =
			pCallingFibElement->getFibElement( uiElementPoint );
		if ( pBasisFibElement != pReturnedFibElement ){
			cerr<<"Error: While calling typeElementPointToElementPoint( "<<
				cTypeBasisElement <<", "<< uiBasisFibElement <<" ) from the "<<
				uiCallingFibElement <<"'th Fib element with the type "<<
				cTypeCallingElement <<" (number="<<
				pCallingFibElement->getNumberOfElement()<<
				") returned Fib element point number "<< uiElementPoint <<
				", but it isn't the correct Fib element point."<<endl;
			if ( pReturnedFibElement ){
				cerr<<"   The returned Fib element point number is of a Fib element with number"<<
					pReturnedFibElement->getNumberOfElement() <<" ."<<endl;
			}
			iReturn++;
		}
	}
	
	//test typeElementPointToElementPoint() for bAbsolute=true
	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 100 + 20) ; uiIteration++){
		
		//choos a random calling Fib element
		char cTypeCallingElement = choosRandomType();
		unsigned int uiNumberOfElementsOfType = 0;
		switch ( cTypeCallingElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		if ( uiNumberOfElementsOfType == 0 ){
			//skip
			continue;
		}
		const unsigned int uiCallingFibElement = rand() % uiNumberOfElementsOfType + 1;
		cFibElement * pCallingFibElement = pFibObject->getFibElement(
			 cTypeCallingElement, uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element with the type "<< cTypeCallingElement <<
				"of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		switch ( cTypeBasisElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}

		long lBasisFibElement = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			lBasisFibElement = rand() % uiNumberOfElementsOfType;
		}
		cFibElement * pBasisFibElement = pFibObject->getFibElement(
			 cTypeBasisElement, lBasisFibElement );
		//check the getType() methode from cList
		if ( pBasisFibElement == NULL ){
			cerr<<"Error: The "<< lBasisFibElement <<
				"'th Fib element from the master -root-Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			continue;
		}

		//convert the point with typeElementPointToElementPoint()
		unsigned long ulElementPoint = pCallingFibElement->
			typeElementPointToElementPoint( cTypeBasisElement, lBasisFibElement, true );
		
		//check if the converted point is correct
		cFibElement * pReturnedFibElement =
			pFibObject->getFibElement( ulElementPoint );
		if ( pBasisFibElement != pReturnedFibElement ){
			cerr<<"Error: While calling typeElementPointToElementPoint( "<<
				cTypeBasisElement <<", "<< lBasisFibElement <<", true ) from the "<<
				uiCallingFibElement <<"'th Fib element with the type "<<
				cTypeCallingElement <<" (number="<<
				pCallingFibElement->getNumberOfElement()<<
				") returned Fib element point number "<< ulElementPoint <<
				", but it isn't the correct Fib element point."<<endl;
			if ( pReturnedFibElement ){
				cerr<<"   The returned Fib element point number is of a Fib element with number"<<
					pReturnedFibElement->getNumberOfElement() <<" ."<<endl;
			}
			iReturn++;
		}
	}
	
	return iReturn;
}






/**
 * This function tests the elementPointToObjectPoints() and
 * objectPointToElementPoint() methods on a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- list<unsignedIntFib> elementPointToObjectPoints( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false ) const;
 * 	- unsignedIntFib objectPointToElementPoint( const unsignedIntFib uiObjectPoint, bool bAbsolute=false ) const;
 *
 * (Nothing to change for new Fib elements.)
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testObjectPointOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}

	cout<<"Checking elementPointToObjectPoints() and objectPointToElementPoint()"<<endl;

	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
		
	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 100 + 20) ; uiIteration++){
		
		//choos a random calling Fib element
		const unsigned int uiCallingFibElement =
			rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pCallingFibElement =
			pFibObject->getFibElement( uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		unsignedIntFib uiNumberOfElementsOfType = pCallingFibElement->
			getNumberOfElements( cTypeBasisElement );

		unsignedIntFib uiBasisFibElement = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			uiBasisFibElement = rand() % (uiNumberOfElementsOfType + 1);
		}
		cFibElement * pBasisFibElement = pCallingFibElement->getFibElement(
			 cTypeBasisElement, uiBasisFibElement );
		//check the getType() methode from cList
		if ( pBasisFibElement == NULL ){
			cerr<<"Error: The "<< uiBasisFibElement <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			continue;
		}

		//get the objectpoints for the basis Fib element
		list<unsignedIntFib> liObjectPoints = pCallingFibElement->
			elementPointToObjectPoints( cTypeBasisElement, uiBasisFibElement );
		
		list<unsignedIntFib> liObjectPointsNotReached = liObjectPoints;
		
		const unsignedIntFib uiObjectPointCallingElement =
			pCallingFibElement->getNumberOfObjectPoint();
		
		unsignedIntFib uiLastObjectPoint = 0;
		cFibElement * pLastSuperior = NULL;
		
		for ( cFibElement * pActualSuperior = pBasisFibElement;
				( pActualSuperior != NULL) && (pActualSuperior != pCallingFibElement);
				pActualSuperior = pActualSuperior->getSuperiorFibElement() ){
			
			unsignedIntFib uiObjectPoint = pActualSuperior->getNumberOfObjectPoint()
				- uiObjectPointCallingElement;
			if ( uiObjectPoint == 0 ){
				//no real objectpoint ->skip it
				continue;
			}
			//if the objectpoint has changed
			if ( uiObjectPoint != uiLastObjectPoint ){
				
				//check if the objectpoint was found by elementPointToObjectPoints()
				list<unsignedIntFib>::iterator itrFoundedObjectPoint = find(
					liObjectPoints.begin(), liObjectPoints.end(),
					uiObjectPoint );
				
				if ( itrFoundedObjectPoint == liObjectPoints.end() ){
					cerr<<"Error: While calling elementPointToObjectPoints( "<<
						cTypeBasisElement <<", "<< uiBasisFibElement <<" ) from the "<<
						uiCallingFibElement <<"'th Fib element (number="<<
						pCallingFibElement->getNumberOfElement()<<
						") the objectpoint "<< uiObjectPoint <<" was not returned."<<endl;
					iReturn++;
				}else{
					//remove the objectpoint from the not reached objectpointlist
					list<unsignedIntFib>::iterator itrReachedObjectPoint = find(
						liObjectPointsNotReached.begin(), liObjectPointsNotReached.end(),
						uiObjectPoint );
					
					if ( itrReachedObjectPoint != liObjectPointsNotReached.end() ){
						
						liObjectPointsNotReached.erase( itrReachedObjectPoint );
					}else{
						cerr<<"Error: While calling elementPointToObjectPoints( "<<
							cTypeBasisElement <<", "<< uiBasisFibElement <<" ) from the "<<
							uiCallingFibElement <<"'th Fib element (number="<<
							pCallingFibElement->getNumberOfElement()<<
							") the objectpoint "<< uiObjectPoint <<" was reached twice."<<endl;
						iReturn++;
					}
				}
				/*check if the pLastSuperior is the defining element of the
				old uiLastObjectPoint objectPointToElementPoint()*/
				//get the Fib element points to the returned objectpoints
				if ( pLastSuperior != NULL ){
					const unsignedIntFib uiLastSuperior =
						pCallingFibElement->objectPointToElementPoint( uiLastObjectPoint );
					if ( uiLastSuperior != (pLastSuperior->getNumberOfElement() -
							pCallingFibElement->getNumberOfElement() + 1) ){
						cerr<<"Error: While calling objectPointToElementPoint( "<<
							uiLastObjectPoint <<" ) from the "<<
							uiCallingFibElement <<"'th Fib element (number="<<
							pCallingFibElement->getNumberOfElement()<<
							") the objectpoint "<< uiLastObjectPoint <<
							" has not the defining Fib element with the number "<<
							(pLastSuperior->getNumberOfElement() -
							pCallingFibElement->getNumberOfElement() + 1) <<" (absolute="<<
							pLastSuperior->getNumberOfElement() <<"), but one with the number "<<
							uiLastSuperior <<" ."<<endl;
						iReturn++;
					}
				}
				//save the old value
				uiLastObjectPoint = uiObjectPoint;
			}
			//save the old value
			pLastSuperior    = pActualSuperior;
		}
		//check if the liObjectPointsNotReached list is empty
		if ( ! liObjectPointsNotReached.empty() ){
			cerr<<"Error: While calling elementPointToObjectPoints( "<<
				cTypeBasisElement <<", "<< uiBasisFibElement <<" ) from the "<<
				uiCallingFibElement <<"'th Fib element (number="<<
				pCallingFibElement->getNumberOfElement() <<
				") not all objectpoints found could be reached."<<endl;
			cerr<<"   The not reached objectpoints are : ";
			for ( list<unsignedIntFib>::iterator itrObjectPoint =
					liObjectPointsNotReached.begin();
					(itrObjectPoint != liObjectPointsNotReached.end());
					itrObjectPoint++ ){
				cerr<< *itrObjectPoint <<"; ";
			}
			cerr<<endl;
			iReturn++;
		}
	}
	
	
	//test typeElementPointToElementPoint() for bAbsolute=true
	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 100 + 20) ; uiIteration++){
		
		//choos a random calling Fib element
		const unsigned int uiCallingFibElement =
			rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pCallingFibElement =
			pFibObject->getFibElement( uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		unsignedIntFib uiNumberOfElementsOfType = pFibObject->
			getNumberOfElements( cTypeBasisElement );

		unsignedIntFib uiBasisFibElement = 0;
		if ( uiNumberOfElementsOfType != 0 ){
			uiBasisFibElement = rand() % (uiNumberOfElementsOfType + 1);
		}
		cFibElement * pBasisFibElement = pFibObject->getFibElement(
			 cTypeBasisElement, uiBasisFibElement );
		//check the getType() methode from cList
		if ( pBasisFibElement == NULL ){
			cerr<<"Error: The "<< uiBasisFibElement <<
				"'th absolute Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			continue;
		}

		//get the objectpoints for the basis Fib element
		list<unsignedIntFib> liObjectPoints = pCallingFibElement->
			elementPointToObjectPoints( cTypeBasisElement, uiBasisFibElement, true );
		
		list<unsignedIntFib> liObjectPointsNotReached = liObjectPoints;
		
		unsignedIntFib uiLastObjectPoint = 0;
		cFibElement * pLastSuperior = NULL;
		
		for ( cFibElement * pActualSuperior = pBasisFibElement;
				pActualSuperior != NULL;
				pActualSuperior = pActualSuperior->getSuperiorFibElement() ){
			
			unsignedIntFib uiObjectPoint = pActualSuperior->getNumberOfObjectPoint();
			if ( uiObjectPoint == 0 ){
				//no real objectpoint ->skip it
				continue;
			}
			
			//if the objectpoint has changed
			if ( uiObjectPoint != uiLastObjectPoint ){
				
				//check if the objectpoint was found by elementPointToObjectPoints()
				list<unsignedIntFib>::iterator itrFoundedObjectPoint = find(
					liObjectPoints.begin(), liObjectPoints.end(),
					uiObjectPoint );
				
				if ( itrFoundedObjectPoint == liObjectPoints.end() ){
					cerr<<"Error: While calling elementPointToObjectPoints( "<<
						cTypeBasisElement <<", "<< uiBasisFibElement <<", true ) from the "<<
						uiCallingFibElement <<"'th Fib element (number="<<
						pCallingFibElement->getNumberOfElement()<<
						") the objectpoint "<< uiObjectPoint <<" was not returned."<<endl;
					iReturn++;
				}else{
					//remove the objectpoint from the not reached objectpointlist
					list<unsignedIntFib>::iterator itrReachedObjectPoint = find(
						liObjectPointsNotReached.begin(), liObjectPointsNotReached.end(),
						uiObjectPoint );
					
					if ( itrReachedObjectPoint != liObjectPointsNotReached.end() ){
						
						liObjectPointsNotReached.erase( itrReachedObjectPoint );
					}else{
						cerr<<"Error: While calling elementPointToObjectPoints( "<<
							cTypeBasisElement <<", "<< uiBasisFibElement <<", true ) from the "<<
							uiCallingFibElement <<"'th Fib element (number="<<
							pCallingFibElement->getNumberOfElement()<<
							") the objectpoint "<< uiObjectPoint <<" was reached twice."<<endl;
						iReturn++;
					}
				}
				/*check if the pLastSuperior is the defining element of the
				old uiLastObjectPoint objectPointToElementPoint()*/
				//get the Fib element points to the returned objectpoints
				if ( pLastSuperior != NULL ){
					const unsignedIntFib uiLastSuperior =
						pCallingFibElement->objectPointToElementPoint( uiLastObjectPoint, true );
					if ( uiLastSuperior != pLastSuperior->getNumberOfElement() ){
						cerr<<"Error: While calling objectPointToElementPoint( "<<
							uiLastObjectPoint <<", true ) from the "<<
							uiCallingFibElement <<"'th Fib element (number="<<
							pCallingFibElement->getNumberOfElement()<<
							") the objectpoint "<< uiLastObjectPoint <<
							" has not the defining Fib element with the number "<<
							pLastSuperior->getNumberOfElement() <<", but one with the number "<<
							uiLastSuperior <<" ."<<endl;
						iReturn++;
					}
				}
				//save the old value
				uiLastObjectPoint = uiObjectPoint;
			}
			//save the old value
			pLastSuperior    = pActualSuperior;
		}
		//check if the liObjectPointsNotReached list is empty
		if ( ! liObjectPointsNotReached.empty() ){
			cerr<<"Error: While calling elementPointToObjectPoints( "<<
				cTypeBasisElement <<", "<< uiBasisFibElement <<", true ) from the "<<
				uiCallingFibElement <<"'th Fib element (number="<<
				pCallingFibElement->getNumberOfElement() <<
				") not all objectpoints found could be reached."<<endl;
			cerr<<"   The not reached objectpoints are : ";
			for ( list<unsignedIntFib>::iterator itrObjectPoint =
					liObjectPointsNotReached.begin();
					(itrObjectPoint != liObjectPointsNotReached.end());
					itrObjectPoint++ ){
				cerr<< *itrObjectPoint <<"; ";
			}
			cerr<<endl;
			iReturn++;
		}
	}
	//check upper boudery (lower boundery was checked befor)
	for ( unsigned int uiIteration = 0; uiIteration <=
			(uiNumberOfAllFibElements / 1000 + 5) ; uiIteration++){
		
		//choos a random calling Fib element
		const unsigned int uiCallingFibElement =
			rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pCallingFibElement =
			pFibObject->getFibElement( uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		//choos random basis Fib element
		char cTypeBasisElement = choosRandomType();
		unsignedIntFib uiNumberOfElementsOfType = pCallingFibElement->
			getNumberOfElements( cTypeBasisElement );

		unsignedIntFib uiBasisFibElement = uiNumberOfElementsOfType + 1;

		//get the objectpoints for the basis Fib element
		list<unsignedIntFib> liObjectPoints = pCallingFibElement->
			elementPointToObjectPoints( cTypeBasisElement, uiBasisFibElement );

		//check if the liObjectPointsNotReached list is empty
		if ( ! liObjectPoints.empty() ){
			cerr<<"Error: While calling elementPointToObjectPoints( "<<
				cTypeBasisElement <<", "<< uiBasisFibElement <<" ) from the "<<
				uiCallingFibElement <<"'th Fib element (number="<<
				pCallingFibElement->getNumberOfElement() <<
				") ther shouldn't be objectpoints for the choosen element, but ther are."<<endl;
			cerr<<"   The objectpoints given back are : ";
			for ( list<unsignedIntFib>::iterator itrObjectPoint =
					liObjectPoints.begin();
					(itrObjectPoint != liObjectPoints.end());
					itrObjectPoint++ ){
				cerr<< *itrObjectPoint <<"; ";
			}
			cerr<<endl;
			iReturn++;
		}
	}
	
	return iReturn;
}



/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bDeleteOld the bDeleteOld for the removeObject() method
 * @return the number of erros occured in the test
 */
int testOverwriteObjectWithObjectOnObject( cFibElement * pFibObject, bool bDeleteOld ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated Fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
				pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			//remove not needed parts of generated Fib object
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
		
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted
#ifdef TODO_LATER
//when getFibElements works on negativ values:
	char cTypeOverwriteObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeOverwriteObject ){
		case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
		break;
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}

	long lToOverwriteObject = uiNumberOfElementsOfType + 1;
	cFibElement * pToOverwriteObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			lToOverwriteObject = rand() % uiNumberOfElementsOfType;
		}
		pToOverwriteObject = pFibObject->getFibElement(
				cTypeOverwriteObject, lToOverwriteObject );
		//check the getType() methode from cList
		if ( pToOverwriteObject == NULL ){
			cerr<<"Error: The "<< lToOverwriteObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			return iReturn;
		}
	}
	
	if ( lToOverwriteObject != 0 ){
		if( cTypeOverwriteObject != 'u' ){
			if ( pToOverwriteObject->getNumberOfElement() <
					pCallingFibElement->getNumberOfElement() ){
				/*count from previos Fib element from calling element as same type as basis*/
				lToOverwriteObject -= pCallingFibElement->getFibElement(
					cTypeOverwriteObject, -1 )->getNumberOfElement( true );
				lToOverwriteObject--;
			}else{
				/*count from next Fib element from calling element as same type as basis*/
				lToOverwriteObject -= pCallingFibElement->getFibElement(
					cTypeOverwriteObject, 1 )->getNumberOfElement( true );
				lToOverwriteObject++;
			}
		}else{//cTypeOverwriteObject == 'u'
			lToOverwriteObject -= pCallingFibElement->getNumberOfElement();
			if ( 0 <= lToOverwriteObject ){
				lToOverwriteObject++;
			}
		}
	}

#else

	char cTypeOverwriteObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeOverwriteObject );

	unsigned int uiToOverwriteObject = 0;
	
	cFibElement * pToOverwriteObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToOverwriteObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToOverwriteObject = 0;
		}
		pToOverwriteObject = pCallingFibElement->getFibElement(
				cTypeOverwriteObject, uiToOverwriteObject );
		//check the getType() methode from cList
		if ( pToOverwriteObject == NULL ){
			cerr<<"Error: The "<< uiToOverwriteObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeOverwriteObject ){
			case 'u':uiToOverwriteObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToOverwriteObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToOverwriteObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToOverwriteObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToOverwriteObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToOverwriteObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToOverwriteObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToOverwriteObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToOverwriteObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements + 1;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements + 1;
			break;
		}
	}
#endif
	
	bool bCanOverwrite = true;
	if ( uiToOverwriteObject == 0 ){
		//overwrite the object in the selected Fib element
		cFibElement * pToOverwriteObjectTmp =
			pCallingFibElement->getNextFibElement();
		
		if ( pToOverwriteObjectTmp != NULL ){
			if ( pToOverwriteObjectTmp->getSuperiorFibElement() ==
					pCallingFibElement ){
				/*overwrite the next Fib element/ the subobject of the
				selected Fib element*/
				pToOverwriteObject = pToOverwriteObjectTmp;
			}else{
				cout<<"Should overwrite in the Fib element on the position,"<<
					" but it's next Fib element superior isn't the Fib element."<<endl;
				bCanOverwrite = false;
			}
		}else{
			cout<<"Should overwrite in the Fib element on the position, but it has no next Fib element."<<endl;
			bCanOverwrite = false;
		}
	}

	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert  = 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert  = 0;
	unsigned int uiNumberOfSetElementsInInsert      = 0;
	unsigned int uiNumberOfMatrixElementsInInsert   = 0;
	
	//store last Fib element of the insert Fib object
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanOverwrite = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanOverwrite = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult   = 0;
	unsigned int uiNumberOfRootElementsOfResult     = 0;
	unsigned int uiNumberOfPointElementsOfResult    = 0;
	unsigned int uiNumberOfListElementsOfResult     = 0;
	unsigned int uiNumberOfPropertyElementsOfResult = 0;
	unsigned int uiNumberOfAreaElementsOfResult     = 0;
	unsigned int uiNumberOfFunctionElementsOfResult = 0;
	unsigned int uiNumberOfIfElementsOfResult = 0;
	unsigned int uiNumberOfCommentElementsOfResult  = 0;
	unsigned int uiNumberOfExtObjectElementsOfResult  = 0;
	unsigned int uiNumberOfExtSubobjectElementsOfResult  = 0;
	unsigned int uiNumberOfSetElementsOfResult  = 0;
	unsigned int uiNumberOfMatrixElementsOfResult  = 0;
	
	//store the Fib elements betwean which the Fib object will be inserted
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = NULL;
	

	if ( pToOverwriteObject != NULL ){
		uiNumberOfAllFibElementsOfResult =
			uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert -
			pToOverwriteObject->getNumberOfElements();
		uiNumberOfRootElementsOfResult =
			uiNumberOfRootElements + uiNumberOfRootElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'r' );
		uiNumberOfPointElementsOfResult =
			uiNumberOfPointElements + uiNumberOfPointElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'p' );
		uiNumberOfListElementsOfResult =
			uiNumberOfListElements + uiNumberOfListElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsOfResult =
			uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsOfResult =
			uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsOfResult =
			uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'f' );
		uiNumberOfIfElementsOfResult =
			uiNumberOfIfElements + uiNumberOfIfElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsOfResult =
			uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsOfResult =
			uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsOfResult =
			uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 's' );
		uiNumberOfSetElementsOfResult =
			uiNumberOfSetElements + uiNumberOfSetElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsOfResult =
			uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'm' );

		//store the Fib elements betwean which the Fib object will be inserted
		pSuperiorFibObjectToInsert = pToOverwriteObject->getSuperiorFibElement();
		pAfterFibObjectToInsert = pToOverwriteObject-> getFibElement(
			pToOverwriteObject->getNumberOfElements() + 1 );
		
		if ( (pToOverwriteObject->getType() == 'r')  ){
			cout<<"The to overwrite is an root-element."<<endl;
			bCanOverwrite = false;
		}
		if ( (pToOverwriteObject->getSuperiorFibElement() == NULL) ){
			cout<<"The to overwrite has no superior."<<endl;
			bCanOverwrite = false;
		}
	}else{
		cout<<"The to overwrite object didn't exists."<<endl;
		bCanOverwrite = false;
	}
	//clone to compare with if Fib object shouldn't be changed
	cFibElement * pFibObjectClone = pFibObject->clone();
	
	cout<<"Calling overwriteObjectWithObject("<<
		pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
		uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") << " ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to overwrite "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	if ( pToOverwriteObject == NULL ){
		cout<<"   But ther is no Fib object to overwrite.";
	}else{
		cout<<"   The to overwrite object has the number "<<
			pToOverwriteObject->getNumberOfElement() <<" and type "<<
			pToOverwriteObject->getType() <<" ."<<endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call overwriteObjectWithObject()
	bool bOverwritten = pCallingFibElement->overwriteObjectWithObject(
		pFibObjectToInsert, cTypeOverwriteObject, uiToOverwriteObject, bDeleteOld );

	if ( ! bCanOverwrite  ){
		if ( bOverwritten ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false")<<
				" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the to overwrite Fib element can't be overwritten, but it "<<
				"was overwritten."<<endl;
			iReturn++;
			
			if ( ( ! bDeleteOld ) && ( pToOverwriteObject != NULL ) ){
				//delete the not deleted but removed part object
				cout<<flush;
				cFibElement::deleteObject( pToOverwriteObject );
			}
		}else{
			cout<<"The object was correctly not overwritten."<<endl;
			
			if ( pFibObjectToInsert != NULL ){
				//delete the not inserted Fib object
				cout<<"Delete the not inserted Fib object."<<endl<<flush;
				cout<<flush;
				pFibObjectToInsert->deleteObject();
			}
		}
		//check if the Fib object hasn't changed
		if ( ! pFibObject->equal( *pFibObjectClone ) ){
			cerr<<"Error: The Fib object was changed."<<endl;
			iReturn++;
		}
		pFibObjectClone->deleteObject();
		return iReturn;
	}
	pFibObjectClone->deleteObject();
	
	if ( ! bOverwritten ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the to overwrite Fib element couldn't be overwritten."<<endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to overwrite "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
		}
		iReturn++;
	}else{
		cout<<"The object was correctly overwritten."<<endl;
	}
	if ( bOverwritten && ( ! bDeleteOld ) && ( pToOverwriteObject != NULL ) ){
		//delete the not deleted but removed part object
		cout<<flush;
		cFibElement::deleteObject( pToOverwriteObject );
	}
	if ( ( ! bOverwritten ) && ( pFibObjectToInsert != NULL ) ){
		//delete the not inserted Fib object
		cout<<"Delete the not inserted Fib object."<<endl<<flush;
		cout<<flush;
		pFibObjectToInsert->deleteObject();
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	if ( (pSuperiorFibObjectToInsert != NULL) && (pFibObjectToInsert != NULL) &&
			(pFibObjectToInsert->getSuperiorFibElement() != NULL) ){
		if ( pSuperiorFibObjectToInsert !=
				pFibObjectToInsert->getSuperiorFibElement() ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
				" ) from the "<<pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong superior Fib element (number="<<
				pFibObjectToInsert->getSuperiorFibElement()->getNumberOfElement()
				<<" and not number="<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<") ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior element is NULL (sup insert old="<<
			pSuperiorFibObjectToInsert <<" new="<<
			pFibObjectToInsert->getSuperiorFibElement() <<")."<<endl;
		iReturn++;
	}
	if ( pLastInFibObjectInInsert != NULL ){
		if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
				pLastInFibObjectInInsert->getNextFibElement() ) ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false")
				<< " ) from the "<< pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element ";
			if ( pLastInFibObjectInInsert->getNextFibElement() ){
				cerr<<"(number="<<pLastInFibObjectInInsert->getNextFibElement()->
					getNumberOfElement() <<" and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		if ( (pAfterFibObjectToInsert == NULL) &&
				(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
				" ) from the "<< pCallingElementNumber <<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be."<<endl;
			iReturn++;
		}
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool overwriteObjectWithObject( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool bDeleteOld, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bDeleteOld the bDeleteOld for the removeObject() method
 * @return the number of erros occured in the test
 */
int testOverwriteObjectWithObjectAbsoluteOnObject( cFibElement * pFibObject, bool bDeleteOld ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated Fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			//remove not needed parts of generated Fib object
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted
	char cTypeOverwriteObject = choosRandomType();

	unsigned int uiToOverwriteObject = 0;
	
	cFibElement * pToOverwriteObject = NULL;
	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeOverwriteObject ){
		case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
		break;
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToOverwriteObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToOverwriteObject = 0;
		}
		pToOverwriteObject = pFibObject->getFibElement(
				cTypeOverwriteObject, uiToOverwriteObject );
		//check the getType() methode from cList
		if ( pToOverwriteObject == NULL ){
			cerr<<"Error: The "<< uiToOverwriteObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		uiToOverwriteObject = uiNumberOfAllFibElements + 1;
	}

	
	bool bCanOverwrite = true;
	if ( uiToOverwriteObject == 0 ){
		//overwrite the object in the selected Fib element
		cFibElement * pToOverwriteObjectTmp =
			pCallingFibElement->getNextFibElement();
		
		if ( pToOverwriteObjectTmp != NULL ){
			if ( pToOverwriteObjectTmp->getSuperiorFibElement() ==
					pCallingFibElement ){
				/*overwrite the next Fib element/ the subobject of the
				selected Fib element*/
				pToOverwriteObject = pToOverwriteObjectTmp;
			}else{
				cout<<"Should overwrite in the Fib element on the position,"<<
					" but it's next Fib element superior isn't the Fib element."<<endl;
				bCanOverwrite = false;
			}
		}else{
			cout<<"Should overwrite in the Fib element on the position, but it has no next Fib element."<<endl;
			bCanOverwrite = false;
		}
	}

	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	//store last Fib element of the insert Fib object
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanOverwrite = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanOverwrite = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult   = 0;
	unsigned int uiNumberOfRootElementsOfResult     = 0;
	unsigned int uiNumberOfPointElementsOfResult    = 0;
	unsigned int uiNumberOfListElementsOfResult     = 0;
	unsigned int uiNumberOfPropertyElementsOfResult = 0;
	unsigned int uiNumberOfAreaElementsOfResult     = 0;
	unsigned int uiNumberOfFunctionElementsOfResult = 0;
	unsigned int uiNumberOfIfElementsOfResult = 0;
	unsigned int uiNumberOfCommentElementsOfResult  = 0;
	unsigned int uiNumberOfExtObjectElementsOfResult= 0;
	unsigned int uiNumberOfExtSubobjectElementsOfResult= 0;
	unsigned int uiNumberOfSetElementsOfResult= 0;
	unsigned int uiNumberOfMatrixElementsOfResult= 0;
	
	//store the Fib elements betwean which the Fib object will be inserted
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = NULL;
	

	if ( pToOverwriteObject != NULL ){
		uiNumberOfAllFibElementsOfResult =
			uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert -
			pToOverwriteObject->getNumberOfElements();
		uiNumberOfRootElementsOfResult =
			uiNumberOfRootElements + uiNumberOfRootElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'r' );
		uiNumberOfPointElementsOfResult =
			uiNumberOfPointElements + uiNumberOfPointElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'p' );
		uiNumberOfListElementsOfResult =
			uiNumberOfListElements + uiNumberOfListElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsOfResult =
			uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsOfResult =
			uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsOfResult =
			uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'f' );
		uiNumberOfIfElementsOfResult =
			uiNumberOfIfElements + uiNumberOfIfElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsOfResult =
			uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsOfResult =
			uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsOfResult =
			uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 's' );
		uiNumberOfSetElementsOfResult =
			uiNumberOfSetElements + uiNumberOfSetElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsOfResult =
			uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert -
			pToOverwriteObject->getNumberOfElements( 'm' );

		//store the Fib elements betwean which the Fib object will be inserted
		pSuperiorFibObjectToInsert = pToOverwriteObject->getSuperiorFibElement();
		pAfterFibObjectToInsert = pToOverwriteObject-> getFibElement(
			pToOverwriteObject->getNumberOfElements() + 1 );
		
		if ( (pToOverwriteObject->getType() == 'r')  ){
			cout<<"The to overwrite is an root-element."<<endl;
			bCanOverwrite = false;
		}
		if ( (pToOverwriteObject->getSuperiorFibElement() == NULL) ){
			cout<<"The to overwrite has no superior."<<endl;
			bCanOverwrite = false;
		}
	}else{
		cout<<"The to overwrite object didn't exists."<<endl;
		bCanOverwrite = false;
	}
	
	cout<<"Calling overwriteObjectWithObject("<<
		pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
		uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") << ", true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to overwrite "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	if ( pToOverwriteObject == NULL ){
		cout<<"   But ther is no Fib object to overwrite.";
	}else{
		cout<<"   The to overwrite object has the number "<<
			pToOverwriteObject->getNumberOfElement() <<" and type "<<
			pToOverwriteObject->getType() <<" ."<<endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call overwriteObjectWithObject()
	bool bOverwritten = pCallingFibElement->overwriteObjectWithObject(
		pFibObjectToInsert, cTypeOverwriteObject, uiToOverwriteObject, bDeleteOld, true );

	if ( ! bCanOverwrite  ){
		if ( bOverwritten ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false")<<
				", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the to overwrite Fib element can't be overwritten, but it "<<
				"was overwritten."<<endl;
			iReturn++;
			
			if ( ( ! bDeleteOld ) && ( pToOverwriteObject != NULL ) ){
				//delete the not deleted but removed part object
				cout<<flush;
				cFibElement::deleteObject( pToOverwriteObject );
			}
		}else{
			cout<<"The object was correctly not overwritten."<<endl;
			
			if ( pFibObjectToInsert != NULL ){
				//delete the not inserted Fib object
				cout<<"Delete the not inserted Fib object."<<endl<<flush;
				cout<<flush;
				pFibObjectToInsert->deleteObject();
			}
		}
		//TODO check if the Fib object hasn't changed
		return iReturn;
	}
	if ( ! bOverwritten ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the to overwrite Fib element couldn't be overwritten."<<endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to overwrite "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
		}
		iReturn++;
	}else{
		cout<<"The object was correctly overwritten."<<endl;
	}
	if ( bOverwritten && ( ! bDeleteOld ) && ( pToOverwriteObject != NULL ) ){
		//delete the not deleted but removed part object
		cout<<flush;
		cFibElement::deleteObject( pToOverwriteObject );
	}
	if ( ( ! bOverwritten ) && ( pFibObjectToInsert != NULL ) ){
		//delete the not inserted Fib object
		cout<<"Delete the not inserted Fib object."<<endl<<flush;
		cout<<flush;
		pFibObjectToInsert->deleteObject();
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling overwriteObjectWithObject("<<
			pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
			uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
			", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	if ( (pSuperiorFibObjectToInsert != NULL) && (pFibObjectToInsert != NULL) &&
			(pFibObjectToInsert->getSuperiorFibElement() != NULL) ){
		if ( pSuperiorFibObjectToInsert !=
				pFibObjectToInsert->getSuperiorFibElement() ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
				", true ) from the "<<pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong superior Fib element (number="<<
				pFibObjectToInsert->getSuperiorFibElement()->getNumberOfElement()
				<<" and not number="<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<") ."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior element is NULL (sup insert old="<<
			pSuperiorFibObjectToInsert <<" new="<<
			pFibObjectToInsert->getSuperiorFibElement() <<")."<<endl;
		iReturn++;
	}
	if ( pLastInFibObjectInInsert != NULL ){
		if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
				pLastInFibObjectInInsert->getNextFibElement() ) ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false")<<
				", true ) from the "<< pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element ";
			if ( pLastInFibObjectInInsert->getNextFibElement() ){
				cerr<<"(number="<<pLastInFibObjectInInsert->getNextFibElement()->
					getNumberOfElement() <<" and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		if ( (pAfterFibObjectToInsert == NULL) &&
				(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: While calling overwriteObjectWithObject("<<
				pFibObjectToInsert <<", "<< cTypeOverwriteObject<<", "<<
				uiToOverwriteObject<<", "<< (bDeleteOld ?"true":"false") <<
				", true ) from the "<< pCallingElementNumber <<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be."<<endl;
			iReturn++;
		}
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}



/**
 * This function tests the removeObject() method for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bDeleteOld the bDeleteOld for the removeObject() method
 * @return the number of erros occured in the test
 */
int testRemoveObjectOnObject( cFibElement * pFibObject, bool bDeleteOld ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfAllObjectPoints =
		pFibObject->getNumberOfObjectPoints();
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfCallingObjectPoints =
		pCallingFibElement->getNumberOfObjectPoints();
	
	if ( uiNumberOfCallingObjectPoints == 0 ){
		//skip
		return iReturn;
	}
	
	const unsigned int uiToRemoveObject =
		rand() % uiNumberOfCallingObjectPoints + 1;

	unsignedIntFib uiDefiningFibElement =
		pCallingFibElement->objectPointToElementPoint( uiToRemoveObject );

	cFibElement * pDefiningFibElement =
		pCallingFibElement->getFibElement( uiDefiningFibElement );

	if ( pDefiningFibElement == NULL ){
		cerr<<"Error: The "<< uiDefiningFibElement <<
			"'th Fib element from the calling Fib element (number="<<
			pCallingFibElement->getNumberOfElement() <<" and type "<<
			pCallingFibElement->getType()<<") of the "<<
			"Fib object isn't returned as the defining the Fib element."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cFibElement * pSuperiorDefiningFibElement =
		pDefiningFibElement->getSuperiorFibElement();
	
	const unsigned int uiNumberOfAllObjectPointsSuperior =
		pSuperiorDefiningFibElement->getNumberOfObjectPoints();
	const unsigned int uiNumberOfAllObjectPointsDefining =
		pDefiningFibElement->getNumberOfObjectPoints();
	
	unsigned int uiNumberOfAllObjectPointsSuperiorAfterDeleting =
		uiNumberOfAllObjectPointsSuperior - uiNumberOfAllObjectPointsDefining - 1;
	unsigned int uiNumberOfAllObjectPointsAllAfterDeleting =
		uiNumberOfAllObjectPoints - uiNumberOfAllObjectPointsDefining - 1;

	bool isDeletebel = true;
	if ( ( pSuperiorDefiningFibElement->getType() != 'l' ) &&
			( pSuperiorDefiningFibElement->getType() != 'o' ) ){
		//containing element is no list element -> can't remove
		isDeletebel = false;
		uiNumberOfAllObjectPointsAllAfterDeleting =
			uiNumberOfAllObjectPoints;
		uiNumberOfAllObjectPointsSuperiorAfterDeleting =
			uiNumberOfAllObjectPointsSuperior;
	}
	bool bSuperiorWillBeRemoved = false;
	if ( pSuperiorDefiningFibElement->getType() == 'l' ){
		cList * pSuperiorListDefiningFibElement =
			(cList*)pSuperiorDefiningFibElement;
		
		if ( pSuperiorListDefiningFibElement->getNumberOfUnderobjects() == 2 ){
			//the list element will be removed
			uiNumberOfAllObjectPointsAllAfterDeleting--;
			uiNumberOfAllObjectPointsSuperiorAfterDeleting--;
			bSuperiorWillBeRemoved = true;
		}
	}

	cout<<"The defining Fib element (number="<<
		pDefiningFibElement->getNumberOfElement() <<" and type "<<
		pDefiningFibElement->getType()<<"), from the calling Fib element (number="<<
		pCallingFibElement->getNumberOfElement() <<" and type "<<
		pCallingFibElement->getType()<<") of the "<<
		"Fib object, has the superior Fib element with the number "<<
		pSuperiorDefiningFibElement->getNumberOfElement()<<
		" and type "<< pSuperiorDefiningFibElement->getType()<<" ."<<endl;
	cout<<"  Calling removeObject( "<<uiToRemoveObject<<", bDeleteOld="<<
		(bDeleteOld ? "true" : "false") <<" ) from the calling element."<<endl;
	cout<<"  Removing "<< uiNumberOfAllObjectPointsDefining + 1 <<" objectpoints. "<<
		" The Fib object has "<< uiNumberOfAllObjectPoints <<" objectpoints."<<endl;

	//test removeObject()
	bool bObjectRemoved = pCallingFibElement->removeObject( uiToRemoveObject, bDeleteOld );
	
	if ( isDeletebel ){
		if ( ! bObjectRemoved ){
			cerr<<"Error: Couldn't remove the part object."<<endl;
			iReturn++;
		}else{
			cout<<"Object correctly removed."<<endl;
		}
	}else{
		if ( bObjectRemoved ){
			cerr<<"Error: Could remove the part object, but it shouldn't be removebel."<<endl;
			iReturn++;
		}else{
			cout<<"Object correctly not removed."<<endl;
		}
	}
	if ( bObjectRemoved && (! bDeleteOld) ){
		//delete the not deleted but removed part object
		cout<<flush;
		cFibElement::deleteObject( pDefiningFibElement );
	}
	
	if ( ! bSuperiorWillBeRemoved ){
		if ( pSuperiorDefiningFibElement->getNumberOfObjectPoints() !=
				uiNumberOfAllObjectPointsSuperiorAfterDeleting ){
			cerr<<"Error: The number of objectpoints of the superior is "<<
				pSuperiorDefiningFibElement->getNumberOfObjectPoints()<<
				", but should be "<< uiNumberOfAllObjectPointsSuperiorAfterDeleting <<" ."<<endl;
			iReturn++;
		}
	}

	if ( pFibObject->getNumberOfObjectPoints() !=
			uiNumberOfAllObjectPointsAllAfterDeleting ){
		cerr<<"Error: The number of objectpoints in the Fib object is "<<
			pFibObject->getNumberOfObjectPoints()<<
			", but should be "<< uiNumberOfAllObjectPointsAllAfterDeleting <<" ."<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the removeObject() method for a given Fib object,
 * with bAbsolute set to true.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool removeObject( const unsignedIntFib objectPoint, bool bDeleteOld, bool bAbsolute=true );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bDeleteOld the bDeleteOld for the removeObject() method
 * @return the number of erros occured in the test
 */
int testRemoveObjectAbsoluteOnObject( cFibElement * pFibObject, bool bDeleteOld ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfAllObjectPoints =
		pFibObject->getNumberOfObjectPoints();
	
	if ( uiNumberOfAllObjectPoints == 0 ){
		//skip
		return iReturn;
	}

	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );


	const unsigned int uiToRemoveObject =
		rand() % uiNumberOfAllObjectPoints + 1;

	unsignedIntFib uiDefiningFibElement =
		pFibObject->objectPointToElementPoint( uiToRemoveObject, true );

	cFibElement * pDefiningFibElement =
		pFibObject->getFibElement( uiDefiningFibElement, true );

	if ( pDefiningFibElement == NULL ){
		cerr<<"Error: The "<< uiDefiningFibElement <<
			"'th Fib element from the calling Fib element (number="<<
			pCallingFibElement->getNumberOfElement() <<") of the "<<
			"Fib object isn't returned as the defining the Fib element."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cFibElement * pSuperiorDefiningFibElement =
		pDefiningFibElement->getSuperiorFibElement();
	
	const unsigned int uiNumberOfAllObjectPointsSuperior =
		pSuperiorDefiningFibElement->getNumberOfObjectPoints();
	const unsigned int uiNumberOfAllObjectPointsDefining =
		pDefiningFibElement->getNumberOfObjectPoints();
	
	unsigned int uiNumberOfAllObjectPointsSuperiorAfterDeleting =
		uiNumberOfAllObjectPointsSuperior - uiNumberOfAllObjectPointsDefining - 1;
	unsigned int uiNumberOfAllObjectPointsAllAfterDeleting =
		uiNumberOfAllObjectPoints - uiNumberOfAllObjectPointsDefining - 1;

	bool isDeletebel = true;
	if ( ( pSuperiorDefiningFibElement->getType() != 'l' ) &&
			( pSuperiorDefiningFibElement->getType() != 'o' ) ){
		//containing element is no list element -> can't remove
		isDeletebel = false;
		uiNumberOfAllObjectPointsAllAfterDeleting =
			uiNumberOfAllObjectPoints;
		uiNumberOfAllObjectPointsSuperiorAfterDeleting =
			uiNumberOfAllObjectPointsSuperior;
	}
	bool bSuperiorWillBeRemoved = false;
	if ( pSuperiorDefiningFibElement->getType() == 'l' ){
		cList * pSuperiorListDefiningFibElement =
			(cList*)pSuperiorDefiningFibElement;
		
		if ( pSuperiorListDefiningFibElement->getNumberOfUnderobjects() == 2 ){
			//the list element will be removed
			uiNumberOfAllObjectPointsAllAfterDeleting--;
			uiNumberOfAllObjectPointsSuperiorAfterDeleting--;
			bSuperiorWillBeRemoved = true;
		}
	}

	cout<<"The defining Fib element (number="<<
		pDefiningFibElement->getNumberOfElement() <<
		"), from the calling Fib element (number="<<
		pCallingFibElement->getNumberOfElement() <<") of the "<<
		"Fib object, has the superior Fib element with the number "<<
		pSuperiorDefiningFibElement->getNumberOfElement()<<
		" and type "<< pSuperiorDefiningFibElement->getType()<<" ."<<endl;
	cout<<"  Calling removeObject( "<<uiToRemoveObject<<", bDeleteOld="<<
		(bDeleteOld ? "true" : "false") <<", bAbsolut=true ) from the calling element."<<endl;
	cout<<"  Removing "<< uiNumberOfAllObjectPointsDefining + 1 <<" objectpoints. "<<
		" The Fib object has "<< uiNumberOfAllObjectPoints <<" objectpoints."<<endl<<flush;

	//test removeObject()
	bool bObjectRemoved = pCallingFibElement->removeObject( uiToRemoveObject, bDeleteOld, true );
	
	if ( isDeletebel && ! bObjectRemoved ){
		cerr<<"Error: Couldn't remove the part object."<<endl;
		iReturn++;
	}
	if ( ! isDeletebel && bObjectRemoved ){
		cerr<<"Error: Could remove the part object, but it shouldn't be removebel."<<endl;
		iReturn++;
	}
	
	if ( bObjectRemoved && ( ! bDeleteOld ) ){
		//delete the not deleted but removed part object
		cFibElement::deleteObject( pDefiningFibElement );
	}
	
	if ( ! bSuperiorWillBeRemoved ){
		if ( pSuperiorDefiningFibElement->getNumberOfObjectPoints() !=
				uiNumberOfAllObjectPointsSuperiorAfterDeleting ){
			cerr<<"Error: The number of objectpoints of the superior is "<<
				pSuperiorDefiningFibElement->getNumberOfObjectPoints()<<
				", but should be "<< uiNumberOfAllObjectPointsSuperiorAfterDeleting <<" ."<<endl;
			iReturn++;
		}
	}

	if ( pFibObject->getNumberOfObjectPoints() !=
			uiNumberOfAllObjectPointsAllAfterDeleting ){
		cerr<<"Error: The number of objectpoints in the Fib object is "<<
			pFibObject->getNumberOfObjectPoints()<<
			", but should be "<< uiNumberOfAllObjectPointsAllAfterDeleting <<" ."<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}




#ifdef FEATURE_INSERT_OBJECT_IN_ELEMENT

//TODO check

/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectFirstOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated Fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted

	char cTypeInsertObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeInsertObject );

	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pCallingFibElement->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeInsertObject ){
			case 'u':uiToInsertPositionObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToInsertPositionObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToInsertPositionObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToInsertPositionObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToInsertPositionObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToInsertPositionObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToInsertPositionObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToInsertPositionObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToInsertPositionObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToInsertPositionObject = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToInsertPositionObject = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToInsertPositionObject = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToInsertPositionObject = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = pToInsertPositionObject;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pAfterFibObjectToInsert = pCallingFibElement->getNextFibElement();
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
					pAfterFibObjectToInsert = pToInsertPositionObject;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}//else ( pToInsertPositionObject->getSuperiorFibElement() != NULL )
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert   = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
	}
	
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) &&
			( ( pToInsertPositionObject == NULL ) ||
				( pToInsertPositionObject->getType() != 'l' ) ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}
	//adapt pAfterFibObjectToInsert
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
				( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
			( ( pToInsertPositionObject != NULL ) &&
				( pToInsertPositionObject->getType() == 'l' ) ) ){
		//Fib object will be inserted into pToInsertPositionObject as first subobject
		pAfterFibObjectToInsert = pToInsertPositionObject->getNextFibElement();
	}
	
	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType();
	if ( pToInsertPositionObject ){
		cout<<", insert position type "<<pToInsertPositionObject->getType();
	}
	if ( pSuperiorFibObjectToInsert ){
		cout<<", superior to insert position type "<<pSuperiorFibObjectToInsert->getType();
	}
	cout<<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	const bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, true );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert."<<endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted."<<endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to insert "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
		}
		iReturn++;
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
						( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
					( ( pToInsertPositionObject != NULL ) &&
						( pToInsertPositionObject->getType() == 'l' ) ) ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pToInsertPositionObject) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list object element at the insert position ( notBranch( list(...)) )."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = static_cast<cList*>(
				pFibObjectToInsert->getSuperiorFibElement());
			
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
							( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
						( ( pToInsertPositionObject != NULL ) &&
							( pToInsertPositionObject->getType() == 'l' ) ) ){
					
					if ( pInsertList->getUnderobject( 1 ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's first subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( 2 ) != pAfterFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the old after Fib object the inserted "<<
							"Fib object as it's second subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted,is not the insert position Fib object."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( 1 ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's first subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( 2 ) != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the insert position Fib object as it's "<<
							"second subobject."<<endl;
						iReturn++;
					}
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == pInsertList->getNumberOfUnderobjects() ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the last in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement + 1 ) != pToInsertPositionObject ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( ( uiActualSubobject == pInsertExtObject->getNumberOfSubobjects() ) &&
						( 1 < uiActualSubobject ) ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior external object element inserted "<<
							"Fib object is the last in the external object element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
				}else{
					if ( ( pToInsertPositionObject != NULL ) &&
							( pInsertExtObject->getSubobject( uiActualSubobject + 1 ) != pToInsertPositionObject ) ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}

	if ( ( pToInsertPositionObject != NULL ) &&
			( (pToInsertPositionObject->getType() != 'l') &&
				(pToInsertPositionObject->getType() != 'o') ) &&
			(pToInsertPositionObject != pLastInFibObjectInInsert->getNextFibElement()) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element ";
		if ( pLastInFibObjectInInsert->getNextFibElement() ){
			cerr<<"(number="<<pLastInFibObjectInInsert->getNextFibElement()->
				getNumberOfElement() <<" and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<")."<<endl;
		}else{
			cerr<<" NULL and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<")."<<endl;
		}
		iReturn++;
	}
	
	cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
		pFibObjectToInsert->getNumberOfElements() + 1 );
	
	if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
			pNewAfterFibObjectToInsert ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the insert position Fib object has the wrong next Fib element ";
		if ( pNewAfterFibObjectToInsert ){
			cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
				" and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
		}else{
			cerr<<" NULL and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
		}
		iReturn++;
	}
	if ( (pAfterFibObjectToInsert == NULL) &&
			(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element "<<
			"it isn't NULL (has number="<<
			pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
			<<"), but it should be."<<endl;
		iReturn++;
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=true );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectFirstAbsoluteOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated Fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted
	char cTypeInsertObject = choosRandomType();

	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeInsertObject ){
		case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
		break;
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}
	
	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pFibObject->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		uiToInsertPositionObject = uiNumberOfElementsOfType + 1;
	}
	if ( uiToInsertPositionObject == 0 ){
		pToInsertPositionObject = pCallingFibElement;
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = pToInsertPositionObject;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pAfterFibObjectToInsert = pCallingFibElement->getNextFibElement();
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
					pAfterFibObjectToInsert = pToInsertPositionObject;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}//else ( pToInsertPositionObject->getSuperiorFibElement() != NULL )
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert = 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert = 0;
	unsigned int uiNumberOfSetElementsInInsert = 0;
	unsigned int uiNumberOfMatrixElementsInInsert = 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
	}
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) &&
			( ( pToInsertPositionObject == NULL ) ||
				( pToInsertPositionObject->getType() != 'l' ) ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}
	//adapt pAfterFibObjectToInsert
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
				( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
			( ( pToInsertPositionObject != NULL ) &&
				( pToInsertPositionObject->getType() == 'l' ) ) ){
		//Fib object will be inserted into pToInsertPositionObject as first subobject
		pAfterFibObjectToInsert = pToInsertPositionObject->getNextFibElement();
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", true, true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType();
	if ( pToInsertPositionObject ){
		cout<<", insert position type "<<pToInsertPositionObject->getType();
	}
	if ( pSuperiorFibObjectToInsert ){
		cout<<", superior to insert position type "<<pSuperiorFibObjectToInsert->getType();
	}
	cout<<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	if ( pFibObjectToInsert ){
		cout<<"   The to insert Fib object has the type "<<
			pFibObjectToInsert->getType() <<" ."<<endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, true, true );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert."<<endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted."<<endl;
		iReturn++;
		
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}else{
		cout<<"   The Fib object was inserted."<<endl;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
						( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
					( ( pToInsertPositionObject != NULL ) &&
						( pToInsertPositionObject->getType() == 'l' ) ) ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pToInsertPositionObject) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list object element at the insert position ( notBranch( list(...)) )."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = static_cast<cList*>(
				pFibObjectToInsert->getSuperiorFibElement());
			
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
							( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
						( ( pToInsertPositionObject != NULL ) &&
							( pToInsertPositionObject->getType() == 'l' ) ) ){
				
					if ( pInsertList->getUnderobject( 1 ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's first subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( 2 ) != pAfterFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the old after Fib object the inserted "<<
							"Fib object as it's second subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, is not the insert position Fib object."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( 1 ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's first subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( 2 ) != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the insert position Fib object as it's "<<
							"second subobject."<<endl;
						iReturn++;
					}
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement ++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == pInsertList->getNumberOfUnderobjects() ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the last in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement + 1 ) != pToInsertPositionObject ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( ( uiActualSubobject == pInsertExtObject->getNumberOfSubobjects() ) &&
						( 1 < uiActualSubobject ) ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior external object element inserted "<<
							"Fib object is the last in the external object element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
				}else{
					if ( ( pToInsertPositionObject != NULL ) &&
							( pInsertExtObject->getSubobject( uiActualSubobject + 1 ) != pToInsertPositionObject ) ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}

	if ( ( pToInsertPositionObject != NULL ) &&
			( (pToInsertPositionObject->getType() != 'l') &&
				(pToInsertPositionObject->getType() != 'o') ) &&
			(pToInsertPositionObject != pLastInFibObjectInInsert->getNextFibElement()) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element ";
		if ( pLastInFibObjectInInsert->getNextFibElement() ){
			cerr<<"(number="<<pLastInFibObjectInInsert->getNextFibElement()->
				getNumberOfElement() <<" and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<")."<<endl;
		}else{
			cerr<<" NULL and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<")."<<endl;
		}
		iReturn++;
	}
	
	cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
		pFibObjectToInsert->getNumberOfElements() + 1 );
	
	if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
			pNewAfterFibObjectToInsert ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the insert position Fib object has the wrong next Fib element ";
		if ( pNewAfterFibObjectToInsert ){
			cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
				" and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
		}else{
			cerr<<" NULL and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
		}
		iReturn++;
	}
	if ( (pAfterFibObjectToInsert == NULL) &&
			(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element "<<
			"it isn't NULL (has number="<<
			pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
			<<"), but it should be."<<endl;
		iReturn++;
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectSecondOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated Fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted

	char cTypeInsertObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeInsertObject );

	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pCallingFibElement->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeInsertObject ){
			case 'u':uiToInsertPositionObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToInsertPositionObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToInsertPositionObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToInsertPositionObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToInsertPositionObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToInsertPositionObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToInsertPositionObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToInsertPositionObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToInsertPositionObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToInsertPositionObject = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToInsertPositionObject = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToInsertPositionObject = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToInsertPositionObject = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}//else ( pToInsertPositionObject->getSuperiorFibElement() != NULL )
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert       = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	cFibElement * pAfterFibObjectToInsert = NULL;
	unsignedIntFib uiNumberOfElementsInToInsert = 0;
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
		uiNumberOfElementsInToInsert =
			pToInsertPositionObject->getNumberOfElements();
		pAfterFibObjectToInsert = pToInsertPositionObject->getFibElement(
			uiNumberOfElementsInToInsert + 1 );
	}else if ( ( pSuperiorFibObjectToInsert != NULL ) && bCanInsert ){
		//can insert in superior element
		pAfterFibObjectToInsert = pSuperiorFibObjectToInsert->getFibElement(
			pSuperiorFibObjectToInsert->getNumberOfElements() + 1 );
	}
	
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) &&
			( ( pToInsertPositionObject == NULL ) ||
				( pToInsertPositionObject->getType() != 'l' ) ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", false ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType();
	if ( pToInsertPositionObject ){
		cout<<", insert position type "<<pToInsertPositionObject->getType()<<
			" (nbr.: "<<pToInsertPositionObject->getNumberOfElement()<<")";
	}
	if ( pSuperiorFibObjectToInsert ){
		cout<<", superior to insert position type "<<pSuperiorFibObjectToInsert->getType()<<
			"(nbr.: "<<pSuperiorFibObjectToInsert->getNumberOfElement()<<")";
	}
	cout<<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	if ( pFibObjectToInsert ){
		cout<<"   The to insert Fib object has the type "<<
			pFibObjectToInsert->getType() <<" ."<<endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, false );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert."<<endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted."<<endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to insert "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
		}
		iReturn++;
		
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
						( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
					( ( pToInsertPositionObject != NULL ) &&
						( pToInsertPositionObject->getType() == 'l' ) ) ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pToInsertPositionObject) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list object element at the insert position ( notBranch( list(...)) )."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = static_cast<cList*>(
				pFibObjectToInsert->getSuperiorFibElement());
			
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
							( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
						( ( pToInsertPositionObject != NULL ) &&
							( pToInsertPositionObject->getType() == 'l' ) ) ){
				
					if ( pInsertList->getUnderobject(
							pInsertList->getNumberOfUnderobjects() ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's last subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, is not the insert position Fib object."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( 1 ) != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the insert position Fib object as it's "<<
							"first subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( 2 ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's second subobject."<<endl;
						iReturn++;
					}
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == 1 ){
					if ( pInsertList->getUnderobject( 1 ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the first in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( uiActualListelement - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualSubobject == 1 ){
					if ( 1 < pInsertExtObject->getNumberOfSubobjects() ){
						if ( pInsertExtObject->getSubobject( 1 ) == pFibObjectToInsert ){
							cerr<<"Error: The in the superior external object element inserted "<<
								"Fib object is the first in the external object element."<<endl;
							iReturn++;
						}else{
							cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
							iReturn++;
						}
					}
				}else{
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
					if ( pInsertExtObject->getSubobject( uiActualSubobject - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}
	if ( (pToInsertPositionObject != NULL) && (pFibObjectToInsert != NULL) ){
		cFibElement * pNewAfterInsertPositionObject =
			pToInsertPositionObject->getFibElement(
				uiNumberOfElementsInToInsert + 1 );
		
		if ( pNewAfterInsertPositionObject != pFibObjectToInsert ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted position Fib object has the wrong next Fib element ";
			if ( pNewAfterInsertPositionObject ){
				cerr<<"(number="<<pNewAfterInsertPositionObject->
					getNumberOfElement() <<" and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
	}
	if ( pFibObjectToInsert ){
		cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() + 1 );
		
		if ( (pAfterFibObjectToInsert != NULL) &&
				( pAfterFibObjectToInsert != pNewAfterFibObjectToInsert ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the insert position Fib object has the wrong next Fib element ";
			if ( pNewAfterFibObjectToInsert ){
				cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
					" and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		if ( (pAfterFibObjectToInsert == NULL) &&
				(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be."<<endl;
			iReturn++;
		}
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=true );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectSecondAbsoluteOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated Fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted
	char cTypeInsertObject = choosRandomType();

	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeInsertObject ){
		case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
		break;
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}
	
	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pFibObject->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		uiToInsertPositionObject = uiNumberOfElementsOfType + 1;
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}//else ( pToInsertPositionObject->getSuperiorFibElement() != NULL )
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert       = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	cFibElement * pAfterFibObjectToInsert = NULL;
	unsignedIntFib uiNumberOfElementsInToInsert = 0;
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
		uiNumberOfElementsInToInsert =
			pToInsertPositionObject->getNumberOfElements();
		pAfterFibObjectToInsert = pToInsertPositionObject->getFibElement(
			uiNumberOfElementsInToInsert + 1 );
	}else if ( ( pSuperiorFibObjectToInsert != NULL ) && bCanInsert ){
		//can insert in superior element
		pAfterFibObjectToInsert = pSuperiorFibObjectToInsert->getFibElement(
			pSuperiorFibObjectToInsert->getNumberOfElements() + 1 );
	}
	
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) &&
			( ( pToInsertPositionObject == NULL ) ||
				( pToInsertPositionObject->getType() != 'l' ) ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", false, true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType();
	if ( pToInsertPositionObject ){
		cout<<", insert position type "<<pToInsertPositionObject->getType()<<
			" (nbr.: "<<pToInsertPositionObject->getNumberOfElement()<<")";
	}
	if ( pSuperiorFibObjectToInsert ){
		cout<<", superior to insert position type "<<pSuperiorFibObjectToInsert->getType();
	}
	cout<<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	if ( pFibObjectToInsert ){
		cout<<"   The to insert Fib object has the type "<<
			pFibObjectToInsert->getType() <<" ."<<endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, false, true );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert."<<endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted."<<endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to insert "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
		}
		iReturn++;
		
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}else{
		cout<<"   The Fib object was inserted."<<endl;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
						( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
					( ( pToInsertPositionObject != NULL ) &&
						( pToInsertPositionObject->getType() == 'l' ) ) ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pToInsertPositionObject) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list object element at the insert position ( notBranch( list(...)) )."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = static_cast<cList*>(
				pFibObjectToInsert->getSuperiorFibElement());
			
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( ( ! ( ( pSuperiorFibObjectToInsert->getType() == 'l' ) ||
							( pSuperiorFibObjectToInsert->getType() == 'o' ) ) ) &&
						( ( pToInsertPositionObject != NULL ) &&
							( pToInsertPositionObject->getType() == 'l' ) ) ){
				
					if ( pInsertList->getUnderobject(
							pInsertList->getNumberOfUnderobjects() ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's last subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, is not the insert position Fib object."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( 1 ) != pToInsertPositionObject ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the insert position Fib object as it's "<<
							"first subobject."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( 2 ) != pFibObjectToInsert ){
						cerr<<"Error: The list element, where the Fib object was "<<
							"inserted, hasn't the inserted Fib object as it's second subobject."<<endl;
						iReturn++;
					}
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == 1 ){
					if ( pInsertList->getUnderobject( 1 ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the first in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( uiActualListelement - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject ++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualSubobject == 1 ){
					if ( 1 < pInsertExtObject->getNumberOfSubobjects() ){
						if ( pInsertExtObject->getSubobject( 1 ) == pFibObjectToInsert ){
							cerr<<"Error: The in the superior external object element inserted "<<
								"Fib object is the first in the external object element."<<endl;
							iReturn++;
						}else{
							cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
							iReturn++;
						}
					}
				}else{
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
					if ( pInsertExtObject->getSubobject( uiActualSubobject - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}
	if ( (pToInsertPositionObject != NULL) && (pFibObjectToInsert != NULL) ){
		cFibElement * pNewAfterInsertPositionObject =
			pToInsertPositionObject->getFibElement(
				uiNumberOfElementsInToInsert + 1 );
		
		if (  pNewAfterInsertPositionObject != pFibObjectToInsert ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted position Fib object has the wrong next Fib element ";
			if ( pNewAfterInsertPositionObject ){
				cerr<<"(number="<<pNewAfterInsertPositionObject->
					getNumberOfElement() <<" and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
	}
	if ( pFibObjectToInsert ){
		cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() + 1 );
		
		if ( ( pAfterFibObjectToInsert != NULL ) &&
				( pAfterFibObjectToInsert != pNewAfterFibObjectToInsert ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the insert position Fib object has the wrong next Fib element ";
			if ( pNewAfterFibObjectToInsert ){
				cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
					" and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<"NULL and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		if ( ( pAfterFibObjectToInsert == NULL ) &&
				(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be."<<endl;
			iReturn++;
		}
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}

//TODO check end

#else//FEATURE_INSERT_OBJECT_IN_ELEMENT



/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectFirstOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted

	char cTypeInsertObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeInsertObject );

	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pCallingFibElement->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeInsertObject ){
			case 'u':uiToInsertPositionObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToInsertPositionObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToInsertPositionObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToInsertPositionObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToInsertPositionObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToInsertPositionObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToInsertPositionObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToInsertPositionObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToInsertPositionObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToInsertPositionObject = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToInsertPositionObject = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToInsertPositionObject = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToInsertPositionObject = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = pToInsertPositionObject;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pAfterFibObjectToInsert = pCallingFibElement->getNextFibElement();
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
					pAfterFibObjectToInsert = pToInsertPositionObject;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}else{//( pToInsertPositionObject->getSuperiorFibElement() != NULL )
			if ( pToInsertPositionObject->getSuperiorFibElement()->getType() == 'i' ){
				//can't insert into if-element with all subobjects
				cout<<"Can't insert into if-element with all subobjects."<<endl;
				bCanInsert = false;
			}
		}
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert   = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
	}
	
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<"). "<< endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, true );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert. "<< endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted. "<< endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to insert "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
		}
		iReturn++;
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
				(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = (cList*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( pInsertList->getUnderobject( 1 ) != pFibObjectToInsert ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the inserted Fib object as it's first subobject."<<endl;
					iReturn++;
				}
				if ( pInsertList->getUnderobject( 2 ) != pToInsertPositionObject ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the insert position Fib object as it's "<<
						"second subobject."<<endl;
					iReturn++;
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == pInsertList->getNumberOfUnderobjects() ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the last in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement + 1 ) != pToInsertPositionObject ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( ( uiActualSubobject == pInsertExtObject->getNumberOfSubobjects() ) &&
						( 1 < uiActualSubobject ) ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior external object element inserted "<<
							"Fib object is the last in the external object element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
				}else{
					if ( ( pToInsertPositionObject != NULL ) &&
							( pInsertExtObject->getSubobject( uiActualSubobject + 1 ) != pToInsertPositionObject ) ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}

	if ( ( pToInsertPositionObject != NULL ) &&
			( (pToInsertPositionObject->getType() != 'l') &&
				(pToInsertPositionObject->getType() != 'o') ) &&
			(pToInsertPositionObject != pLastInFibObjectInInsert->getNextFibElement()) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element ";
		if ( pLastInFibObjectInInsert->getNextFibElement() ){
			cerr<<"(number="<<pLastInFibObjectInInsert->getNextFibElement()->
				getNumberOfElement() <<" and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<"). "<< endl;
		}else{
			cerr<<" NULL and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<"). "<< endl;
		}
		iReturn++;
	}
	
	cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
		pFibObjectToInsert->getNumberOfElements() + 1 );
	
	if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
			pNewAfterFibObjectToInsert ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the insert position Fib object has the wrong next Fib element ";
		if ( pNewAfterFibObjectToInsert ){
			cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
				" and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
		}else{
			cerr<<" NULL and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
		}
		iReturn++;
	}
	if ( (pAfterFibObjectToInsert == NULL) &&
			(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element "<<
			"it isn't NULL (has number="<<
			pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
			<<"), but it should be. "<< endl;
		iReturn++;
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=true, bool bAbsolute=true );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectFirstAbsoluteOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted
	char cTypeInsertObject = choosRandomType();

	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeInsertObject ){
		case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
		break;
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}
	
	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pFibObject->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		uiToInsertPositionObject = uiNumberOfElementsOfType + 1;
	}
	if ( uiToInsertPositionObject == 0 ){
		pToInsertPositionObject = pCallingFibElement;
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = pToInsertPositionObject;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pAfterFibObjectToInsert = pCallingFibElement->getNextFibElement();
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
					pAfterFibObjectToInsert = pToInsertPositionObject;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}else{//( pToInsertPositionObject->getSuperiorFibElement() != NULL )
			if ( pToInsertPositionObject->getSuperiorFibElement()->getType() == 'i' ){
				//can't insert into if-element with all subobjects
				cout<<"Can't insert into if-element with all subobjects."<<endl;
				bCanInsert = false;
			}
		}
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert = 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert = 0;
	unsigned int uiNumberOfSetElementsInInsert = 0;
	unsigned int uiNumberOfMatrixElementsInInsert = 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
	}
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", true, true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<"). "<< endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
	}
	if ( pFibObjectToInsert ){
		cout<<"   The to insert fib object has the type "<<
			pFibObjectToInsert->getType() <<" . "<< endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, true, true );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert. "<< endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted. "<< endl;
		iReturn++;
		
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}else{
		cout<<"   The Fib object was inserted. "<< endl;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') )&&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = (cList*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( pInsertList->getUnderobject( 1 ) != pFibObjectToInsert ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the inserted Fib object as it's first subobject."<<endl;
					iReturn++;
				}
				if ( pInsertList->getUnderobject( 2 ) != pToInsertPositionObject ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the insert position Fib object as it's "<<
						"second subobject."<<endl;
					iReturn++;
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement ++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == pInsertList->getNumberOfUnderobjects() ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the last in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement + 1 ) != pToInsertPositionObject ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( ( uiActualSubobject == pInsertExtObject->getNumberOfSubobjects() ) &&
						( 1 < uiActualSubobject ) ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior external object element inserted "<<
							"Fib object is the last in the external object element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
				}else{
					if ( ( pToInsertPositionObject != NULL ) &&
							( pInsertExtObject->getSubobject( uiActualSubobject + 1 ) != pToInsertPositionObject ) ){
						cerr<<"Error: After the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}

	if ( ( pToInsertPositionObject != NULL ) &&
			( (pToInsertPositionObject->getType() != 'l') &&
				(pToInsertPositionObject->getType() != 'o') ) &&
			(pToInsertPositionObject != pLastInFibObjectInInsert->getNextFibElement()) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element ";
		if ( pLastInFibObjectInInsert->getNextFibElement() ){
			cerr<<"(number="<<pLastInFibObjectInInsert->getNextFibElement()->
				getNumberOfElement() <<" and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<"). "<< endl;
		}else{
			cerr<<" NULL and not number="<<
				pToInsertPositionObject->getNumberOfElement() <<"). "<< endl;
		}
		iReturn++;
	}
	
	cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
		pFibObjectToInsert->getNumberOfElements() + 1 );
	
	if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
			pNewAfterFibObjectToInsert ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the insert position Fib object has the wrong next Fib element ";
		if ( pNewAfterFibObjectToInsert ){
			cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
				" and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
		}else{
			cerr<<" NULL and not number="<<
				pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
		}
		iReturn++;
	}
	if ( (pAfterFibObjectToInsert == NULL) &&
			(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", true, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the inserted Fib object has the wrong next Fib element "<<
			"it isn't NULL (has number="<<
			pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
			<<"), but it should be. "<< endl;
		iReturn++;
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=false );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectSecondOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted

	char cTypeInsertObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeInsertObject );

	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pCallingFibElement->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeInsertObject ){
			case 'u':uiToInsertPositionObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToInsertPositionObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToInsertPositionObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToInsertPositionObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToInsertPositionObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToInsertPositionObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToInsertPositionObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToInsertPositionObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToInsertPositionObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToInsertPositionObject = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToInsertPositionObject = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToInsertPositionObject = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToInsertPositionObject = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = pToInsertPositionObject;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pAfterFibObjectToInsert = pCallingFibElement->getNextFibElement();
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
					pAfterFibObjectToInsert = pToInsertPositionObject;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}else{//( pToInsertPositionObject->getSuperiorFibElement() != NULL )
			if ( pToInsertPositionObject->getSuperiorFibElement()->getType() == 'i' ){
				//can't insert into if-element with all subobjects
				cout<<"Can't insert into if-element with all subobjects."<<endl;
				bCanInsert = false;
			}
		}
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert       = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
		pAfterFibObjectToInsert = pToInsertPositionObject->getFibElement(
			pToInsertPositionObject->getNumberOfElements() + 1 );
	}
	
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", false ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<"). "<< endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
	}
	if ( pFibObjectToInsert ){
		cout<<"   The to insert fib object has the type "<<
			pFibObjectToInsert->getType() <<" . "<< endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, false );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert. "<< endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted. "<< endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to insert "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
		}
		iReturn++;
		
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list or external object element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = (cList*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( pInsertList->getUnderobject( 1 ) != pToInsertPositionObject ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the insert position Fib object as it's "<<
						"first subobject."<<endl;
					iReturn++;
				}
				if ( pInsertList->getUnderobject( 2 ) != pFibObjectToInsert ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the inserted Fib object as it's second subobject."<<endl;
					iReturn++;
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == 1 ){
					if ( pInsertList->getUnderobject( 1 ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the first in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( uiActualListelement - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualSubobject == 1 ){
					if ( 1 < pInsertExtObject->getNumberOfSubobjects() ){
						if ( pInsertExtObject->getSubobject( 1 ) == pFibObjectToInsert ){
							cerr<<"Error: The in the superior external object element inserted "<<
								"Fib object is the first in the external object element."<<endl;
							iReturn++;
						}else{
							cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
							iReturn++;
						}
					}
				}else{
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
					if ( pInsertExtObject->getSubobject( uiActualSubobject - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}
	if ( (pToInsertPositionObject != NULL) && (pFibObjectToInsert != NULL) ){
		cFibElement * pNewAfterInsertPositionObject = pToInsertPositionObject->getFibElement(
			pToInsertPositionObject->getNumberOfElements() + 1 );
		
		if (  pNewAfterInsertPositionObject != pFibObjectToInsert ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted position Fib object has the wrong next Fib element ";
			if ( pNewAfterInsertPositionObject ){
				cerr<<"(number="<<pNewAfterInsertPositionObject->
					getNumberOfElement() <<" and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}else{
				cerr<<" NULL and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}
			iReturn++;
		}
	}
	if ( pFibObjectToInsert ){
		cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() + 1 );
		
		if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
				pNewAfterFibObjectToInsert ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the insert position Fib object has the wrong next Fib element ";
			if ( pNewAfterFibObjectToInsert ){
				cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
					" and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}else{
				cerr<<" NULL and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}
			iReturn++;
		}
		if ( (pAfterFibObjectToInsert == NULL) &&
				(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be. "<< endl;
			iReturn++;
		}
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the overwriteObjectWithObject() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertObjectInElement( cFibElement *fibObject, const char cType, const unsignedIntFib elementPoint, bool first=false, bool bAbsolute=true );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testInsertObjectInElementObjectSecondAbsoluteOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );


	const unsigned int uiAverageSubRoots = 1;
	const unsigned int uiAverageSubRootsDepth = 1;
	const unsigned int uiNumberOfAverageInputVariables = 0;
	const unsigned int uiMaxVectorElementNumber = 1023;
	
	//TODO check with variables
	const double dFractionsOfUsedVariables = 0.0;

	cFibElement * pFibObjectToInsert = NULL;
	if ( rand() % 50 != 0 ){
		cFibElement * pGeneratedFibObject = generateFibObject( uiNumberOfAllFibElements / 10 + 10,
			liFractionOfFibElements, liPossiblePropertytyps, uiNumberOfDimensions,
			uiAverageSubRoots, uiAverageSubRootsDepth,
			uiNumberOfAverageInputVariables, dFractionsOfUsedVariables,
			uiMaxVectorElementNumber );
		
		pFibObjectToInsert = pGeneratedFibObject;
		
		if ( rand() % 50 != 0 ){
			//get the next non root-element from the generated fib object
			for ( pFibObjectToInsert = pGeneratedFibObject;
					(pFibObjectToInsert != NULL) && ( pFibObjectToInsert->getType() == 'r' );
					pFibObjectToInsert = pFibObjectToInsert->getNextFibElement() ){
			}
			pFibObjectToInsert = pFibObjectToInsert->copy();
			pGeneratedFibObject->deleteObject();
		}//else check when to insert a root-element
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos a position where the Fib object will be inserted
	char cTypeInsertObject = choosRandomType();

	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeInsertObject ){
		case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
		break;
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}
	
	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pFibObject->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the basis the Fib element."<<endl;
			iReturn++;
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		uiToInsertPositionObject = uiNumberOfElementsOfType + 1;
	}
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pAfterFibObjectToInsert = pToInsertPositionObject;
	bool bCanInsert = true;
	if ( uiToInsertPositionObject == 0 ){
		//insert the object into the selected Fib element
		if ( pCallingFibElement->getType() == 'o' ){
			//insert in a erxternal object element
			cout<<"Insert in an external object element with "<<
				((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects()<<" subobjects."<<endl;
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pAfterFibObjectToInsert = pCallingFibElement->getNextFibElement();
			if ( ((cExtObject*)(pCallingFibElement))->getNumberOfSubobjects() == 0 ){
				pToInsertPositionObject = NULL;
			}else{/*the external object element has subobjects ->
				the first subobject is the insert position*/
				pToInsertPositionObject = pCallingFibElement->getNextFibElement();
			}
		}else{
			cFibElement * pToInsertPositionObjectTmp =
				pCallingFibElement->getNextFibElement();
			
			if ( pToInsertPositionObjectTmp != NULL ){
				if ( pToInsertPositionObjectTmp->getSuperiorFibElement() ==
						pCallingFibElement ){
					/*overwrite the next Fib element/ the subobject of the
					selected Fib element*/
					pToInsertPositionObject = pToInsertPositionObjectTmp;
					pAfterFibObjectToInsert = pToInsertPositionObject;
				}else{
					
					cout<<"Should insert in the Fib element on the position,"<<
						" but it's next Fib element superior isn't the Fib element."<<endl;
					bCanInsert = false;
				}
			}else{
				cout<<"Should insert in the Fib element on the position, but it has no next Fib element."<<endl;
				bCanInsert = false;
			}
		}
	}else{
		if ( pToInsertPositionObject == NULL ){
			cout<<"Can't insert: The to insert position object is NULL."<<endl;
			bCanInsert = false;
		}
	}
	if ( pToInsertPositionObject != NULL ){
		if ( pToInsertPositionObject->getType() == 'r' ){
			cout<<"Can't insert: The to insert position object is wrong an root-element."<<endl;
			bCanInsert = false;
		}else if ( pToInsertPositionObject->getSuperiorFibElement() == NULL ){
			cout<<"Can't insert: The to insert position object has superior NULL."<<endl;
			bCanInsert = false;
		}else{//( pToInsertPositionObject->getSuperiorFibElement() != NULL )
			if ( pToInsertPositionObject->getSuperiorFibElement()->getType() == 'i' ){
				//can't insert into if-element with all subobjects
				cout<<"Can't insert into if-element with all subobjects."<<endl;
				bCanInsert = false;
			}
		}
	}
	
	//evalue the count values of the to insert Fib object
	unsigned int uiNumberOfAllFibElementsInInsert   = 0;
	unsigned int uiNumberOfRootElementsInInsert     = 0;
	unsigned int uiNumberOfPointElementsInInsert    = 0;
	unsigned int uiNumberOfListElementsInInsert     = 0;
	unsigned int uiNumberOfPropertyElementsInInsert = 0;
	unsigned int uiNumberOfAreaElementsInInsert     = 0;
	unsigned int uiNumberOfFunctionElementsInInsert = 0;
	unsigned int uiNumberOfIfElementsInInsert       = 0;
	unsigned int uiNumberOfCommentElementsInInsert  = 0;
	unsigned int uiNumberOfExtObjectElementsInInsert= 0;
	unsigned int uiNumberOfExtSubobjectElementsInInsert= 0;
	unsigned int uiNumberOfSetElementsInInsert= 0;
	unsigned int uiNumberOfMatrixElementsInInsert= 0;
	
	cFibElement * pLastInFibObjectInInsert = NULL;

	if ( pFibObjectToInsert != NULL ){
		uiNumberOfAllFibElementsInInsert =
			pFibObjectToInsert->getNumberOfElements();
		uiNumberOfRootElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'r' );
		uiNumberOfPointElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'p' );
		uiNumberOfListElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'l' );
		uiNumberOfPropertyElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'y' );
		uiNumberOfAreaElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'a' );
		uiNumberOfFunctionElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'f' );
		uiNumberOfIfElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'i' );
		uiNumberOfCommentElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'c' );
		uiNumberOfExtObjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'o' );
		uiNumberOfExtSubobjectElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 's' );
		uiNumberOfSetElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'v' );
		uiNumberOfMatrixElementsInInsert =
			pFibObjectToInsert->getNumberOfElements( 'm' );
			
		//store last Fib element of the insert Fib object
		pLastInFibObjectInInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() );
			
		if ( pFibObjectToInsert->getType() == 'r' ){
			//can't insert a root-element
			cout<<"The to insert object is an root-element."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert object didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult =
		uiNumberOfAllFibElements + uiNumberOfAllFibElementsInInsert;
	const unsigned int uiNumberOfRootElementsOfResult =
		uiNumberOfRootElements + uiNumberOfRootElementsInInsert;
	const unsigned int uiNumberOfPointElementsOfResult =
		uiNumberOfPointElements + uiNumberOfPointElementsInInsert;
	unsigned int uiNumberOfListElementsOfResult =
		uiNumberOfListElements + uiNumberOfListElementsInInsert;
	const unsigned int uiNumberOfPropertyElementsOfResult =
		uiNumberOfPropertyElements + uiNumberOfPropertyElementsInInsert;
	const unsigned int uiNumberOfAreaElementsOfResult =
		uiNumberOfAreaElements + uiNumberOfAreaElementsInInsert;
	const unsigned int uiNumberOfFunctionElementsOfResult =
		uiNumberOfFunctionElements + uiNumberOfFunctionElementsInInsert;
	const unsigned int uiNumberOfIfElementsOfResult =
		uiNumberOfIfElements + uiNumberOfIfElementsInInsert;
	const unsigned int uiNumberOfCommentElementsOfResult =
		uiNumberOfCommentElements + uiNumberOfCommentElementsInInsert;
	const unsigned int uiNumberOfExtObjectElementsOfResult =
		uiNumberOfExtObjectElements + uiNumberOfExtObjectElementsInInsert;
	const unsigned int uiNumberOfExtSubobjectElementsOfResult =
		uiNumberOfExtSubobjectElements + uiNumberOfExtSubobjectElementsInInsert;
	const unsigned int uiNumberOfSetElementsOfResult =
		uiNumberOfSetElements + uiNumberOfSetElementsInInsert;
	const unsigned int uiNumberOfMatrixElementsOfResult =
		uiNumberOfMatrixElements + uiNumberOfMatrixElementsInInsert;
	
	//store the Fib elements betwean which the Fib object will be inserted
	if ( pToInsertPositionObject ){
		pSuperiorFibObjectToInsert =
			pToInsertPositionObject->getSuperiorFibElement();
		pAfterFibObjectToInsert = pToInsertPositionObject->getFibElement(
			pToInsertPositionObject->getNumberOfElements() + 1 );
	}
	
	if ( (pSuperiorFibObjectToInsert != NULL) &&
			( pSuperiorFibObjectToInsert->getType() != 'l' ) &&
			( pSuperiorFibObjectToInsert->getType() != 'o' ) ){
		/*create a new list element to insert at the insert position*/
		uiNumberOfAllFibElementsOfResult++;
		uiNumberOfListElementsOfResult++;
	}

	cout<<"Calling insertObjectInElement("<<
		pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", false, true ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<"). "<< endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
	}
	if ( pFibObjectToInsert ){
		cout<<"   The to insert fib object has the type "<<
			pFibObjectToInsert->getType() <<" . "<< endl;
	}

	const unsigned int pCallingElementNumber =
		pCallingFibElement->getNumberOfElement();
	const char pCallingElementType = pCallingFibElement->getType();
	
	//call insertObjectInElement()
	bool bInserted = pCallingFibElement->insertObjectInElement(
		pFibObjectToInsert, cTypeInsertObject, uiToInsertPositionObject, false, true );

	if ( ! bCanInsert  ){
		if ( bInserted ){
			cerr<<"Error: At the insert Fib element can't be insert,"<<
				" but it was insert. "<< endl;
			iReturn++;
		}else{
			if ( pFibObjectToInsert ){
				pFibObjectToInsert->deleteObject();
			}
		}
		return iReturn;
	}
	if ( ! bInserted ){
		cerr<<"Error: At the insert Fib element couldn't be inserted. "<< endl;
		if ( pSuperiorFibObjectToInsert != NULL ){
			cerr<<"   The superior Fib element of the to insert "<<
				"Fib element is the "<<
				pSuperiorFibObjectToInsert->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToInsert->getType() <<" . "<< endl;
		}
		iReturn++;
		
		if ( pFibObjectToInsert ){
			pFibObjectToInsert->deleteObject();
		}
		return iReturn;
	}else{
		cout<<"   The Fib object was inserted. "<< endl;
	}
	
	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of Fib elements "<< pFibObject->getNumberOfElements() <<
			" isn't correct ("<<uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<" + "<<
			uiNumberOfAllFibElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of root-elements "<< pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<<uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<" + "<<
			uiNumberOfRootElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of point elements "<< pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<<uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<" + "<<
			uiNumberOfPointElementsInInsert <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of list elements "<< pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<<uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<" + "<<
			uiNumberOfListElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of property elements "<< pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<<uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<" + "<<
			uiNumberOfPropertyElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of area elements "<< pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<<uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<" + "<<
			uiNumberOfAreaElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of function elements "<< pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<<uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<" + "<<
			uiNumberOfFunctionElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of if-elements "<< pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<<uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<" + "<<
			uiNumberOfIfElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of comment elements "<< pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<<uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<" + "<<
			uiNumberOfCommentElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external object elements "<< pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<<uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<" + "<<
			uiNumberOfExtObjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of external subobject elements "<< pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<<uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<" + "<<
			uiNumberOfExtSubobjectElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of set elements "<< pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<<uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<" + "<<
			uiNumberOfSetElementsInInsert <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: While calling insertObjectInElement("<<
			pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
			uiToInsertPositionObject<<", false, true ) from the "<<
			pCallingElementNumber<<"'th Fib element "<<
			"(which is of type "<< pCallingElementType <<"), "<<
			"the number of matrix elements "<< pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<<uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<" + "<<
			uiNumberOfMatrixElementsInInsert <<")"<<endl;
		iReturn++;
	}
	
	if ( (pFibObjectToInsert->getSuperiorFibElement() != NULL) &&
			(pSuperiorFibObjectToInsert != NULL) ){
		if ( ( (pSuperiorFibObjectToInsert->getType() == 'l') ||
					(pSuperiorFibObjectToInsert->getType() == 'o') ) &&
				(pFibObjectToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert) ){
			cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
				"list element at the superior insert position."<<endl;
			iReturn++;
		}
		if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'l' ){
			cList * pInsertList = (cList*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'l' ){
				
				if ( pInsertList->getUnderobject( 1 ) != pToInsertPositionObject ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the insert position Fib object as it's "<<
						"first subobject."<<endl;
					iReturn++;
				}
				if ( pInsertList->getUnderobject( 2 ) != pFibObjectToInsert ){
					cerr<<"Error: The list element, where the Fib object was "<<
						"inserted, hasn't the inserted Fib object as it's second subobject."<<endl;
					iReturn++;
				}
			}else{
				unsigned int uiActualListelement;
				for ( uiActualListelement = 1;
						uiActualListelement < pInsertList->getNumberOfUnderobjects();
						uiActualListelement ++ ){
					if ( pInsertList->getUnderobject( uiActualListelement ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualListelement == 1 ){
					if ( pInsertList->getUnderobject( 1 ) == pFibObjectToInsert ){
						cerr<<"Error: The in the superior list element inserted "<<
							"Fib object is the first in the list element."<<endl;
						iReturn++;
					}else{
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
				}else{
					if ( pInsertList->getUnderobject( uiActualListelement ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior list element."<<endl;
						iReturn++;
					}
					if ( pInsertList->getUnderobject( uiActualListelement - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior list element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else if ( pFibObjectToInsert->getSuperiorFibElement()->getType() == 'o' ){
			cExtObject * pInsertExtObject = (cExtObject*)pFibObjectToInsert->getSuperiorFibElement();
			if ( pSuperiorFibObjectToInsert->getType() != 'o' ){
				
				cerr<<"Error: A new external object element was created."<<endl;
				iReturn++;
			}else{
				unsigned int uiActualSubobject;
				for ( uiActualSubobject = 1;
						uiActualSubobject < pInsertExtObject->getNumberOfSubobjects();
						uiActualSubobject ++ ){
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) == pFibObjectToInsert ){
						//inserted Fib object found
						break;
					}
				}
				if ( uiActualSubobject == 1 ){
					if ( 1 < pInsertExtObject->getNumberOfSubobjects() ){
						if ( pInsertExtObject->getSubobject( 1 ) == pFibObjectToInsert ){
							cerr<<"Error: The in the superior external object element inserted "<<
								"Fib object is the first in the external object element."<<endl;
							iReturn++;
						}else{
							cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
							iReturn++;
						}
					}
				}else{
					if ( pInsertExtObject->getSubobject( uiActualSubobject ) != pFibObjectToInsert ){
						cerr<<"Error: The inserted Fib object was not found in the superior external object element."<<endl;
						iReturn++;
					}
					if ( pInsertExtObject->getSubobject( uiActualSubobject - 1 ) != pToInsertPositionObject ){
						cerr<<"Error: Befor the inserted Fib object in the "<<
							"superior external object element isn't the positions Fib element."<<endl;
						iReturn++;
					}
				}
			}
		}else{
			cerr<<"Error: The Fib element wasn't inserted in a list element."<<endl;
			iReturn++;
		}
	}else{
		cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
		iReturn++;
	}
	if ( (pToInsertPositionObject != NULL) && (pFibObjectToInsert != NULL) ){
		cFibElement * pNewAfterInsertPositionObject = pToInsertPositionObject->getFibElement(
			pToInsertPositionObject->getNumberOfElements() + 1 );
		
		if (  pNewAfterInsertPositionObject != pFibObjectToInsert ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted position Fib object has the wrong next Fib element ";
			if ( pNewAfterInsertPositionObject ){
				cerr<<"(number="<<pNewAfterInsertPositionObject->
					getNumberOfElement() <<" and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}else{
				cerr<<" NULL and not number="<<
					pFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}
			iReturn++;
		}
	}
	if ( pFibObjectToInsert ){
		cFibElement * pNewAfterFibObjectToInsert = pFibObjectToInsert->getFibElement(
			pFibObjectToInsert->getNumberOfElements() + 1 );
		
		if ( (pAfterFibObjectToInsert != NULL) && ( pAfterFibObjectToInsert !=
				pNewAfterFibObjectToInsert ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the insert position Fib object has the wrong next Fib element ";
			if ( pNewAfterFibObjectToInsert ){
				cerr<<"(number="<< pNewAfterFibObjectToInsert->getNumberOfElement() <<
					" and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}else{
				cerr<<" NULL and not number="<<
					pAfterFibObjectToInsert->getNumberOfElement() <<"). "<< endl;
			}
			iReturn++;
		}
		if ( (pAfterFibObjectToInsert == NULL) &&
				(pLastInFibObjectInInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: While calling insertObjectInElement("<<
				pFibObjectToInsert <<", "<< cTypeInsertObject<<", "<<
				uiToInsertPositionObject<<", false ) from the "<<
				pCallingElementNumber<<"'th Fib element "<<
				"(which is of type "<< pCallingElementType <<"), "<<
				"the inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pLastInFibObjectInInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be. "<< endl;
			iReturn++;
		}
	}

	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


#endif//FEATURE_INSERT_OBJECT_IN_ELEMENT






/**
 * This function tests the hasUnderAllObjects() method for a given
 * Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool hasUnderAllObjects() const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testHasUnderAllObjectsForLimbOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );

	if ( (uiNumberOfPropertyElements + uiNumberOfAreaElements
			 + uiNumberOfFunctionElements + uiNumberOfCommentElements) == 0 ){
		//no limbelements to remove the subobjects from
		return iReturn;
	}
	//choos a random limbelement
	char cChoosenFibElementType = 'y';
	unsigned int uiNumberOfElementsOfType = 0;
	while ( uiNumberOfElementsOfType == 0 ){
		switch ( rand() % 6 ){
			case 0:
				cChoosenFibElementType = 'y';
				uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 1:
				cChoosenFibElementType = 'a';
				uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 2:
				cChoosenFibElementType = 'f';
				uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 3:
				cChoosenFibElementType = 'c';
				uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 4:
				cChoosenFibElementType = 'v';
				uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 5:
				cChoosenFibElementType = 'm';
				uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
	}
	unsigned int uiChoosenFibElementNumber = (rand() % uiNumberOfElementsOfType) + 1;
	
	cFibLimb * pLimbElement =
		(cFibLimb *)(pFibObject->getFibElement( cChoosenFibElementType, uiChoosenFibElementNumber ) );
	
	if ( pLimbElement == NULL ){
		cerr<<"Error: The "<< uiChoosenFibElementNumber <<
			"'th Fib element of the type "<< cChoosenFibElementType <<
			" couldn't be choosen."<<endl;
		iReturn++;
		return iReturn;
	}
	
	const unsigned int uiElementsInChoosenLimbElement =
		pLimbElement->getNumberOfElements();

	//remove all subobjects from the choosen limbelement
	cFibLimb * pLimbElementCopy = copyFibLimbWithoutStructur( pLimbElement );
	if ( pLimbElementCopy == NULL ){
		cerr<<"Error: Couldn't copy the "<< uiChoosenFibElementNumber <<
			"'th Fib element of the type "<< cChoosenFibElementType <<" ."<<endl;
		iReturn++;
		return iReturn;
	}
	const bool bLimbElementReplaced = pFibObject->overwriteObjectWithObject(
		pLimbElementCopy, cChoosenFibElementType, uiChoosenFibElementNumber );
	
	if ( ! bLimbElementReplaced ){
		cerr<<"Error: Couldn't remove the subobjects of the "<< uiChoosenFibElementNumber <<
			"'th Fib element of the type "<< cChoosenFibElementType <<"."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cout<<"In the "<< uiChoosenFibElementNumber <<"'th Fib element of the type "<<
		cChoosenFibElementType <<" with number "<<
		pLimbElementCopy->getNumberOfElement() <<" the subobject was removed. "<<
		"Checking now hasUnderAllObjects() on some Fib elements in the Fib object."<<endl;
	
	/*test if hasUnderAllObjects() is false for all superior -fib
	-elements of the choosen limb element*/
	set<cFibElement*> setSuperiorElements;
	unsigned int uiHasUnderAllObjectsCalled = 0;
	unsigned int uiHasUnderAllObjectsWasTrue = 0;
	for ( cFibElement * pActualSuperior = pLimbElementCopy;
			pActualSuperior != NULL;
			pActualSuperior = pActualSuperior->getSuperiorFibElement() ){
		
		if ( pActualSuperior->hasUnderAllObjects() ){
			cerr<<"Error: The superior, of the "<< uiChoosenFibElementNumber <<
				"'th Fib element of the type "<< cChoosenFibElementType <<
				" with number "<< pLimbElementCopy->getNumberOfElement() <<
				", with the number "<< pActualSuperior->getNumberOfElement() <<
				" has all subobjects, but it shouldn't."<<endl;
			iReturn++;
		}
		uiHasUnderAllObjectsCalled++;
		setSuperiorElements.insert( pActualSuperior );
	}

	/*choos some random points, if ther are not superior to the choosen limbelement
	hasUnderAllObjects() should be false for them*/
	const unsigned int uiRemainingFibElements = uiNumberOfAllFibElements -
		uiElementsInChoosenLimbElement + 1;
	for ( unsigned int uiIteration = 0;
			uiIteration <= uiNumberOfAllFibElements / 100 + 10; uiIteration++ ){
		
		unsigned int uiChoosenFibElement =
			(rand() % uiRemainingFibElements) + 1;
		
		cFibElement * pChoosenFibElement = NULL;
		pChoosenFibElement =
			pFibObject->getFibElement( uiChoosenFibElement );
		
		if ( pChoosenFibElement == NULL ){
			//skip
			continue;
		}
		
		set<cFibElement*>::iterator itrFoundedElement = find(
			setSuperiorElements.begin(), setSuperiorElements.end(),
			pChoosenFibElement );
		
		if ( itrFoundedElement != setSuperiorElements.end() ){
			/*skip this Fib element, because it's an superior of the
			choosen limbelement*/
			continue;
		}
		if ( ! pChoosenFibElement->hasUnderAllObjects() ){
			cerr<<"Error: The Fib element with number "<<
				 pChoosenFibElement->getNumberOfElement() <<"hasn't all it's subobjects, but "<<
				"it isn't an superior of the "<< uiChoosenFibElementNumber <<
				"'th Fib element of the type "<< cChoosenFibElementType << " ."<<endl;
			iReturn++;
		}
		uiHasUnderAllObjectsWasTrue++;
		uiHasUnderAllObjectsCalled++;
	}
	cout<<"The hasUnderAllObjects() method was called "<< uiHasUnderAllObjectsCalled
		<<" times. It was correctly true "<< uiHasUnderAllObjectsWasTrue<<" times."<<endl;
	
	return iReturn;
}



/**
 * This function tests the insertElement() method for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bCheckVariables if the variable check should be performed, befor
 * 	removing the Fib element
 * @return the number of erros occured in the test
 */
int testInsertElementOnObject( cFibElement * pFibObject, bool bCheckVariables ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	cFibElement * pFibElementToInsert = NULL;
	//char cChoosenFibElementType = 0x00;
	unsigned int uiChoosenFibElementNumber = 0;
	if ( rand() % 50 != 0 ){
		//copy a random limbelement
		uiChoosenFibElementNumber  = (rand() % uiNumberOfAllFibElements) + 1;
		pFibElementToInsert = pFibObject->getFibElement(
			uiChoosenFibElementNumber );
		
		if ( pFibElementToInsert != NULL ){
			pFibElementToInsert = copyFibElementWithoutStructur(
				pFibElementToInsert );
			
			//cChoosenFibElementType = pFibElementToInsert->getType();
		}
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );
	if ( pCallingFibElement == NULL ){
			cerr<<"Error: No calling Fib element with number "<< uiCallingFibElement <<
				" could be found."<<endl;
			iReturn++;
			if ( pFibElementToInsert ){
				delete pFibElementToInsert;
			}
			return iReturn;
	}

	//choos a position where the Fib object will be inserted

	char cTypeInsertObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeInsertObject );

	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		pToInsertPositionObject = pCallingFibElement->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the to insert position."<<endl;
			iReturn++;
			if ( pFibElementToInsert ){
				delete pFibElementToInsert;
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeInsertObject ){
			case 'u':uiToInsertPositionObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToInsertPositionObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToInsertPositionObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToInsertPositionObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToInsertPositionObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToInsertPositionObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToInsertPositionObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToInsertPositionObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToInsertPositionObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToInsertPositionObject = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToInsertPositionObject = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToInsertPositionObject = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToInsertPositionObject = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	bool bCanInsert = true;
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
	unsigned int uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
	unsigned int uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
	unsigned int uiNumberOfListElementsOfResult   = uiNumberOfListElements;
	unsigned int uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
	unsigned int uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
	unsigned int uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
	unsigned int uiNumberOfIfElementsOfResult  = uiNumberOfIfElements;
	unsigned int uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
	unsigned int uiNumberOfExtObjectElementsOfResult  = uiNumberOfExtObjectElements;
	unsigned int uiNumberOfExtSubobjectElementsOfResult = uiNumberOfExtSubobjectElements;
	unsigned int uiNumberOfSetElementsOfResult = uiNumberOfSetElements;
	unsigned int uiNumberOfMatrixElementsOfResult   = uiNumberOfMatrixElements;
	
	//store the Fib elements betwean which the Fib object will be inserted
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pNextFibElementToInsert = NULL;
	if ( pFibElementToInsert != NULL ){
		switch ( pFibElementToInsert->getType() ){
			case 'r':{
				//can't insert a root-element
				cout<<"The to insert Fib element is an root-element."<<endl;
				bCanInsert = false;
			}break;
			case 'l':{
				cout<<"The to insert Fib element is an list element."<<endl;
				bCanInsert = false;
			}break;
			case 'p':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfPointElementsOfResult++;
				cout<<"The to insert Fib element is an point element."<<endl;
			}break;
			case 'y':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfPropertyElementsOfResult++;
				cout<<"The to insert Fib element is an property element."<<endl;
			}break;
			case 'a':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfAreaElementsOfResult++;
				cout<<"The to insert Fib element is an area element."<<endl;
			}break;
			case 'f':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfFunctionElementsOfResult++;
				cout<<"The to insert Fib element is an function element."<<endl;
			}break;
			case 'i':{
				cout<<"The to insert Fib element is an if-element."<<endl;
				bCanInsert = false;
			}break;
			case 'c':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfCommentElementsOfResult++;
				cout<<"The to insert Fib element is an comment element."<<endl;
			}break;
			case 'o':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfExtObjectElementsOfResult++;
				cout<<"The to insert Fib element is an external object element."<<endl;
			}break;
			case 's':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfExtSubobjectElementsOfResult++;
				cout<<"The to insert Fib element is an external subobject element."<<endl;
			}break;
			case 'v':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfSetElementsOfResult++;
				cout<<"The to insert Fib element is an set element."<<endl;
			}break;
			case 'm':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfMatrixElementsOfResult++;
				cout<<"The to insert Fib element is an matrix element."<<endl;
			}break;
		}
		if ( uiToInsertPositionObject == 0 ){
			//insert the object into the selected Fib element
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pNextFibElementToInsert = pCallingFibElement->getNextFibElement();
		}else if ( pToInsertPositionObject ){
			pSuperiorFibObjectToInsert =
				pToInsertPositionObject->getSuperiorFibElement();
			pNextFibElementToInsert = pToInsertPositionObject;
		}
		
		if ( pSuperiorFibObjectToInsert != NULL ){
			if ( pSuperiorFibObjectToInsert->isLeaf() ){
				cout<<"Can't insert in a (superior) leaf element."<<endl;
				bCanInsert = false;
			}
			if ( pFibElementToInsert->isLeaf() ){
				//can insert in point elements in list elements or when insert position is NULL
				if ( (pToInsertPositionObject == NULL) ||
						( (pSuperiorFibObjectToInsert->isBranch()) &&
							(pSuperiorFibObjectToInsert->getType() != 'r') &&
							(pSuperiorFibObjectToInsert->getType() != 'i') ) ){
					
					cout<<"The leaf element can be inserted in Fib element."<<endl;
					pToInsertPositionObject = NULL;
				}else{
					cout<<"The leaf element can't be inserted in Fib element."<<endl;
					bCanInsert = false;
				}
			}else if ( pFibElementToInsert->isLimb() ){
				//can insert limb element as long as ther is an Fib element it can contain
				if ( uiToInsertPositionObject == 0 ){
					//the limb element should contain the next element of the wher to insert element
					pToInsertPositionObject = pSuperiorFibObjectToInsert->getNextFibElement();
				}
				if ( pToInsertPositionObject != NULL ){
					if ( pToInsertPositionObject->getSuperiorFibElement() !=
							pSuperiorFibObjectToInsert ){
						cout<<"Should insert in the limb element on the position,"<<
							" but it's next Fib element superior isn't the Fib element."<<endl;
						bCanInsert = false;
					}
				}else{
					cout<<"Should insert in the limb element on the position, but it has no next Fib element."<<endl;
					bCanInsert = false;
				}
			}else{//is branch element
				if ( uiToInsertPositionObject == 0 ){
					//the branch element should contain the next element of the wher to insert element
					if ( 1 < pSuperiorFibObjectToInsert->getNumberOfElements() ){
						//the Fib element contains other Fib elements
						pToInsertPositionObject = pSuperiorFibObjectToInsert->getNextFibElement();
					}else{
						pToInsertPositionObject = NULL;
					}
				}
			}
		}else{//no Fib element wher to insert
			cout<<"No Fib element wher to insert -> can't insert."<<endl;
			bCanInsert = false;
		}
		if ( ( pToInsertPositionObject != NULL ) &&
				( pToInsertPositionObject->getType() == 'r' ) ){
			cout<<"Can't replace a root element."<<endl;
			bCanInsert = false;
		}
		//check the used variables
		cFibElement * pVariableDefiningPoint = pToInsertPositionObject;
		if ( pVariableDefiningPoint == NULL ){
			pVariableDefiningPoint = pSuperiorFibObjectToInsert;
		}
		if ( bCheckVariables && (pVariableDefiningPoint != NULL) ){
			//check variables
			list<cFibVariable*> liDefinedVariables =
				pVariableDefiningPoint->getDefinedVariables( ED_HIGHER );
			set<cFibVariable*> setUsedVariables =
				pFibElementToInsert->getUsedVariables( ED_POSITION );
			
			for ( set<cFibVariable*>::iterator itrVariable = setUsedVariables.begin();
					itrVariable != setUsedVariables.end(); itrVariable++ ){
				
				const list<cFibVariable*>::iterator itrFoundedVariable = find(
					liDefinedVariables.begin(), liDefinedVariables.end(),
					(*itrVariable) );
				
				if ( itrFoundedVariable == liDefinedVariables.end() ){
					/*variable not found in the defined variables ->
					can't insert the Fib element*/
					bCanInsert = false;
					cout<<"A variable used in the to insert Fib element can't "<<
						"be found defined higher. -> Can't insert the Fib element."<<endl;
					break;
				}
			}
		}
	}else{
		cout<<"The to insert Fib element didn't exists."<<endl;
		bCanInsert = false;
	}
	
	cout<<"Calling insertElement("<<
		pFibElementToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", bAbsolute=false, bCheckVariables="<<
		(bCheckVariables?"true":"false") <<" ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	
	//call insertElement()
	const bool bInserted = pCallingFibElement->insertElement(
		pFibElementToInsert, cTypeInsertObject, uiToInsertPositionObject, false, bCheckVariables );

	if ( bCanInsert  ){
		if ( bInserted ){
			cout<<"Fib element correctly inserted"<<endl;
		}else{
			cerr<<"Error: The insert Fib element couldn't be inserted."<<endl;
			if ( pSuperiorFibObjectToInsert != NULL ){
				cerr<<"   The superior Fib element of the to insert "<<
					"Fib element is the "<<
					pSuperiorFibObjectToInsert->getNumberOfElement() <<
					"'th Fib element with the type "<<
					pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
			}
			iReturn++;
		}
	}else{
		if ( bInserted ){
			cerr<<"Error: The insert Fib element can't be insert,"<<
				" but it was insert."<<endl;
			iReturn++;
		}else{
			cout<<"Fib element correctly not inserted"<<endl;
		}
	}
	if ( bInserted ){
		if ( (pFibElementToInsert->getSuperiorFibElement() != NULL) &&
				(pSuperiorFibObjectToInsert != NULL) ){
			if ( pFibElementToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert ){
				cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
					"Fib element at the superior insert position."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
			iReturn++;
		}
	
		if (  pNextFibElementToInsert != pFibElementToInsert->getNextFibElement() ){
			cerr<<"Error: The inserted Fib object has the wrong next Fib element ";
			if ( pFibElementToInsert->getNextFibElement() ){
				cerr<<"(number="<<pFibElementToInsert->getNextFibElement()->
					getNumberOfElement() <<" and not number="<<
					pNextFibElementToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pNextFibElementToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		
		if ( (pNextFibElementToInsert == NULL) &&
				(pFibElementToInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: The inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pFibElementToInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be NULL."<<endl;
			iReturn++;
		}
	}else{
		uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
		uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
		uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
		uiNumberOfListElementsOfResult   = uiNumberOfListElements;
		uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
		uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
		uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
		uiNumberOfIfElementsOfResult     = uiNumberOfIfElements;
		uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
		uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
		uiNumberOfExtSubobjectElementsOfResult= uiNumberOfExtSubobjectElements;
		uiNumberOfSetElementsOfResult    = uiNumberOfSetElements;
		uiNumberOfMatrixElementsOfResult = uiNumberOfMatrixElements;
		if ( pFibElementToInsert ){
			delete pFibElementToInsert;
		}
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}



/**
 * This function tests the insertElement() method for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bCheckVariables if the variable check should be performed, befor
 * 	removing the Fib element
 * @return the number of erros occured in the test
 */
int testInsertElementAbsoluteOnObject( cFibElement * pFibObject, bool bCheckVariables ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	cFibElement * pFibElementToInsert = NULL;
	//char cChoosenFibElementType = 0x00;
	unsigned int uiChoosenFibElementNumber = 0;
	if ( rand() % 50 != 0 ){
		//copy a random limbelement
		uiChoosenFibElementNumber  = (rand() % uiNumberOfAllFibElements) + 1;
		pFibElementToInsert = pFibObject->getFibElement(
			uiChoosenFibElementNumber );
		
		if ( pFibElementToInsert != NULL ){
			pFibElementToInsert = copyFibElementWithoutStructur(
				pFibElementToInsert );
			
			//cChoosenFibElementType = pFibElementToInsert->getType();
		}
	}//else check when return is false when pFibObjectToInsert==NULL
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cout<<"Choosen for calling element is the "<<uiCallingFibElement<<" Fib element."<<flush<<endl;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );
	if ( pCallingFibElement == NULL ){
			cerr<<"Error: No calling Fib element with number "<< uiCallingFibElement <<
				" could be found."<<endl;
			iReturn++;
			if ( pFibElementToInsert ){
				delete pFibElementToInsert;
			}
			return iReturn;
	}

	//choos a position where the Fib object will be inserted

	char cTypeInsertObject = choosRandomType();
	unsigned int uiNumberOfElementsOfType = 0;
	switch ( cTypeInsertObject ){
		case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
		break;
		case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
		break;
		case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
		break;
		case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
		break;
		case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
		break;
		case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
		break;
		case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
		break;
		case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
		break;
		case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
		break;
		case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
		break;
		case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
		break;
		case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
		break;
	}

	unsigned int uiToInsertPositionObject = 0;
	
	cFibElement * pToInsertPositionObject = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToInsertPositionObject = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToInsertPositionObject = 0;
		}
		cout<<"The insert position element is the "<<uiToInsertPositionObject<<
			" Fib element of type "<<cTypeInsertObject<<"."<<flush<<endl;
		pToInsertPositionObject = pFibObject->getFibElement(
				cTypeInsertObject, uiToInsertPositionObject );
		//check the getType() methode from cList
		if ( pToInsertPositionObject == NULL ){
			cerr<<"Error: The "<< uiToInsertPositionObject <<
				"'th Fib element from the Fib object couldn't be choosen "<<
				"as the to insert position."<<endl;
			iReturn++;
			if ( pFibElementToInsert ){
				delete pFibElementToInsert;
			}
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		cout<<"The insert position element is a non existing ( the"<<uiToInsertPositionObject<<
			") Fib element of type "<<cTypeInsertObject<<"."<<flush<<endl;
		switch ( cTypeInsertObject ){
			case 'u':uiToInsertPositionObject = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToInsertPositionObject = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToInsertPositionObject = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToInsertPositionObject = uiNumberOfListElements + 1;
			break;
			case 'y':uiToInsertPositionObject = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToInsertPositionObject = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToInsertPositionObject = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToInsertPositionObject = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToInsertPositionObject = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToInsertPositionObject = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToInsertPositionObject = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToInsertPositionObject = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToInsertPositionObject = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	bool bCanInsert = true;
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
	unsigned int uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
	unsigned int uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
	unsigned int uiNumberOfListElementsOfResult   = uiNumberOfListElements;
	unsigned int uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
	unsigned int uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
	unsigned int uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
	unsigned int uiNumberOfIfElementsOfResult     = uiNumberOfIfElements;
	unsigned int uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
	unsigned int uiNumberOfExtObjectElementsOfResult  = uiNumberOfExtObjectElements;
	unsigned int uiNumberOfExtSubobjectElementsOfResult  = uiNumberOfExtSubobjectElements;
	unsigned int uiNumberOfSetElementsOfResult  = uiNumberOfSetElements;
	unsigned int uiNumberOfMatrixElementsOfResult  = uiNumberOfMatrixElements;
	
	cFibElement * pSuperiorFibObjectToInsert = NULL;
	cFibElement * pNextFibElementToInsert = NULL;
	if ( pFibElementToInsert != NULL ){
		switch ( pFibElementToInsert->getType() ){
			case 'r':{
				//can't insert a root-element
				cout<<"The to insert Fib element is an root-element."<<flush<<endl;
				bCanInsert = false;
			}break;
			case 'l':{
				cout<<"The to insert Fib element is an list element."<<flush<<endl;
				bCanInsert = false;
			}break;
			case 'p':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfPointElementsOfResult++;
				cout<<"The to insert Fib element is an point element."<<flush<<endl;
			}break;
			case 'y':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfPropertyElementsOfResult++;
				cout<<"The to insert Fib element is an property element."<<flush<<endl;
			}break;
			case 'a':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfAreaElementsOfResult++;
				cout<<"The to insert Fib element is an area element."<<flush<<endl;
			}break;
			case 'f':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfFunctionElementsOfResult++;
				cout<<"The to insert Fib element is an function element."<<flush<<endl;
			}break;
			case 'i':{
				cout<<"The to insert Fib element is an if-element."<<flush<<endl;
				bCanInsert = false;
			}break;
			case 'c':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfCommentElementsOfResult++;
				cout<<"The to insert Fib element is an comment element."<<flush<<endl;
			}break;
			case 'o':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfExtObjectElementsOfResult++;
				cout<<"The to insert Fib element is an external object element."<<flush<<endl;
			}break;
			case 's':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfExtSubobjectElementsOfResult++;
				cout<<"The to insert Fib element is an external subobject element."<<flush<<endl;
			}break;
			case 'v':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfSetElementsOfResult++;
				cout<<"The to insert Fib element is an set element."<<flush<<endl;
			}break;
			case 'm':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfMatrixElementsOfResult++;
				cout<<"The to insert Fib element is an matrix element."<<flush<<endl;
			}break;
		}
		if ( uiToInsertPositionObject == 0 ){
			//insert the object into the selected Fib element
			pSuperiorFibObjectToInsert = pCallingFibElement;
			pNextFibElementToInsert = pCallingFibElement->getNextFibElement();
		}else if ( pToInsertPositionObject ){
			pSuperiorFibObjectToInsert =
				pToInsertPositionObject->getSuperiorFibElement();
			pNextFibElementToInsert = pToInsertPositionObject;
		}
		
		if ( pSuperiorFibObjectToInsert != NULL ){
			if ( pSuperiorFibObjectToInsert->isLeaf() ){
				cout<<"Can't insert in a (superior) leaf element."<<endl;
				bCanInsert = false;
			}
			if ( pFibElementToInsert->isLeaf() ){
				//can insert in point elements in list elements or when insert position is NULL
				if ( (pToInsertPositionObject == NULL) ||
						( (pSuperiorFibObjectToInsert->isBranch()) &&
							(pSuperiorFibObjectToInsert->getType() != 'r') &&
							(pSuperiorFibObjectToInsert->getType() != 'i') ) ){
					
					cout<<"The leaf element can be inserted in Fib element."<<endl;
					pToInsertPositionObject = NULL;
				}else{
					cout<<"The leaf element can't be inserted in Fib element."<<endl;
					bCanInsert = false;
				}
			}else if ( pFibElementToInsert->isLimb() ){
				//can insert limb element as long as ther is an Fib element it can contain
				if ( uiToInsertPositionObject == 0 ){
					//the limb element should contain the next element of the wher to insert element
					pToInsertPositionObject = pSuperiorFibObjectToInsert->getNextFibElement();
				}
				if ( pToInsertPositionObject != NULL ){
					if ( pToInsertPositionObject->getSuperiorFibElement() !=
							pSuperiorFibObjectToInsert ){
						cout<<"Should insert in the limb element on the position,"<<
							" but it's next Fib element superior isn't the Fib element."<<endl;
						bCanInsert = false;
					}
				}else{
					cout<<"Should insert in the limb element on the position, but it has no next Fib element."<<endl;
					bCanInsert = false;
				}
			}else{//is branch element
				if ( uiToInsertPositionObject == 0 ){
					//the branch element should contain the next element of the wher to insert element
					if ( 1 < pSuperiorFibObjectToInsert->getNumberOfElements() ){
						//the Fib element contains other Fib elements
						pToInsertPositionObject = pSuperiorFibObjectToInsert->getNextFibElement();
					}else{
						pToInsertPositionObject = NULL;
					}
				}
			}
		}else{//no Fib element wher to insert
			cout<<"No Fib element wher to insert -> can't insert."<<endl;
			bCanInsert = false;
		}
		
		if ( ( pToInsertPositionObject != NULL ) &&
				( pToInsertPositionObject->getType() == 'r' ) ){
			cout<<"Can't replace a root element."<<endl;
			bCanInsert = false;
		}
		//check the used variables
		cFibElement * pVariableDefiningPoint = pToInsertPositionObject;
		if ( pVariableDefiningPoint == NULL ){
			pVariableDefiningPoint = pSuperiorFibObjectToInsert;
		}
		if ( bCheckVariables && (pVariableDefiningPoint != NULL) ){
			//check variables
			list<cFibVariable*> liDefinedVariables =
				pVariableDefiningPoint->getDefinedVariables( ED_HIGHER );
			set<cFibVariable*> setUsedVariables =
				pFibElementToInsert->getUsedVariables( ED_POSITION );
			
			for ( set<cFibVariable*>::iterator itrVariable = setUsedVariables.begin();
					itrVariable != setUsedVariables.end(); itrVariable++ ){
				
				const list<cFibVariable*>::iterator itrFoundedVariable = find(
					liDefinedVariables.begin(), liDefinedVariables.end(),
					(*itrVariable) );
				
				if ( itrFoundedVariable == liDefinedVariables.end() ){
					/*variable not found in the defined variables ->
					can't insert the Fib element*/
					bCanInsert = false;
					cout<<"A variable used in the to insert Fib element can't "<<
						"be found defined higher. -> Can't insert the Fib element."<<endl;
					break;
				}
			}
		}
	}else{
		cout<<"The to insert Fib element didn't exists."<<endl;
		bCanInsert = false;
	}

	cout<<"Calling insertElement("<<
		pFibElementToInsert <<", "<< cTypeInsertObject<<", "<<
		uiToInsertPositionObject<<", bAbsolute=true, bCheckVariables="<<
		(bCheckVariables?"true":"false") <<" ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
	if ( pSuperiorFibObjectToInsert != NULL ){
		cout<<"   The superior Fib element of the to insert "<<
			"Fib element is the "<<
			pSuperiorFibObjectToInsert->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
	}
	
	//call insertElement()
	const bool bInserted = pCallingFibElement->insertElement(
		pFibElementToInsert, cTypeInsertObject, uiToInsertPositionObject, true, bCheckVariables );

	if ( bCanInsert ){
		if ( bInserted ){
			cout<<"Fib element correctly inserted"<<endl<<flush;
		}else{
			cerr<<"Error: At the insert position the Fib element couldn't be inserted. "<< endl<<flush;
			if ( pSuperiorFibObjectToInsert != NULL ){
				cerr<<"   The superior Fib element of the to insert "<<
					"Fib element is the "<<
					pSuperiorFibObjectToInsert->getNumberOfElement() <<
					"'th Fib element with the type "<<
					pSuperiorFibObjectToInsert->getType() <<" ."<<endl;
			}
			iReturn++;
		}
	}else{
		if ( bInserted ){
			cerr<<"Error: At the insert position the Fib element can't be insert,"<<
				" but it was insert. "<< endl<<flush;
			iReturn++;
		}else{
			cout<<"Fib element correctly not inserted"<<endl<<flush;
		}
	}
	if ( bInserted ){
		if ( (pFibElementToInsert->getSuperiorFibElement() != NULL) &&
				(pSuperiorFibObjectToInsert != NULL) ){
			if ( pFibElementToInsert->getSuperiorFibElement() != pSuperiorFibObjectToInsert ){
				cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
					"Fib element at the superior insert position."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
			iReturn++;
		}
	
		if (  pNextFibElementToInsert != pFibElementToInsert->getNextFibElement() ){
			cerr<<"Error: The inserted Fib object has the wrong next Fib element ";
			if ( pFibElementToInsert->getNextFibElement() ){
				cerr<<"(number="<<pFibElementToInsert->getNextFibElement()->
					getNumberOfElement() <<" and not number="<<
					pNextFibElementToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pNextFibElementToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		
		if ( (pNextFibElementToInsert == NULL) &&
				(pFibElementToInsert->getNextFibElement() != NULL ) ){
			cerr<<"Error: The inserted Fib object has the wrong next Fib element "<<
				"it isn't NULL (has number="<<
				pFibElementToInsert->getNextFibElement()->getNumberOfElement()
				<<"), but it should be NULL."<<endl;
			iReturn++;
		}
	}else{
		uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
		uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
		uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
		uiNumberOfListElementsOfResult   = uiNumberOfListElements;
		uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
		uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
		uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
		uiNumberOfIfElementsOfResult = uiNumberOfIfElements;
		uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
		uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
		uiNumberOfExtSubobjectElementsOfResult= uiNumberOfExtSubobjectElements;
		uiNumberOfSetElementsOfResult= uiNumberOfSetElements;
		uiNumberOfMatrixElementsOfResult   = uiNumberOfMatrixElements;
		
		if ( pFibElementToInsert ){
			delete pFibElementToInsert;
		}
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error:The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if-elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}


/**
 * This function tests the insertElement() method for a given Fib object.
 * The subobject to overwrite will be NULL.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool insertElement( cFibElement *fibElement, const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bCheckVariables if the variable check should be performed, befor
 * 	removing the Fib element
 * @return the number of erros occured in the test
 */
int testInsertElementNullOnObject( cFibElement * pFibObject, bool bCheckVariables ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//replace the Fib object where the Fib element should be inserted with 0
	//evalue the count values of the given Fib object
	unsigned int uiNumberOfAllFibElements = pFibObject->getNumberOfElements();

	if ( uiNumberOfAllFibElements == 0 ){
		//no limbelements to remove the subobjects from
		return iReturn;
	}
	//choos a random limbelement
	unsigned int uiChoosenFibElementNumber = 0;
	cFibElement * pFibElement = NULL;
	unsigned int uiIteration = 0;
	unsigned int uiMaxIteration = ((uiNumberOfAllFibElements < 1000) ?
		uiNumberOfAllFibElements : 1000 );
	do{
		uiChoosenFibElementNumber = (rand() % uiNumberOfAllFibElements) + 1;
		pFibElement = pFibObject->getFibElement( uiChoosenFibElementNumber );
		
		if ( pFibElement == NULL ){
			cerr<<"Error: The "<< uiChoosenFibElementNumber <<
				"'th Fib element couldn't be choosen."<<endl;
			iReturn++;
			return iReturn;
		}
		uiIteration++;
	}while ( ((pFibElement->getType() == 'r') || (pFibElement->isLeaf())) &&
		(uiIteration < uiMaxIteration) );
	
	if (pFibElement->getType() == 'r'){
		//skip because overwriteObjectWithObject() wouldn't work
		return iReturn;
	}
	if ( pFibElement->isLeaf() ){
		//skip because insertElement() wouldn't work
		return iReturn;
	}

	//remove all subobjects from the choosen limbelement
	cFibElement * pFibElementCopy = copyFibElementWithoutStructur( pFibElement );
	if ( pFibElementCopy == NULL ){
		cerr<<"Error: Couldn't copy the."<<endl;
		iReturn++;
		return iReturn;
	}
	const bool bFibElementReplaced = pFibObject->overwriteObjectWithObject(
		pFibElementCopy, 'u', uiChoosenFibElementNumber );
	
	if ( ! bFibElementReplaced ){
		cerr<<"Error: Couldn't remove the subobjects of the "<< uiChoosenFibElementNumber <<
			"'th Fib element."<<endl;
		iReturn++;
		return iReturn;
	}

	//evalue the count values of the given Fib object
	uiNumberOfAllFibElements = pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	cFibElement * pFibElementToInsert = NULL;
	//char cChoosenFibElementType = 0x00;
	uiChoosenFibElementNumber = 0;
	if ( rand() % 50 != 0 ){
		//copy a random Fib element
		uiChoosenFibElementNumber  = (rand() % uiNumberOfAllFibElements) + 1;
		pFibElementToInsert = pFibObject->getFibElement(
			uiChoosenFibElementNumber );
		
		if ( pFibElementToInsert != NULL ){
			pFibElementToInsert = copyFibElementWithoutStructur(
				pFibElementToInsert );
			
			//cChoosenFibElementType = pFibElementToInsert->getType();
		}
	}//else check when return is false when pFibObjectToInsert==NULL

	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
	unsigned int uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
	unsigned int uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
	unsigned int uiNumberOfListElementsOfResult   = uiNumberOfListElements;
	unsigned int uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
	unsigned int uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
	unsigned int uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
	unsigned int uiNumberOfIfElementsOfResult = uiNumberOfIfElements;
	unsigned int uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
	unsigned int uiNumberOfExtObjectElementsOfResult  = uiNumberOfExtObjectElements;
	unsigned int uiNumberOfExtSubobjectElementsOfResult  = uiNumberOfExtSubobjectElements;
	unsigned int uiNumberOfSetElementsOfResult  = uiNumberOfSetElements;
	unsigned int uiNumberOfMatrixElementsOfResult  = uiNumberOfMatrixElements;
	
	bool bCanInsert = true;
	if ( pFibElementToInsert != NULL ){
		switch ( pFibElementToInsert->getType() ){
			case 'r':{
				//can't insert a root-element
				cout<<"The to insert Fib element is an root-element. (can't insert it)"<<endl;
				bCanInsert = false;
			}break;
			case 'l':{
				cout<<"The to insert Fib element is an list element. (can't insert it)"<<endl;
				bCanInsert = false;
			}break;
			case 'p':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfPointElementsOfResult++;
				cout<<"The to insert Fib element is an point element."<<endl;
			}break;
			case 'y':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfPropertyElementsOfResult++;
				cout<<"The to insert Fib element is an property element."<<endl;
			}break;
			case 'a':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfAreaElementsOfResult++;
				cout<<"The to insert Fib element is an area element."<<endl;
			}break;
			case 'f':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfFunctionElementsOfResult++;
				cout<<"The to insert Fib element is an function element."<<endl;
			}break;
			case 'i':{
				cout<<"The to insert Fib element is an if-element. (can't insert it)"<<endl;
				bCanInsert = false;
			}break;
			case 'c':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfCommentElementsOfResult++;
				cout<<"The to insert Fib element is an comment element."<<endl;
			}break;
			case 'o':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfExtObjectElementsOfResult++;
				cout<<"The to insert Fib element is an external object element."<<endl;
			}break;
			case 's':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfExtSubobjectElementsOfResult++;
				cout<<"The to insert Fib element is an external subobject element."<<endl;
			}break;
			case 'v':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfSetElementsOfResult++;
				cout<<"The to insert Fib element is an set element."<<endl;
			}break;
			case 'm':{
				uiNumberOfAllFibElementsOfResult++;
				uiNumberOfMatrixElementsOfResult++;
				cout<<"The to insert Fib element is an matrix element."<<endl;
			}break;
		}
		if ( bCheckVariables && (pFibElementCopy != NULL) ){
			//check variables
			list<cFibVariable*> liDefinedVariables =
				pFibElementCopy->getDefinedVariables( ED_HIGHER );
			set<cFibVariable*> setUsedVariables =
				pFibElementToInsert->getUsedVariables( ED_POSITION );
			
			for ( set<cFibVariable*>::iterator itrVariable = setUsedVariables.begin();
					itrVariable != setUsedVariables.end(); itrVariable++ ){
				
				const list<cFibVariable*>::iterator itrFoundedVariable = find(
					liDefinedVariables.begin(), liDefinedVariables.end(),
					(*itrVariable) );
				
				if ( itrFoundedVariable == liDefinedVariables.end() ){
					/*variable not found in the defined variables ->
					can't insert the Fib element*/
					bCanInsert = false;
					cout<<"A variable used in the to insert Fib element can't "<<
						"be found defined higher. -> Can't insert the Fib element."<<endl;
					break;
				}
			}
		}
		if ( ( pFibElementCopy->getType() == 'o' ) &&
				( ! pFibElementToInsert->isLeaf() ) &&
				( pFibElementToInsert->getType() != 'o' ) ){
			//don't make external object element invalid
			cout<<"Can't insert a non leaf into an external object element. "<<
				"It would become invalid."<<endl;
			bCanInsert = false;
		}
	}else{
		cout<<"The to insert Fib element didn't exists."<<endl;
		bCanInsert = false;
	}
	
	//store the Fib elements betwean which the Fib object will be inserted
	cFibElement * pNextFibObjectToInsert = NULL;
	if ( pFibElementCopy ){
		pNextFibObjectToInsert = pFibElementCopy->getNextFibElement();
	}
	char cTypeInsertPosition = 'u';
	if ( rand() % 2 == 1 ){
		cTypeInsertPosition = choosRandomType();
	}else{
		cTypeInsertPosition = 'u';
	}
	cout<<"Calling insertElement("<<
		pFibElementToInsert <<", "<< cTypeInsertPosition <<", 0, false, bCheckVariables="<<
		(bCheckVariables?"true":"false") << ") from the "<<
		pFibElementCopy->getNumberOfElement()<<"'th Fib element, "<<
		"wich has type "<< pFibElementCopy->getType() <<" and has no subobjects."<<endl;
	
	//call insertElement()
	const bool bInserted = pFibElementCopy->insertElement(
		pFibElementToInsert, cTypeInsertPosition, 0, false, bCheckVariables );

	if ( bCanInsert  ){
		if ( bInserted ){
			cout<<"Fib element correctly inserted"<<endl;
		}else{
			cerr<<"Error: At the insert position the Fib element couldn't be inserted."<<endl;
			iReturn++;
		}
	}else{
		if ( bInserted ){
			cerr<<"Error: At the insert position the Fib element can't be insert,"<<
				" but it was insert."<<endl;
			iReturn++;
		}else{
			cout<<"Fib element correctly not inserted"<<endl;
		}
	}
	if ( bInserted ){
		if ( pFibElementToInsert->getSuperiorFibElement() != NULL ){
			if ( pFibElementToInsert->getSuperiorFibElement() != pFibElementCopy ){
				cerr<<"Error: The inserted Fib element wasn't inserted in the "<<
					"Fib element at the superior insert position."<<endl;
				iReturn++;
			}
		}else{
			cerr<<"Error: The superior Fib element of the inserted Fib element is NULL."<<endl;
			iReturn++;
		}
	
		if ( pFibElementCopy->getNextFibElement() != pFibElementToInsert ){
			cerr<<"Error: The insert position Fib object has the wrong next Fib element. ";
			if ( pFibElementCopy->getNextFibElement() ){
				cerr<<"(number="<< pFibElementCopy->getNextFibElement()->
					getNumberOfElement() <<" and not number="<<
					pFibElementToInsert->getNumberOfElement() <<")."<<endl;
			}else{
				cerr<<" NULL and not number="<<
					pFibElementToInsert->getNumberOfElement() <<")."<<endl;
			}
			iReturn++;
		}
		
		if ( pFibElementToInsert->getNextFibElement() != pNextFibObjectToInsert ){
			cerr<<"Error: The inserted Fib object has the wrong next Fib element ";
			if ( pFibElementToInsert->getNextFibElement() != NULL ){
				cerr<<"it is "<< pFibElementToInsert->getNextFibElement()->getNumberOfElement()<<"."<<endl;
			}else{
				cerr<<"it is NULL."<<endl;
			}
			iReturn++;
		}
	}else{
		uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
		uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
		uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
		uiNumberOfListElementsOfResult   = uiNumberOfListElements;
		uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
		uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
		uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
		uiNumberOfIfElementsOfResult     = uiNumberOfIfElements;
		uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
		uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
		uiNumberOfExtSubobjectElementsOfResult= uiNumberOfExtSubobjectElements;
		uiNumberOfSetElementsOfResult    = uiNumberOfSetElements;
		uiNumberOfMatrixElementsOfResult = uiNumberOfMatrixElements;
		
		if ( pFibElementToInsert ){
			delete pFibElementToInsert;
		}
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error:The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if-elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	
	return iReturn;
}



/**
 * This function tests the methods for removing or cutting a Fib element
 * from a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool isRemovableElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables ) const;
 * 	- bool removeElement(  const char cType, const unsignedIntFib  elementPoint, bool bAbsolute=false, bool bCheckVariables );
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=false, bool bCheckVariables );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bCut if true the cutElement() method will be tested, else the
 * 	removeElement() method
 * @param bCheckVariables if the variable check should be performed, befor
 * 	removing the Fib element
 * @return the number of erros occured in the test
 */
int testRemoveElementOnObject( cFibElement * pFibObject, bool bCut, bool bCheckVariables ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos the Fib element which will be removed
	char cTypeRemoveElement = choosRandomType();
	unsigned int uiNumberOfElementsOfType = pCallingFibElement->
		getNumberOfElements( cTypeRemoveElement );

	unsigned int uiToRemoveFibElement = 0;
	
	cFibElement * pToRemoveFibElement = NULL;
	if ( rand() % 50 != 0 ){
		if ( uiNumberOfElementsOfType != 0 ){
			uiToRemoveFibElement = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToRemoveFibElement = 0;
		}
		pToRemoveFibElement = pCallingFibElement->getFibElement(
				cTypeRemoveElement, uiToRemoveFibElement );
		//check the getType() methode from cList
		if ( pToRemoveFibElement == NULL ){
			cerr<<"Error: The "<< uiToRemoveFibElement <<
				"'th Fib element from the calling Fib element of the "<<
				"Fib object couldn't be choosen as the to remove position."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeRemoveElement ){
			case 'u':uiToRemoveFibElement = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToRemoveFibElement = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToRemoveFibElement = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToRemoveFibElement = uiNumberOfListElements + 1;
			break;
			case 'y':uiToRemoveFibElement = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToRemoveFibElement = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToRemoveFibElement = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToRemoveFibElement = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToRemoveFibElement = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToRemoveFibElement = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToRemoveFibElement = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToRemoveFibElement = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToRemoveFibElement = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	bool bCanRemove = true;
	if ( (pToRemoveFibElement == NULL) ||
			(pToRemoveFibElement->getType() == 'r') ||
			(pToRemoveFibElement->getSuperiorFibElement() == NULL) ){
		bCanRemove = false;
	}
	unsigned int uiNumberOfToRemoveElement = 0;
	
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
	unsigned int uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
	unsigned int uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
	unsigned int uiNumberOfListElementsOfResult   = uiNumberOfListElements;
	unsigned int uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
	unsigned int uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
	unsigned int uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
	unsigned int uiNumberOfIfElementsOfResult       = uiNumberOfIfElements;
	unsigned int uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
	unsigned int uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
	unsigned int uiNumberOfExtSubobjectElementsOfResult= uiNumberOfExtSubobjectElements;
	unsigned int uiNumberOfSetElementsOfResult    = uiNumberOfSetElements;
	unsigned int uiNumberOfMatrixElementsOfResult   = uiNumberOfMatrixElements;
	
	//store the Fib elements betwean which the Fib object will be removed
	cFibElement * pSuperiorFibObjectToRemove = NULL;
	cFibElement * pSubobjectOfToRemove = NULL;
	char cCorrectTypeOfToRemove = 'u';

	if ( pToRemoveFibElement != NULL ){
		
		pSuperiorFibObjectToRemove =
			pToRemoveFibElement->getSuperiorFibElement();
		pSubobjectOfToRemove =
			pToRemoveFibElement->getNextFibElement();
		
		cCorrectTypeOfToRemove = pToRemoveFibElement->getType();
		
		switch ( cCorrectTypeOfToRemove ){
			case 'r':{
				//can't remove a root-element
				cout<<"The to remove Fib element is an root-element."<<endl;
				bCanRemove = false;
			}break;
			case 'l':{
				cout<<"The to remove Fib element is an list element."<<endl;
				bCanRemove = false;
			}break;
			case 'p':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfPointElementsOfResult--;
				cout<<"The to remove Fib element is an point element."<<endl;
				bCanRemove = false;
			}break;
			case 'y':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfPropertyElementsOfResult--;
				cout<<"The to remove Fib element is an property element."<<endl;
			}break;
			case 'a':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfAreaElementsOfResult--;
				cout<<"The to remove Fib element is an area element."<<endl;
			}break;
			case 'f':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfFunctionElementsOfResult--;
				cout<<"The to remove Fib element is an function element."<<endl;
			}break;
			case 'i':{
				cout<<"The to remove Fib element is an if-element."<<endl;
				bCanRemove = false;
			}break;
			case 'c':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfCommentElementsOfResult--;
				cout<<"The to remove Fib element is an comment element."<<endl;
			}break;
			case 'o':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfExtObjectElementsOfResult--;
				
				const unsignedIntFib uiNumberOfSubobjects =
					((cExtObject*)(pToRemoveFibElement))->getNumberOfSubobjects();
				
				cout<<"The to remove Fib element is an external object element with "<<
					uiNumberOfSubobjects<<" subobjects."<<endl;
				
				if ( 2 <= uiNumberOfSubobjects ){
					//external object element can't be replaced be its more than 1 subobjects
					bCanRemove = false;
				}else if ( uiNumberOfSubobjects == 0 ){
					//external object element has no subobjects
					pSubobjectOfToRemove = NULL;
					
					const char cTypeSuperiorToRemove =
						pSuperiorFibObjectToRemove->getType();
					
					if ( cTypeSuperiorToRemove != 'o' ){
						
						if ( cTypeSuperiorToRemove == 'l' ){
							/*can remove if the list element has more than 2
							subobjects left after removing*/
							cout<<"The superior to the to remove Fib element is a list element with "<<
								((cList*)(pSuperiorFibObjectToRemove))->getNumberOfUnderobjects()<<" subobjects."<<endl;
							if ( 2 < ((cList*)(pSuperiorFibObjectToRemove))->getNumberOfUnderobjects() ){
								bCanRemove = true;
							}else{//list element has not enought subobjects to remove one
								bCanRemove = false;
							}
						}else{//can't remove subobject from other superior Fib element typs
							cout<<"Can't remove a external object element with "<<
								"no subobjects from a superior element of type "<<
								cTypeSuperiorToRemove<<" ."<<endl;
							bCanRemove = false;
						}
					}//else a external object element can contain any number of subobjects
				}
			}break;
			case 's':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfExtSubobjectElementsOfResult--;
				cout<<"The to remove Fib element is an external subobject element."<<endl;
				bCanRemove = false;
			}break;
			case 'v':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfSetElementsOfResult--;
				cout<<"The to remove Fib element is an set element."<<endl;
			}break;
			case 'm':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfMatrixElementsOfResult--;
				cout<<"The to remove Fib element is an matrix element."<<endl;
			}break;
		}

		cout<<"The to remove Fib element contains "<<pToRemoveFibElement->getNumberOfElements()<<
			" Fib elements."<<endl;
		
		if ( bCheckVariables && (pToRemoveFibElement != NULL)  ){
			//check variables
			list<cFibVariable*> liDefinedVariables =
				pToRemoveFibElement->getDefinedVariables( ED_POSITION );
			set<cFibVariable*> setUsedVariables =
				pToRemoveFibElement->getUsedVariables( ED_BELOW );
			
			for ( set<cFibVariable*>::iterator itrVariable = setUsedVariables.begin();
					itrVariable != setUsedVariables.end(); itrVariable++ ){
				
				const list<cFibVariable*>::iterator itrFoundedVariable = find(
					liDefinedVariables.begin(), liDefinedVariables.end(),
					(*itrVariable) );
				
				if ( itrFoundedVariable != liDefinedVariables.end() ){
					/*variable not found in the defined variables ->
					can't remove the Fib element*/
					bCanRemove = false;
					cout<<"A variable defined in the to remove Fib element can "<<
						"be found used higher. -> Can't remove the Fib element."<<endl;
				}
			}
		}
		uiNumberOfToRemoveElement = pToRemoveFibElement->getNumberOfElement();
	}else{
		cout<<"The to remove Fib element didn't exists."<<endl;
		bCanRemove = false;
	}
	
	//check isRemovableElement
	cout<<"Calling isRemovableElement("<<
		cTypeRemoveElement <<", "<< uiToRemoveFibElement<<", false, "<<
		(bCheckVariables?"true":"false") <<" ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
	if ( pSuperiorFibObjectToRemove != NULL ){
		cout<<"   The superior Fib element of the to remove "<<
			"Fib element is the "<<
			pSuperiorFibObjectToRemove->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToRemove->getType() <<" ."<<endl;
	}
	const bool bIsRemovebel = pCallingFibElement->isRemovableElement(
		cTypeRemoveElement, uiToRemoveFibElement, false, bCheckVariables );
	if ( bCanRemove  ){
		if ( bIsRemovebel ){
			cout<<"Fib element correctly can be removed."<<endl;
		}else{
			cerr<<"Error: The to remove Fib element says it isn't removebel, but it should."<<endl;
			iReturn++;
		}
	}else{
		if ( bIsRemovebel ){
			cerr<<"Error: The to remove Fib element says it is removebel, but it shouldn't."<<endl;
			iReturn++;
		}else{
			cout<<"Fib element correctly can't be removed."<<endl;
		}
	}

	bool bRemoved = false;
	if ( bCut ){
	
		cout<<"Calling cutElement("<<
			cTypeRemoveElement <<", "<< uiToRemoveFibElement<<", false, "<<
			(bCheckVariables?"true":"false") <<") from the "<<
			pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
			"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
		if ( pSuperiorFibObjectToRemove != NULL ){
			cout<<"   The superior Fib element of the to remove "<<
				"Fib element is the "<<
				pSuperiorFibObjectToRemove->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToRemove->getType() <<" ."<<endl;
		}
		
		//call cutElement()
		cFibElement * pCutElement = pCallingFibElement->cutElement(
			cTypeRemoveElement, uiToRemoveFibElement, false, bCheckVariables );
		
		if ( pCutElement ){
			if ( pCutElement != pToRemoveFibElement ){
				cerr<<"Error: Wrong Fib element cuted."<<endl;
				cerr<<"   The cuted Fib element is "<<pCutElement <<" "<<
					"and not "<< pToRemoveFibElement <<" with number "<<
					uiNumberOfToRemoveElement <<" ."<<endl;

				iReturn++;
			}else{
				delete pCutElement;
			}
			bRemoved = true;
		}else{
			bRemoved = false;
		}
		
	}else{
		cout<<"Calling removeElement("<<
			cTypeRemoveElement <<", "<< uiToRemoveFibElement<<", false, "<<
			(bCheckVariables?"true":"false") <<" ) from the "<<
			pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
			"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
		if ( pSuperiorFibObjectToRemove != NULL ){
			cout<<"   The superior Fib element of the to remove "<<
				"Fib element is the "<<
				pSuperiorFibObjectToRemove->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToRemove->getType() <<" ."<<endl;
		}
		
		//call removeElement()
		bRemoved = pCallingFibElement->removeElement(
			cTypeRemoveElement, uiToRemoveFibElement, false, bCheckVariables );
	}
	if ( bCanRemove  ){
		if ( bRemoved ){
			cout<<"Fib element correctly removed."<<endl;
		}else{
			cerr<<"Error: The to remove Fib element couldn't be removed."<<endl;
			iReturn++;
		}
	}else{
		if ( bRemoved ){
			cerr<<"Error: The to remove Fib element can't be remove,"<<
				" but it was remove."<<endl;
			iReturn++;
		}else{
			cout<<"Fib element correctly not removed."<<endl;
		}
	}
	if ( bRemoved ){
		if ( pSubobjectOfToRemove != NULL ){
			if ( pSubobjectOfToRemove->getSuperiorFibElement() != pSuperiorFibObjectToRemove ){
				cerr<<"Error: The subobject of the removed Fib element "<<
					"hasn't the superior of the removed Fib element."<<endl;
				iReturn++;
			}
		}else{//pSubobjectOfToRemove == NULL
			if ( cCorrectTypeOfToRemove != 'o' ){
			
				cerr<<"Error: The next Fib element of the removed Fib element is NULL."<<endl;
				iReturn++;
			}//else external object elements don't need to have subobjects
		}
	
	}else{
		uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
		uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
		uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
		uiNumberOfListElementsOfResult   = uiNumberOfListElements;
		uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
		uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
		uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
		uiNumberOfIfElementsOfResult     = uiNumberOfIfElements;
		uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
		uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
		uiNumberOfExtSubobjectElementsOfResult= uiNumberOfExtSubobjectElements;
		uiNumberOfSetElementsOfResult    = uiNumberOfSetElements;
		uiNumberOfMatrixElementsOfResult = uiNumberOfMatrixElements;
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error:The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if-elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}



/**
 * This function tests the methods for removing or cutting a Fib element
 * from a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool isRemovableElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables ) const;
 * 	- bool removeElement(  const char cType, const unsignedIntFib  elementPoint, bool bAbsolute=true, bool bCheckVariables );
 * 	- cFibElement *cutElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute=true, bool bCheckVariables );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bCut if true the cutElement() method will be tested, else the
 * 	removeElement() method
 * @param bCheckVariables if the variable check should be performed, befor
 * 	removing the Fib element
 * @return the number of erros occured in the test
 */
int testRemoveElementAbsoluteOnObject( cFibElement * pFibObject, bool bCut, bool bCheckVariables ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	//choos a random calling Fib element
	const unsigned int uiCallingFibElement =
		rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement =
		pFibObject->getFibElement( uiCallingFibElement );

	//choos the Fib element which will be removed
	char cTypeRemoveElement = choosRandomType();
	unsigned int uiNumberOfElementsOfType = 0;

	unsigned int uiToRemoveFibElement = 0;
	
	cFibElement * pToRemoveFibElement = NULL;
	if ( rand() % 50 != 0 ){
		
		switch ( cTypeRemoveElement ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
		if ( uiNumberOfElementsOfType != 0 ){
			uiToRemoveFibElement = rand() % (uiNumberOfElementsOfType + 1);
		}else{
			uiToRemoveFibElement = 0;
		}
		if ( uiToRemoveFibElement != 0 ){
			pToRemoveFibElement = pFibObject->getFibElement(
					cTypeRemoveElement, uiToRemoveFibElement );
		}else{
			pToRemoveFibElement = pCallingFibElement;
		}
		if ( pToRemoveFibElement == NULL ){
			cerr<<"Error: The "<< uiToRemoveFibElement <<
				"'th Fib element of the Fib object couldn't be choosen as "<<
				"the to remove position."<<endl;
			iReturn++;
			return iReturn;
		}
	}else{//test when no Fib object to overwrite exists
		switch ( cTypeRemoveElement ){
			case 'u':uiToRemoveFibElement = uiNumberOfAllFibElements + 1;
			break;
			case 'r':uiToRemoveFibElement = uiNumberOfRootElements + 1;
			break;
			case 'p':uiToRemoveFibElement = uiNumberOfPointElements + 1;
			break;
			case 'l':uiToRemoveFibElement = uiNumberOfListElements + 1;
			break;
			case 'y':uiToRemoveFibElement = uiNumberOfPropertyElements + 1;
			break;
			case 'a':uiToRemoveFibElement = uiNumberOfAreaElements + 1;
			break;
			case 'f':uiToRemoveFibElement = uiNumberOfFunctionElements + 1;
			break;
			case 'i':uiToRemoveFibElement = uiNumberOfIfElements + 1;
			break;
			case 'c':uiToRemoveFibElement = uiNumberOfCommentElements + 1;
			break;
			case 'o':uiToRemoveFibElement = uiNumberOfExtObjectElements + 1;
			break;
			case 's':uiToRemoveFibElement = uiNumberOfExtSubobjectElements + 1;
			break;
			case 'v':uiToRemoveFibElement = uiNumberOfSetElements + 1;
			break;
			case 'm':uiToRemoveFibElement = uiNumberOfMatrixElements + 1;
			break;
		}
	}
	
	bool bCanRemove = true;
	if ( (pToRemoveFibElement == NULL) ||
			(pToRemoveFibElement->getType() == 'r') ||
			(pToRemoveFibElement->getSuperiorFibElement() == NULL) ){
		bCanRemove = false;
	}
	
	unsigned int uiNumberOfToRemoveElement = 0;
	//subtract the counts of the Fib part object that will be overwritten
	unsigned int uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
	unsigned int uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
	unsigned int uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
	unsigned int uiNumberOfListElementsOfResult   = uiNumberOfListElements;
	unsigned int uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
	unsigned int uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
	unsigned int uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
	unsigned int uiNumberOfIfElementsOfResult     = uiNumberOfIfElements;
	unsigned int uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
	unsigned int uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
	unsigned int uiNumberOfExtSubobjectElementsOfResult = uiNumberOfExtSubobjectElements;
	unsigned int uiNumberOfSetElementsOfResult    = uiNumberOfSetElements;
	unsigned int uiNumberOfMatrixElementsOfResult = uiNumberOfMatrixElements;
	
	//store the Fib elements betwean which the Fib object will be removed
	cFibElement * pSuperiorFibObjectToRemove = NULL;
	cFibElement * pSubobjectOfToRemove = NULL;
	char cCorrectTypeOfToRemove = 'u';

	if ( pToRemoveFibElement != NULL ){
		
		pSuperiorFibObjectToRemove =
			pToRemoveFibElement->getSuperiorFibElement();
		pSubobjectOfToRemove =
			pToRemoveFibElement->getNextFibElement();
		
		cCorrectTypeOfToRemove = pToRemoveFibElement->getType();
		
		switch ( cCorrectTypeOfToRemove ){
			case 'r':{
				//can't remove a root-element
				cout<<"The to remove Fib element is an root-element."<<endl;
				bCanRemove = false;
			}break;
			case 'l':{
				cout<<"The to remove Fib element is an list element."<<endl;
				bCanRemove = false;
			}break;
			case 'p':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfPointElementsOfResult--;
				cout<<"The to remove Fib element is an point element."<<endl;
				bCanRemove = false;
			}break;
			case 'y':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfPropertyElementsOfResult--;
				cout<<"The to remove Fib element is an property element."<<endl;
			}break;
			case 'a':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfAreaElementsOfResult--;
				cout<<"The to remove Fib element is an area element."<<endl;
			}break;
			case 'f':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfFunctionElementsOfResult--;
				cout<<"The to remove Fib element is an function element."<<endl;
			}break;
			case 'i':{
				cout<<"The to remove Fib element is an if-element."<<endl;
				bCanRemove = false;
			}break;
			case 'c':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfCommentElementsOfResult--;
				cout<<"The to remove Fib element is an comment element."<<endl;
			}break;
			case 'o':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfExtObjectElementsOfResult--;
				
				const unsignedIntFib uiNumberOfSubobjects =
					((cExtObject*)(pToRemoveFibElement))->getNumberOfSubobjects();
				
				cout<<"The to remove Fib element is an external object element with "<<
					uiNumberOfSubobjects<<" subobjects."<<endl;
				
				if ( 2 <= uiNumberOfSubobjects ){
					//external object element can't be replaced be its more than 1 subobjects
					bCanRemove = false;
				}else if ( uiNumberOfSubobjects == 0 ){
					//external object element has no subobjects
					pSubobjectOfToRemove = NULL;
					
					const char cTypeSuperiorToRemove =
						pSuperiorFibObjectToRemove->getType();
					
					if ( cTypeSuperiorToRemove != 'o' ){
						
						if ( cTypeSuperiorToRemove == 'l' ){
							/*can remove if the list element has more than 2
							subobjects left after removing*/
							cout<<"The superior to the to remove Fib element is a list element with "<<
								((cList*)(pSuperiorFibObjectToRemove))->getNumberOfUnderobjects()<<" subobjects."<<endl;
							if ( 2 < ((cList*)(pSuperiorFibObjectToRemove))->getNumberOfUnderobjects() ){
								bCanRemove = true;
							}else{//list element has not enought subobjects to remove one
								bCanRemove = false;
							}
						}else{//can't remove subobject from other superior Fib element typs
							cout<<"Can't remove a external object element with "<<
								"no subobjects from a superior element of type "<<
								cTypeSuperiorToRemove<<" ."<<endl;
							bCanRemove = false;
						}
					}//else a external object element can contain any number of subobjects
				}
			}break;
			case 's':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfExtSubobjectElementsOfResult--;
				cout<<"The to remove Fib element is an external subobject element."<<endl;
				bCanRemove = false;
			}break;
			case 'v':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfSetElementsOfResult--;
				cout<<"The to remove Fib element is an set element."<<endl;
			}break;
			case 'm':{
				uiNumberOfAllFibElementsOfResult--;
				uiNumberOfMatrixElementsOfResult--;
				cout<<"The to remove Fib element is an matrix element."<<endl;
			}break;
		}

		if ( bCheckVariables && (pToRemoveFibElement != NULL)  ){
			//check variables
			list<cFibVariable*> liDefinedVariables =
				pToRemoveFibElement->getDefinedVariables( ED_POSITION );
			set<cFibVariable*> setUsedVariables =
				pToRemoveFibElement->getUsedVariables( ED_BELOW );
			
			for ( set<cFibVariable*>::iterator itrVariable = setUsedVariables.begin();
					itrVariable != setUsedVariables.end(); itrVariable++ ){
				
				const list<cFibVariable*>::iterator itrFoundedVariable = find(
					liDefinedVariables.begin(), liDefinedVariables.end(),
					(*itrVariable) );
				
				if ( itrFoundedVariable != liDefinedVariables.end() ){
					/*variable not found in the defined variables ->
					can't remove the Fib element*/
					bCanRemove = false;
					cout<<"A variable defined in the to remove Fib element can "<<
						"be found used higher. -> Can't remove the Fib element."<<endl;
				}
			}
		}
		uiNumberOfToRemoveElement = pToRemoveFibElement->getNumberOfElement();
	}else{
		cout<<"The to remove Fib element didn't exists."<<endl;
		bCanRemove = false;
	}
	
	//check isRemovableElement
	cout<<"Calling isRemovableElement("<<
		cTypeRemoveElement <<", "<< uiToRemoveFibElement<<", true, "<<
		(bCheckVariables?"true":"false") <<" ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
	if ( pSuperiorFibObjectToRemove != NULL ){
		cout<<"   The superior Fib element of the to remove "<<
			"Fib element is the "<<
			pSuperiorFibObjectToRemove->getNumberOfElement() <<
			"'th Fib element with the type "<<
			pSuperiorFibObjectToRemove->getType() <<" ."<<endl;
	}
	const bool bIsRemovebel = pCallingFibElement->isRemovableElement(
		cTypeRemoveElement, uiToRemoveFibElement, true, bCheckVariables );
	if ( bCanRemove  ){
		if ( bIsRemovebel ){
			cout<<"Fib element correctly can be removed."<<endl;
		}else{
			cerr<<"Error: The to remove Fib element says it isn't removebel, but it should."<<endl;
			iReturn++;
		}
	}else{
		if ( bIsRemovebel ){
			cerr<<"Error: The to remove Fib element says it is removebel, but it shouldn't."<<endl;
			iReturn++;
		}else{
			cout<<"Fib element correctly can't be removed."<<endl;
		}
	}

	bool bRemoved = false;
	if ( bCut ){
	
		cout<<"Calling cutElement("<<
			cTypeRemoveElement <<", "<< uiToRemoveFibElement<<", true, "<<
			(bCheckVariables?"true":"false") <<") from the "<<
			pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
			"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
		if ( pSuperiorFibObjectToRemove != NULL ){
			cout<<"   The superior Fib element of the to remove "<<
				"Fib element is the "<<
				pSuperiorFibObjectToRemove->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToRemove->getType() <<" ."<<endl;
		}
		
		//call cutElement()
		cFibElement * pCutElement = pCallingFibElement->cutElement(
			cTypeRemoveElement, uiToRemoveFibElement, true, bCheckVariables );
		
		if ( pCutElement ){
			if ( pCutElement != pToRemoveFibElement ){
				cerr<<"Error: Wrong Fib element cuted."<<endl;
				cerr<<"   The cuted Fib element is "<<pCutElement <<" "<<
					"and not "<< pToRemoveFibElement <<" with number "<<
					uiNumberOfToRemoveElement <<" ."<<endl;

				iReturn++;
			}else{
				delete pCutElement;
			}
			bRemoved = true;
		}else{
			bRemoved = false;
		}
		
	}else{
		cout<<"Calling removeElement("<<
			cTypeRemoveElement <<", "<< uiToRemoveFibElement<<", true, "<<
			(bCheckVariables?"true":"false") <<" ) from the "<<
			pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
			"(which is of type "<< pCallingFibElement->getType() <<")."<<endl;
		if ( pSuperiorFibObjectToRemove != NULL ){
			cout<<"   The superior Fib element of the to remove "<<
				"Fib element is the "<<
				pSuperiorFibObjectToRemove->getNumberOfElement() <<
				"'th Fib element with the type "<<
				pSuperiorFibObjectToRemove->getType() <<" ."<<endl;
		}
		
		//call removeElement()
		bRemoved = pCallingFibElement->removeElement(
			cTypeRemoveElement, uiToRemoveFibElement, true, bCheckVariables );
	}
	if ( bCanRemove  ){
		if ( bRemoved ){
			cout<<"Fib element correctly removed."<<endl;
		}else{
			cerr<<"Error: The to remove Fib element couldn't be removed."<<endl;
			iReturn++;
		}
	}else{
		if ( bRemoved ){
			cerr<<"Error: The to remove Fib element can't be remove,"<<
				" but it was remove."<<endl;
			iReturn++;
		}else{
			cout<<"Fib element correctly not removed."<<endl;
		}
	}
	if ( bRemoved ){
		if ( pSubobjectOfToRemove != NULL ){
			if ( pSubobjectOfToRemove->getSuperiorFibElement() != pSuperiorFibObjectToRemove ){
				cerr<<"Error: The subobject of the removed Fib element "<<
					"hasn't the superior of the removed Fib element."<<endl;
				iReturn++;
			}
		}else{//pSubobjectOfToRemove == NULL
			if ( cCorrectTypeOfToRemove != 'o' ){
			
				cerr<<"Error: The next Fib element of the removed Fib element is NULL."<<endl;
				iReturn++;
			}//else external object elements don't need to have subobjects
		}
	
	}else{
		uiNumberOfAllFibElementsOfResult = uiNumberOfAllFibElements;
		uiNumberOfRootElementsOfResult   = uiNumberOfRootElements;
		uiNumberOfPointElementsOfResult  = uiNumberOfPointElements;
		uiNumberOfListElementsOfResult   = uiNumberOfListElements;
		uiNumberOfPropertyElementsOfResult = uiNumberOfPropertyElements;
		uiNumberOfAreaElementsOfResult   = uiNumberOfAreaElements;
		uiNumberOfFunctionElementsOfResult = uiNumberOfFunctionElements;
		uiNumberOfIfElementsOfResult     = uiNumberOfIfElements;
		uiNumberOfCommentElementsOfResult  = uiNumberOfCommentElements;
		uiNumberOfExtObjectElementsOfResult= uiNumberOfExtObjectElements;
		uiNumberOfExtSubobjectElementsOfResult= uiNumberOfExtSubobjectElements;
		uiNumberOfSetElementsOfResult    = uiNumberOfSetElements;
		uiNumberOfMatrixElementsOfResult = uiNumberOfMatrixElements;
	}

	//check the created Fib object
	if ( uiNumberOfAllFibElementsOfResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAllFibElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElementsOfResult !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfRootElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElementsOfResult !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error:The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPointElements <<")"<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElementsOfResult !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfListElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsOfResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfPropertyElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsOfResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfAreaElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsOfResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfFunctionElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElementsOfResult !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if-elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfIfElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsOfResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfCommentElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElementsOfResult !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtObjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElementsOfResult !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfExtSubobjectElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsOfResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfSetElements <<")"<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsOfResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElementsOfResult<<
			") in the created Fib object. (old value="<<
			uiNumberOfMatrixElements <<")"<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}



/**
 * This function tests the equal method for two given equal Fib objects.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool equal( const cFibElement & fibObject ) const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject1 a pointer to the first Fib object to test
 * @param pFibObject2 a pointer to the second Fib object to test,
 * 	which is equal to pFibObject1
 * @return the number of erros occured in the test
 */
int testEqualOnTwoObject( cFibElement * pFibObject1, cFibElement * pFibObject2 ){
	
	int iReturn = 0;
	
	if ( (pFibObject1 == NULL) || (pFibObject2 == NULL) ){
		cerr<<"Error: No Fib objects to check ."<<endl;
		iReturn++;
		return iReturn;
	}

	//test equal on both objects on some random choosen Fib element points
	//counters of corect calls
	unsigned int uiEqualCorrect    = 0;
	unsigned int uiNotEqualCorrect = 0;
	//error counters
	unsigned int uiEqualNotCorrect    = 0;
	unsigned int uiNotEqualNotCorrect = 0;
	
	if ( ! pFibObject1->equal( *pFibObject2 ) ){
		cerr<<"Error: Fib object 1 not equal to Fib object 2 ."<<endl;
		iReturn++;
		uiEqualNotCorrect++;
		return iReturn;
	}else{
		uiEqualCorrect++;
	}
	
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject1->getNumberOfElements();
	
	set< pair<cFibElement*, cFibElement*> > setEqualFibElements;
	
	for ( unsigned int uiIteration = 1;
			uiIteration <= uiNumberOfAllFibElements / 100 + 10; uiIteration++ ){
		
		const unsigned int uiChoosenFibElementNumber =
			(rand() % uiNumberOfAllFibElements) + 1;
		cFibElement * pFibElementToCompare1 = pFibObject1->getFibElement(
			uiChoosenFibElementNumber );
		cFibElement * pFibElementToCompare2 = pFibObject2->getFibElement(
			uiChoosenFibElementNumber );
		
		if ( ! pFibElementToCompare1->equal( *pFibElementToCompare2 ) ){
			cerr<<"Error: Fib object 1 not equal to Fib object 2 . "<<
				"The choosen Fib element point is "<< uiChoosenFibElementNumber <<" ."<<endl;
			iReturn++;
			uiNotEqualNotCorrect++;
		}else{
			uiEqualCorrect++;
			setEqualFibElements.insert(
				make_pair( pFibElementToCompare1 , pFibElementToCompare2 ) );
		}
	}
	if ( iReturn != 0 ){
		//Error: occured -> stop evaluation
		cout<<"Equal method tested:"<<endl;
		cout<<"   correctly equal        : "<< uiEqualCorrect <<endl;
		cout<<"   not correctly not equal: "<< uiNotEqualNotCorrect <<endl;
		cout<<"   equal method called    : "<< uiEqualCorrect + uiNotEqualNotCorrect <<endl;
		return iReturn;
	}
	
	set< pair<cFibElement*, cFibElement*> > setNotEqualFibElements;

	//make a random change to a Fib object
	unsigned int uiRetry = 0;
	cFibElement * pSuperiorToRemove1 = NULL;
	char cTypeSuperiorToRemove1;
	cFibElement * pSuperiorToRemove2 = NULL;
	char cTypeSuperiorToRemove2;
	cFibElement * pToRemoveFibElement1 = NULL;
	cFibElement * pToRemoveFibElement2 = NULL;
	cRoot * pNextRoot = NULL;
	
	while ( ( setNotEqualFibElements.empty() ) && (uiRetry < 100) ){
		uiRetry++;
		
		pSuperiorToRemove1 = NULL;
		pSuperiorToRemove2 = NULL;
		pToRemoveFibElement1 = NULL;
		pToRemoveFibElement2 = NULL;
		
		cFibElement * pChoosenObject = pFibObject1;
		if ( rand() % 2 == 1 ){
			cout<<"Try changing object 2: ";
			pChoosenObject = pFibObject2;
		}else{
			cout<<"Try changing object 1: ";
		}
		pNextRoot = NULL;
		
		switch ( rand() % 2 ){
			case 0:{
				//remove a random Fib element
				unsigned int uiToRemoveFibElement =
					(rand() % uiNumberOfAllFibElements) + 1;
				
				pToRemoveFibElement1 =
					pFibObject1->getFibElement( uiToRemoveFibElement );
				pToRemoveFibElement2 =
					pFibObject2->getFibElement( uiToRemoveFibElement );
					
				pair< cFibElement*, cFibElement* > paToRemoveFibElements =
					make_pair( pToRemoveFibElement1, pToRemoveFibElement2 );
				
				cout<<"Try to remove the "<< uiToRemoveFibElement <<"'th Fib element of type "<<
					pToRemoveFibElement1->getType()<<" ."<<endl;
				//evalue Fib elements that are not equal after removing the Fib element
				pSuperiorToRemove1 = pToRemoveFibElement1->getSuperiorFibElement();
				if ( pSuperiorToRemove1 ){
					cTypeSuperiorToRemove1 = pSuperiorToRemove1->getType();
				}
				cFibElement * pSuperior1 = pSuperiorToRemove1;
				pSuperiorToRemove2 = pToRemoveFibElement2->getSuperiorFibElement();
				if ( pSuperiorToRemove2 ){
					cTypeSuperiorToRemove2 = pSuperiorToRemove2->getType();
				}
				for ( cFibElement * pSuperior2 = pSuperiorToRemove2;
						(pSuperior1 != NULL) && (pSuperior2 != NULL);
						pSuperior1 = pSuperior1->getSuperiorFibElement(),
						pSuperior2 = pSuperior2->getSuperiorFibElement() ){
					
					if ( ! pSuperior1->equal( *pSuperior2 ) ){
						cerr<<"Error: Fib object 1 not equal to Fib object 2 . "<<
							"The choosen Fib element point is "<<
							pSuperior1->getNumberOfElement() <<" ."<<endl;
						iReturn++;
						uiEqualNotCorrect++;
					}else{
						/*cout<<"   superior of to remove: "<< pSuperior1->getNumberOfElement() <<"'th Fib element of type "<<
							pSuperior1->getType()<<""<<endl;*/
						uiEqualCorrect++;
						setNotEqualFibElements.insert(
							make_pair( pSuperior1 , pSuperior2 ) );
					}
				}
				pNextRoot = pToRemoveFibElement1->getSuperiorRootElement();
				
				const bool bRemoved = pChoosenObject->removeElement(
					'u', uiToRemoveFibElement, true, true );
				if ( ! bRemoved ){
					//nothing changed
					setNotEqualFibElements.clear();
				}else{
					setEqualFibElements.erase( paToRemoveFibElements );
					cout<< "The "<< uiToRemoveFibElement <<"'th Fib element was removed."<<endl;
					if ( pChoosenObject == pFibObject1 ){
						pToRemoveFibElement1 = NULL;
					}else{
						pToRemoveFibElement2 = NULL;
					}
				}
			}break;
			case 1:{//remove a random part object
				//remove a random Fib element
				unsigned int uiNumberOfObjectPoints = pFibObject1->getNumberOfObjectPoints();
				if ( uiNumberOfObjectPoints <= 2 ){
					continue;
				}
				unsigned int uiToRemoveObject =
					(rand() % uiNumberOfObjectPoints) + 1;
				unsigned int uiDefiningFibElement = pFibObject1->
					objectPointToElementPoint( uiToRemoveObject );
				
				//evalue Fib elements that are not equal after removing the part object
				pToRemoveFibElement1 =
					pFibObject1->getFibElement( uiDefiningFibElement );
				pToRemoveFibElement2 =
					pFibObject2->getFibElement( uiDefiningFibElement );
				
				pSuperiorToRemove1 = pToRemoveFibElement1->getSuperiorFibElement();
				if ( pSuperiorToRemove1 ){
					cTypeSuperiorToRemove1 = pSuperiorToRemove1->getType();
				}
				cFibElement * pSuperior1 = pSuperiorToRemove1->getSuperiorFibElement();
				pSuperiorToRemove2 = pToRemoveFibElement2->getSuperiorFibElement();
				if ( pSuperiorToRemove2 ){
					cTypeSuperiorToRemove2 = pSuperiorToRemove2->getType();
				}
				
				cout<< "Try to remove the "<< uiToRemoveObject <<"'th part object. "<<
					"With defining element "<<uiDefiningFibElement<<" of type "<<flush<<
					pToRemoveFibElement1->getType()<<", superior ";
				if ( pToRemoveFibElement1->getSuperiorFibElement() != NULL ){
					cout<<pToRemoveFibElement1->getSuperiorFibElement()->getNumberOfElement()<<" of type "<<
						pToRemoveFibElement1->getSuperiorFibElement()->getType()<<" and superior superior ";
				}else{
					cout<<"NULL and superior superior ";
				}
				if ( pSuperior1 != NULL ){
					cout<<pSuperior1->getNumberOfElement()<<" of type "<<
						pSuperior1->getType()<<" ."<<endl;
				}else{
					cout<<"NULL ."<<endl;
				}
				
				for ( cFibElement * pSuperior2 = pSuperiorToRemove2->getSuperiorFibElement();
						(pSuperior1 != NULL) && (pSuperior2 != NULL);
						pSuperior1 = pSuperior1->getSuperiorFibElement(),
						pSuperior2 = pSuperior2->getSuperiorFibElement() ){
					
					if ( pSuperior1->equal( *pSuperior2 ) ){
						/*cout<<"   superior of to remove: "<< pSuperior1->getNumberOfElement() <<"'th Fib element of type "<<
							pSuperior1->getType()<<""<<endl;*/
						uiEqualCorrect++;
						setNotEqualFibElements.insert(
							make_pair( pSuperior1 , pSuperior2 ) );
					}else{
						cerr<<"Error: Fib object 1 not equal to Fib object 2 . "<<
							"The choosen Fib element point is "<<
							pSuperior1->getNumberOfElement() <<" and "<<
							pSuperior2->getNumberOfElement() <<" ."<<endl;
						iReturn++;
						uiEqualNotCorrect++;
					}
				}
				pNextRoot = pToRemoveFibElement1->getSuperiorRootElement();
				
				//remove all Fib elements of the to remove part object from the equal list
				setEqualFibElements.erase(
					make_pair( pToRemoveFibElement1->getSuperiorFibElement(),
						pToRemoveFibElement2->getSuperiorFibElement() ) );
				
				unsigned int uiToRemoveFibElements =
					pToRemoveFibElement1->getNumberOfElements();
				
				if ( ( pToRemoveFibElement1->getSuperiorFibElement() != NULL ) &&
						( pToRemoveFibElement1->getSuperiorFibElement()->getType() == 'o' ) ){
					/*If the superior element is an external object element
					 remove also all subobjects of the superior external object,
					 which are after the removed subobject. Because if subobject
					 is moved (one step to the front) its variables (the output
					 variables for the subobject) won't be equal anymore.*/
					cExtObject * pSuperiorExtObject = ((cExtObject*)
						pToRemoveFibElement1->getSuperiorFibElement());
					
					const unsignedIntFib uiNumberOfSubobjects =
						pSuperiorExtObject->getNumberOfSubobjects();
					//find the subobject of the external object to remove
					unsignedIntFib uiActualSubobject = 1;
					for ( ; uiActualSubobject <= uiNumberOfSubobjects;
							uiActualSubobject++ ){
						if ( pSuperiorExtObject->getSubobject( uiActualSubobject ) ==
								pToRemoveFibElement1 ){
							//subobject to remove found
							break;
						}
					}
					/*mark the Fib elements in the subobjects after and the to
					 remove subobject as to remove in the equal list*/
					uiToRemoveFibElements = 0;
					for ( ; uiActualSubobject <= uiNumberOfSubobjects;
							uiActualSubobject++ ){
						//mark Fib elements in the subobject as not equal
						uiToRemoveFibElements += pSuperiorExtObject->
							getSubobject( uiActualSubobject )->getNumberOfElements();
					}
				}//end if superior element is an external object element
				
				cFibElement * pContainedInToRemove1 = pToRemoveFibElement1;
				cFibElement * pContainedInToRemove2 = pToRemoveFibElement2;
				for ( unsigned int uiActualFibElement = 1;
					uiActualFibElement <= uiToRemoveFibElements; uiActualFibElement++ ){
				
					setEqualFibElements.erase(
						make_pair( pContainedInToRemove1, pContainedInToRemove2 ) );
					
					pContainedInToRemove1 = pContainedInToRemove1->getNextFibElement();
					pContainedInToRemove2 = pContainedInToRemove2->getNextFibElement();
				}
				
				const bool bRemoved = pChoosenObject->removeObject(
					uiToRemoveObject, true, true );
				if ( ! bRemoved ){
					//nothing changed
					setNotEqualFibElements.clear();
				}else{
					cout<< "The "<< uiToRemoveObject <<"'th part object was removed."<<endl;
					if ( pChoosenObject == pFibObject1 ){
						pToRemoveFibElement1 = NULL;
					}else{
						pToRemoveFibElement2 = NULL;
					}
				}
			}break;
		
		//TODO change the values a variable could take
		}
		if ( setNotEqualFibElements.empty() ){
			cout<<" not Ok -> retry"<<endl;
		}
	}
	if ( ( pSuperiorToRemove1 != NULL ) &&  ( pSuperiorToRemove2 != NULL ) &&
			 ( cTypeSuperiorToRemove1 == 'o' ) &&
			 ( cTypeSuperiorToRemove2 == 'o' ) &&
			 ( ((cExtObject*)(pSuperiorToRemove1))->getNumberOfSubobjects() !=
			 	((cExtObject*)(pSuperiorToRemove2))->getNumberOfSubobjects() ) ){
		/*if in an external object element an subobject was removed the
		defined variables for the subobjects after the removed are different
		-> Fib elements in them that depend on these variables are not equal*/
		//search for position of removed subobject
		cExtObject * pExtObject1 = ((cExtObject*)(pSuperiorToRemove1));
		cExtObject * pExtObject2 = ((cExtObject*)(pSuperiorToRemove2));
		unsignedIntFib uiSubobjectToCheck1 = 1;
		unsignedIntFib uiSubobjectToCheck2 = 1;
		const unsignedIntFib uiNumberOfSubobjects1 =
			pExtObject1->getNumberOfSubobjects();
		const unsignedIntFib uiNumberOfSubobjects2 =
			pExtObject2->getNumberOfSubobjects();
		if ( pToRemoveFibElement1 != NULL ){
			
			if ( uiNumberOfSubobjects1 != (uiNumberOfSubobjects2 + 1) ){
				//should not happen
				cerr<<"Error: Superior external objects have not correct number of subobjects 1 "<<
					"(1 has "<<uiNumberOfSubobjects1<<", 2 has "<<uiNumberOfSubobjects2<<" subobjects)."<<endl;
				iReturn++;
				return iReturn;
			}
			
			for ( ; uiSubobjectToCheck1 <= uiNumberOfSubobjects1;
					uiSubobjectToCheck1++ ){
				if ( pToRemoveFibElement1 == pExtObject1->getSubobject( uiSubobjectToCheck1 ) ){
					//subobject to check found
					break;
				}
			}
			if ( uiNumberOfSubobjects1 < uiSubobjectToCheck1 ){
				//should not happen
				cerr<<"Error: Removed subobject (number "<<pToRemoveFibElement1->getNumberOfElement()<<
					" type "<<pToRemoveFibElement1->getType()<<") of external object 1 not found (it has "<<
					uiNumberOfSubobjects1<<" subobjects)."<<endl;
				iReturn++;
				return iReturn;
			}
			uiSubobjectToCheck2 = uiSubobjectToCheck1;
			uiSubobjectToCheck1++;
		}else{//(pToRemoveFibElement2 != NULL)
			if ( (uiNumberOfSubobjects1 + 1) != uiNumberOfSubobjects2 ){
				//should not happen
				cerr<<"Error: Superior external objects have not correct number of subobjects 2 "<<
					"(1 has "<<uiNumberOfSubobjects1<<", 2 has "<<uiNumberOfSubobjects2<<" subobjects)."<<endl;
				iReturn++;
				return iReturn;
			}
			
			for ( ; uiSubobjectToCheck2 <= uiNumberOfSubobjects2;
					uiSubobjectToCheck2++ ){
				if ( pToRemoveFibElement2 == pExtObject2->getSubobject( uiSubobjectToCheck2 ) ){
					//subobject to check found
					break;
				}
			}
			if ( uiNumberOfSubobjects2 < uiSubobjectToCheck2 ){
				//should not happen
				cerr<<"Error: Removed subobject (number "<<pToRemoveFibElement2->getNumberOfElement()<<
					" type "<<pToRemoveFibElement2->getType()<<") of external object 2 not found (it has "<<
					uiNumberOfSubobjects2<<" subobjects)."<<endl;
				iReturn++;
				return iReturn;
			}
			uiSubobjectToCheck1 = uiSubobjectToCheck2;
			uiSubobjectToCheck2++;
		}
		//for every subobject to check
		for ( ; uiSubobjectToCheck1 <= uiNumberOfSubobjects1;
				uiSubobjectToCheck1++, uiSubobjectToCheck2++ ){
			
			cFibElement * pSubobject1 = pExtObject1->getSubobject( uiSubobjectToCheck1 );
			cFibElement * pSubobject2 = pExtObject2->getSubobject( uiSubobjectToCheck2 );
			
			/*check all below Fib element (if they use direct or indirect
			variables defined by the external object element they are not
			equal anymore)*/
			list< cFibElement* > liAllFibElementsBelow1 =
				pSubobject1->getAllFibElements( 'u', 0, 'u', ED_BELOW );
			list< cFibElement* > liAllFibElementsBelow2 =
				pSubobject2->getAllFibElements( 'u', 0, 'u', ED_BELOW );
			map< cFibElement*, cFibElement* > mapAllFibElementsBelow;
			list<cFibElement*>::iterator itrFibElementBelow1 =
				liAllFibElementsBelow1.begin();
			for ( list<cFibElement*>::iterator
						itrFibElementBelow2 = liAllFibElementsBelow2.begin();
					( itrFibElementBelow1 != liAllFibElementsBelow1.end() ) &&
					( itrFibElementBelow2 != liAllFibElementsBelow2.end() );
					itrFibElementBelow1++, itrFibElementBelow2++ ){
				
				/*cout<<"      The Fib element "<<(*itrFibElementBelow1)<<" with number "<<
					(*itrFibElementBelow1)->getNumberOfElement()<<" and type "<<
					(*itrFibElementBelow1)->getType()<<
					" is in the subobject of the superior external object element (2 "<<
					(*itrFibElementBelow2)<<" with number "<<
					(*itrFibElementBelow2)->getNumberOfElement()<<" and type "<<
					(*itrFibElementBelow2)->getType()<<")"<<endl;*/
				
				mapAllFibElementsBelow.insert( make_pair(
					(*itrFibElementBelow1), (*itrFibElementBelow2) ) );
			}
			//don't check the external object again
			mapAllFibElementsBelow.erase( pExtObject1 );
			cout<<"   Ther are "<<mapAllFibElementsBelow.size()<<
				" Fib elements is in the subobject of the superior external object element with "<<
				pExtObject1->getNumberOfSubobjects()<<" subobjects (2 "<<
				pExtObject2->getNumberOfSubobjects()<<" subobjects) ."<<endl;
			//check below pairs
			while ( ! mapAllFibElementsBelow.empty() ){
				
				map< cFibElement*, cFibElement* >::iterator itrFibElementBelow =
					mapAllFibElementsBelow.begin();
				
				if ( ! itrFibElementBelow->first->equalElement(
						*(itrFibElementBelow->second) ) ){
					/*Fib elements are not equal
					-> add them and all superior Fib elements to not equal Fib elements*/
					setNotEqualFibElements.insert( make_pair(
						itrFibElementBelow->first , itrFibElementBelow->second ) );
					
					/*cout<<"      The Fib element "<<itrFibElementBelow->first<<" with number "<<
						itrFibElementBelow->first->getNumberOfElement()<<" and type "<<
						itrFibElementBelow->first->getType()<<" is below the external object element (2 "<<
						itrFibElementBelow->second<<" with number "<<
						itrFibElementBelow->second->getNumberOfElement()<<" and type "<<
						itrFibElementBelow->second->getType()<<") and not equal to the correpondending Fib element"<<endl;*/
					
					cFibElement * pSuperior1 = itrFibElementBelow->first->getSuperiorFibElement();
					for ( cFibElement * pSuperior2 = itrFibElementBelow->second->getSuperiorFibElement();
							(pSuperior1 != NULL) && (pSuperior2 != NULL) &&
							(pSuperior1 != pExtObject1) && (pSuperior2 != pExtObject2) ;
							pSuperior1 = pSuperior1->getSuperiorFibElement(),
							pSuperior2 = pSuperior2->getSuperiorFibElement() ){
						
						/*cout<<"      The Fib element "<<pSuperior1<<" with number "<<
							pSuperior1->getNumberOfElement()<<" and type "<<
							pSuperior1->getType()<<" is below the external object element (2 "<<
							pSuperior2<<" with number "<<pSuperior2->getNumberOfElement()<<" and type "<<
							pSuperior2->getType()<<") and has is superior to "<<
							"an not equal to the correpondending Fib element Fib element"<<endl;*/
						
						setNotEqualFibElements.insert(
							make_pair( pSuperior1 , pSuperior2 ) );
						//don't check again this pair
						mapAllFibElementsBelow.erase( pSuperior1 );
					}
				
				}//end if below Fib elements are equal
				mapAllFibElementsBelow.erase( itrFibElementBelow->first );
			}//end for all Fib element pairs below
			
		}
		
	}//endif subobject of external object removed
	//evalue all external object elements that uses the changed root element
	set< cRoot * > setRootsToCheck;
	setRootsToCheck.insert( pNextRoot );
	set< cRoot * > setRootsChecked;
	while ( ! setRootsToCheck.empty() ){
		
		//check next superior root element
		set< cRoot * >::iterator itrNextRootToCheck = setRootsToCheck.begin();
		pNextRoot = (*itrNextRootToCheck);
		setRootsToCheck.erase( itrNextRootToCheck );
		setRootsChecked.insert( pNextRoot );
		
		cRoot * pNextNextRoot = ( pNextRoot != NULL ) ?
			pNextRoot->getSuperiorRootElement() : NULL;
		cout<<"Next root object: "<<pNextRoot<<";  next next root: "<<pNextNextRoot<<endl;
		
		if ( pNextNextRoot == NULL ){
			continue;
		}
		setRootsToCheck.insert( pNextNextRoot );
		
		const unsignedIntFib uiNumberOfSubRootObject =
			pNextNextRoot->getNumberOfSubRootObjects();
			
		//get identifier for the next root element
		longFib lIdentifierForNextRoot = 0;
		for ( unsignedIntFib uiActualSubRootObject = 1;
				uiActualSubRootObject <= uiNumberOfSubRootObject;
				uiActualSubRootObject++ ){
			
			pair< longFib, cRoot* > paActualSubRoot =
				pNextNextRoot->getSubRootObject( uiActualSubRootObject );
			
			if ( paActualSubRoot.second == pNextRoot ){
				//next root found
				lIdentifierForNextRoot = paActualSubRoot.first;
				break;
			}
		}//end for search for root with identifier
		cout<<"The root object with the identifier "<<lIdentifierForNextRoot<<" was changed."<<endl;
		/*evalue all external object elements with the identifier
		(they are not equal)*/
		for ( cExtObject * pExtObject1 = ((cExtObject*)(pNextRoot->getFibElement( 'o', -1 )));
				pExtObject1 != NULL;
				pExtObject1 = ((cExtObject*)(pExtObject1->getFibElement( 'o', -1 ))) ){
			
			if ( pExtObject1->getIdentifier() == lIdentifierForNextRoot ){
				/*external object element that uses the root element found;
				it is not exual to the correspondending external object element*/
				
				cRoot * pExternalObjectRoot = pExtObject1->getSuperiorRootElement();
				if ( setRootsChecked.find( pExternalObjectRoot ) == setRootsChecked.end() ){
					//root not checked befor -> remember external object root to check next
					setRootsToCheck.insert( pExternalObjectRoot );
				}
				
				cFibElement * pExtObject2 =
					pFibObject2->getFibElement( pExtObject1->getNumberOfElement() );
				cFibElement * pSuperior1 = pExtObject1;
				
				cout<<"   The external object element with number "<<
					pExtObject2->getNumberOfElement()<<" uses the root element with the identifier "<<
					pExtObject1->getIdentifier()<<" ."<<endl;
				
				for ( cFibElement * pSuperior2 = pExtObject2;
						(pSuperior1 != NULL) && (pSuperior2 != NULL);
						pSuperior1 = pSuperior1->getSuperiorFibElement(),
						pSuperior2 = pSuperior2->getSuperiorFibElement() ){
					
					/*cout<<"      The Fib element "<<pSuperior1<<" with number "<<
						pSuperior1->getNumberOfElement()<<" and type "<<
						pSuperior1->getType()<<" contains the external object element (2 "<<
						pSuperior2<<" with number "<<pSuperior2->getNumberOfElement()<<" and type "<<
						pSuperior2->getType()<<")"<<endl;*/
					
					setNotEqualFibElements.insert(
						make_pair( pSuperior1 , pSuperior2 ) );
				}
			
				/*check all below Fib element (if they use direct or indirect
				variables defined by the external object element they are not
				equal anymore)*/
				list< cFibElement* > liAllFibElementsBelow1 =
					pExtObject1->getAllFibElements( 'u', 0, 'u', ED_BELOW );
				list< cFibElement* > liAllFibElementsBelow2 =
					pExtObject2->getAllFibElements( 'u', 0, 'u', ED_BELOW );
				map< cFibElement*, cFibElement* > mapAllFibElementsBelow;
				list<cFibElement*>::iterator itrFibElementBelow1 =
					liAllFibElementsBelow1.begin();
				for ( list<cFibElement*>::iterator
							itrFibElementBelow2 = liAllFibElementsBelow2.begin();
						( itrFibElementBelow1 != liAllFibElementsBelow1.end() ) &&
						( itrFibElementBelow2 != liAllFibElementsBelow2.end() );
						itrFibElementBelow1++, itrFibElementBelow2++ ){
					
					/*cout<<"      The Fib element "<<(*itrFibElementBelow1)<<" with number "<<
						(*itrFibElementBelow1)->getNumberOfElement()<<" and type "<<
						(*itrFibElementBelow1)->getType()<<" is below the external object element (2 "<<
						(*itrFibElementBelow2)<<" with number "<<
						(*itrFibElementBelow2)->getNumberOfElement()<<" and type "<<
						(*itrFibElementBelow2)->getType()<<")"<<endl;*/
					
					mapAllFibElementsBelow.insert( make_pair(
						(*itrFibElementBelow1), (*itrFibElementBelow2) ) );
				}
				//don't check the external object again
				mapAllFibElementsBelow.erase( pExtObject1 );
				cout<<"   Ther are "<<mapAllFibElementsBelow.size()<<
					" Fib elements below the external object element with "<<
					((cExtObject*)(pExtObject1))->getNumberOfSubobjects()<<
					" subobjects."<<endl;
				//check below pairs
				while ( ! mapAllFibElementsBelow.empty() ){
					
					map< cFibElement*, cFibElement* >::iterator itrFibElementBelow =
						mapAllFibElementsBelow.begin();
					
					if ( ! itrFibElementBelow->first->equalElement(
							*(itrFibElementBelow->second) ) ){
						/*Fib elements are not equal
						-> add them and all superior Fib elements to not equal Fib elements*/
						setNotEqualFibElements.insert( make_pair(
							itrFibElementBelow->first , itrFibElementBelow->second ) );
						
						/*cout<<"      The Fib element "<<itrFibElementBelow->first<<" with number "<<
							itrFibElementBelow->first->getNumberOfElement()<<" and type "<<
							itrFibElementBelow->first->getType()<<" is below the external object element (2 "<<
							itrFibElementBelow->second<<" with number "<<
							itrFibElementBelow->second->getNumberOfElement()<<" and type "<<
							itrFibElementBelow->second->getType()<<") and not equal to the correpondending Fib element"<<endl;*/
						
						cFibElement * pSuperior1 = itrFibElementBelow->first->getSuperiorFibElement();
						for ( cFibElement * pSuperior2 = itrFibElementBelow->second->getSuperiorFibElement();
								(pSuperior1 != NULL) && (pSuperior2 != NULL) &&
								(pSuperior1 != pExtObject1) && (pSuperior2 != pExtObject2) ;
								pSuperior1 = pSuperior1->getSuperiorFibElement(),
								pSuperior2 = pSuperior2->getSuperiorFibElement() ){
							
							/*cout<<"      The Fib element "<<pSuperior1<<" with number "<<
								pSuperior1->getNumberOfElement()<<" and type "<<
								pSuperior1->getType()<<" is below the external object element (2 "<<
								pSuperior2<<" with number "<<pSuperior2->getNumberOfElement()<<" and type "<<
								pSuperior2->getType()<<") and has is superior to "<<
								"an not equal to the correpondending Fib element Fib element"<<endl;*/
							
							setNotEqualFibElements.insert(
								make_pair( pSuperior1 , pSuperior2 ) );
							//don't check again this pair
							mapAllFibElementsBelow.erase( pSuperior1 );
						}
					
					}//end if below Fib elements are equal
					mapAllFibElementsBelow.erase( itrFibElementBelow->first );
				}//end for all Fib element pairs below
			
			
			}//end if the external object has the correct identifier
		}//end for all previos external objects
		
	}//end while for all superior roots
	
	//remove all not equal elements from the equal set
	for ( set< pair<cFibElement*, cFibElement*> >::iterator
				itrActualNotEqualPair = setNotEqualFibElements.begin();
			itrActualNotEqualPair != setNotEqualFibElements.end();
			itrActualNotEqualPair++ ){
	
		setEqualFibElements.erase( *itrActualNotEqualPair );
	}
	
	/*test equal on changed objects again on some random choosen
	Fib element points for which the Fib object has changed*/
	for ( set< pair<cFibElement*, cFibElement*> >::iterator
				itrActualNotEqualPair = setNotEqualFibElements.begin();
			itrActualNotEqualPair != setNotEqualFibElements.end();
			itrActualNotEqualPair++ ){
	
		if ( (itrActualNotEqualPair->first)->equal( *(itrActualNotEqualPair->second) ) ){
			cerr<<"Error: Fib object 1 is equal to Fib object 2 . "<<
				"The choosen Fib element point is "<<
				(itrActualNotEqualPair->first)->getNumberOfElement() <<" of type "<<
				(itrActualNotEqualPair->first)->getType()<<" ."<<endl;
			iReturn++;
			uiEqualNotCorrect++;
		}else{
			uiNotEqualCorrect++;
		}
	}
	for ( set< pair<cFibElement*, cFibElement*> >::iterator
				itrActualEqualPair = setEqualFibElements.begin();
			itrActualEqualPair != setEqualFibElements.end();
			itrActualEqualPair++ ){
	
		if ( ! (itrActualEqualPair->first)->equal( *(itrActualEqualPair->second) ) ){
			cerr<<"Error: Fib object 1 not equal to Fib object 2 . "<<
				"The choosen Fib element point is "<<
				(itrActualEqualPair->first)->getNumberOfElement() <<" of type "<<
				(itrActualEqualPair->first)->getType()<<" (compare with Fib element "<<
				(itrActualEqualPair->second)->getNumberOfElement() <<" of type "<<
				(itrActualEqualPair->second)->getType()<<")."<<endl;
			iReturn++;
			uiNotEqualNotCorrect++;
		}else{
			uiEqualCorrect++;
		}
	}
	
	cout<<"Equal method tested:"<<endl;
	cout<<"   correctly equal        : "<< uiEqualCorrect <<endl;
	cout<<"   correctly not equal    : "<< uiNotEqualCorrect <<endl;
	cout<<"   correctly              : "<< uiEqualCorrect + uiNotEqualCorrect <<endl;
	cout<<"   not correctly equal    : "<< uiEqualNotCorrect <<endl;
	cout<<"   not correctly not equal: "<< uiNotEqualNotCorrect <<endl;
	cout<<"   not correct            : "<< uiEqualNotCorrect + uiNotEqualNotCorrect <<endl;
	cout<<"   equal method called    : "<< uiEqualCorrect +
		uiNotEqualCorrect + uiEqualNotCorrect + uiNotEqualNotCorrect <<endl;
	
	return iReturn;
}



/**
 * This function tests the moveLimbElement() method for a given Fib object.
 * It trys to move a non limbelement with random parameters.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib elementPoint, const intFib iHowfar, bool bAbsolute );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject1 a pointer to the first Fib object to test
 * @param pFibObject2 a pointer to the second Fib object to test,
 * 	which is equal to pFibObject1
 * @return the number of erros occured in the test
 */
int testMoveLimbElementOnNonMovebelOnObject( cFibElement * pFibObject1, cFibElement * pFibObject2 ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( (pFibObject1 == NULL) || (pFibObject2 == NULL) ){
		cerr<<"Error: No Fib objects to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject1->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject1->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject1->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject1->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject1->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject1->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject1->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject1->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject1->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject1->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject1->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject1->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject1->getNumberOfElements( 'm' );
	
	for ( unsigned int uiIteration = 1;
			uiIteration <= uiNumberOfAllFibElements / 10 + 20;
			uiIteration++ ){
		//choos a rondom calling Fib element
		const unsigned int uiCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
		cFibElement * pCallingFibElement = pFibObject1->getFibElement(
			 uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		
		//choos random parameters
		const char cType = choosRandomType();
		
		bool bAbsolute = false;
		if ( rand() % 2 == 1 ){
			bAbsolute = true;
		}
		unsigned int uiNumberOfElementsOfType = 0;
		if ( bAbsolute ){
			switch ( cType ){
				case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
				break;
				case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
				break;
				case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
				break;
				case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
				break;
				case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
				break;
				case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
				break;
				case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
				break;
				case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
				break;
				case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
				break;
				case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
				break;
				case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
				break;
				case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
				break;
				case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
				break;
			}
		}else{
			uiNumberOfElementsOfType =
				pCallingFibElement->getNumberOfElements( cType );
		}
		const unsignedIntFib elementPoint = rand() % ( uiNumberOfElementsOfType + 3 );
		
		const cFibElement * pToMoveFibElement = pCallingFibElement->
			getFibElement( cType, elementPoint, bAbsolute );
		if ( (pToMoveFibElement != NULL) && ( pToMoveFibElement->isLimb() ) ){
			//skip limbelements which can be moved
			continue;
		}
		
		intFib iHowfar = 0;
		if ( rand() % 3 < 2 ){
			iHowfar = rand() % 20 - 10;
		}else{
			iHowfar = (rand() % uiNumberOfAllFibElements) -
				uiNumberOfAllFibElements / 2;
		}
		
		cout<<"Calling intFib moveLimbElement( cType='"<< cType <<"', elementPoint="<<
			elementPoint <<", iHowfar="<< iHowfar <<", bAbsolute="<<
			(bAbsolute?"true":"false") <<") from the "<< uiNumberOfAllFibElements <<
			" Fib element with the type "<<
			pCallingFibElement->getType() <<" in the Fib object."<<endl;
		
		const intFib iElementsMovedOver = pCallingFibElement->moveLimbElement(
			cType, elementPoint, iHowfar, bAbsolute );
		
		if ( iElementsMovedOver != 0 ){
			cerr<<"Error: The Fib element was moved ."<<endl;
			iReturn++;
		}
		
		if ( ! pFibObject1->equal( *pFibObject2 ) ){
			cerr<<"Error: The Fib object changed ."<<endl;
			iReturn++;
			break;
		}
	}

	return iReturn;
}



/**
 * This function tests the moveLimbElement() method for a given Fib object.
 * It trys to move a limbelement in direction higher.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib  elementPoint, const intFib iHowfar<=0, bool bAbsolute );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bAbsolute the bAbsolute value for moveLimbElement()
 * @return the number of erros occured in the test
 */
int testMoveLimbElementUpOnObject( cFibElement * pFibObject, bool bAbsolute ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( (pFibObject == NULL) || (pFibObject->getType() != 'r' ) ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );

	//choos a rondom calling Fib element
	const unsigned int uiCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement = pFibObject->getFibElement( uiCallingFibElement );
	//check the getType() methode from cList
	if ( pCallingFibElement == NULL ){
		cerr<<"Error: The "<< uiCallingFibElement <<
			"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//choos random Fib limbelement
	char cType;
	unsigned int uiNumberOfElementsOfType = 0;
	unsignedIntFib uiElementPoint   = 0;
	cFibElement * pToMoveFibElement = NULL;
	
	for ( unsigned int uiRetry = 1; uiRetry <= uiNumberOfAllFibElements / 10 + 20;
			uiRetry++ ){
		cType = choosRandomType();
		if ( bAbsolute ){
			switch ( cType ){
				case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
				break;
				case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
				break;
				case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
				break;
				case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
				break;
				case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
				break;
				case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
				break;
				case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
				break;
				case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
				break;
				case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
				break;
				case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
				break;
				case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
				break;
				case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
				break;
				case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
				break;
			}
		}else{
			uiNumberOfElementsOfType =
				pCallingFibElement->getNumberOfElements( cType );
		}
		uiElementPoint = rand() % ( uiNumberOfElementsOfType + 3 );
		
		pToMoveFibElement = pCallingFibElement->getFibElement( cType, uiElementPoint, bAbsolute );
		
		if ( (pToMoveFibElement != NULL) && ( pToMoveFibElement->isLimb() ) &&
				( pToMoveFibElement->getType() != 'c' ) ){
			//movebel Fib element found
			//TODO: move a comment element (how to mark it?)
			break;
		}
	}
	if ( (pToMoveFibElement == NULL) || ( ! pToMoveFibElement->isLimb() ) ||
			( pToMoveFibElement->getType() == 'c' ) ){
		//can't move Fib element -> skip
		cout<<"Couldn't choose a limbelement to move."<<endl;
		return iReturn;
	}
	unsigned int uiNumberOfToMoveElement = pToMoveFibElement->getNumberOfElement();
	//mark the choosen limbelement with a new variable
	cRoot * pNextRoot = (cRoot*)pToMoveFibElement->getFibElement( 'r', -1 );
	
	pNextRoot->setNumberOfInputVariables(
		pNextRoot->getNumberOfInputVariables() + 1 );
	cFibVariable * pVariableMarker = pNextRoot->getInputVariable(
		pNextRoot->getNumberOfInputVariables() );
	
	const char cTypeOfFibElementToMove = pToMoveFibElement->getType();
	switch ( cTypeOfFibElementToMove ){
		case 'y':{
			cProperty * pChoosenProperty = (cProperty*)pToMoveFibElement;
			if ( pChoosenProperty->getProperty()->getNumberOfElements() == 0){
				//can't mark the property element -> skip this test
				cout<<"Propertyelement with 0 Vectorelements choosen -> skip moving."<<endl;
				return iReturn;
			}
			pChoosenProperty->getProperty()->setVariable( 1, pVariableMarker );
		}break;
		case 'a':{
			cArea * pChoosenArea = (cArea*)pToMoveFibElement;
			pChoosenArea->getSubarea( 1 )->setVariable( 1, pVariableMarker );
		}break;
		case 'f':{
			cFunction * pChoosenFunction = (cFunction*)pToMoveFibElement;
			
			cFunctionVariable functionVariable( pVariableMarker );
			pChoosenFunction->setUnderFunction( functionVariable );
		}break;
		case 'v':{
			cFibSet * pChoosenSetElement = (cFibSet*)pToMoveFibElement;
			
			if ( pChoosenSetElement->getVector( 1 )->getNumberOfElements() == 0 ){
				//can't marke Fib element -> skip
				cout<<"Couldn't mark the set-element with a variable (no vector elements)."<<endl;
				return iReturn;
			}
			
			pChoosenSetElement->getVector( 1 )->setVariable( 1, pVariableMarker );
		}break;
		case 'm':{
			cFibMatrix * pChoosenMatrixElement = (cFibMatrix*)pToMoveFibElement;
			
			pChoosenMatrixElement->getArea( 1 )->setVariable( 1, pVariableMarker );
		}break;
		//TODO more limb elements
		default:{
			cerr<<"Error: Unknown Fib limb element type "<<cTypeOfFibElementToMove<<"to move."<<endl;
			iReturn++;
			return iReturn;
		}break;
	}
	
	//choose howfar to move the Fib element
	intFib iHowfar = 0;
	if ( rand() % 3 < 2 ){
		iHowfar = -1 * (rand() % 10);
	}else{
		iHowfar = -1 * (rand() % uiNumberOfAllFibElements);
	}
	
	cout<<"Calling moveLimbElement( cType='"<< cType <<"', elementPoint="<<
		uiElementPoint <<", iHowfar="<< iHowfar <<", bAbsolute="<<
		(bAbsolute?"true":"false") <<") from the "<< uiCallingFibElement <<
		" Fib element with the type "<<
		pCallingFibElement->getType() <<" in the Fib object,"<<
		"to move the "<< uiNumberOfToMoveElement << "'th Fib element of type "<<
		cTypeOfFibElementToMove<<"."<<endl;
	
	const intFib iElementsMovedOver = pCallingFibElement->moveLimbElement(
		cType, uiElementPoint, iHowfar, bAbsolute );
	
	cout<<"Fib element moved "<< iElementsMovedOver <<" steps down."<<endl;
	/*test if the limbelement is moved up the correct number of steps*/
	set<cFibElement*> setMovedElements = pVariableMarker->getUsingElements();
	
	if ( setMovedElements.size() != 1 ){
		cerr<<"Error: After moving the limbelement ther are "<<
			setMovedElements.size()<<" moved Fib elements."<<endl;
		iReturn++;
	}
	cFibElement * pMovedFibElement = *(setMovedElements.begin());
	
	if ( iHowfar == iElementsMovedOver ){
		//check if the moved limbelement is iHowfar steps down the move position
		cFibElement * pMovePosition = pFibObject->getFibElement( uiNumberOfToMoveElement );
		
		int iNumberOfSuperior = 0;
		cFibElement * pSuperior = NULL;
		for ( pSuperior = pMovePosition;
				(pSuperior != NULL) && (pSuperior != pMovedFibElement) &&
				(iHowfar != iNumberOfSuperior); iNumberOfSuperior--,
				pSuperior = pSuperior->getSuperiorFibElement()  ){
			
		}
		if ( pSuperior == NULL ){
			cerr<<"Error: The to moved limbelement couldn't be found higher the move position."<<endl;
			iReturn++;
		}else{
			if ( iHowfar != iNumberOfSuperior ){
				cerr<<"Error: The moved limbelement is "<< -1 * iNumberOfSuperior<<
					" Fib elements hight than befor, but should be "<<
					-1 * iHowfar <<" Fib elements higher."<<endl;
				iReturn++;
			}
		}
		
	}else{
		//check if the moved limbelement can't move any further
		cFibElement * pSuperiorToMove = pMovedFibElement->getSuperiorFibElement();
		
		if ( pSuperiorToMove == NULL ){
			cout<<"Moved till the top of the Fib object."<<endl;
		}else if ( pSuperiorToMove->getType() == 'r' ){
			cout<<"Moved till the next root-element in the Fib object."<<endl;
		}else{
			set<cFibVariable*> setUsedVariables = pMovedFibElement->
				getUsedVariables( ED_POSITION );
			
			bool bDefiedVariableNeeded = false;
			for ( set<cFibVariable*>::iterator itrUsedVariable = setUsedVariables.begin();
					itrUsedVariable != setUsedVariables.end(); itrUsedVariable++ ){
				
				if ( pSuperiorToMove->isDefinedVariable( *itrUsedVariable, ED_POSITION ) ){
					bDefiedVariableNeeded = true;
					break;
				}
			}
			if ( ! bDefiedVariableNeeded ){
				cerr<<"Error: The moved limbelement should be moved "<<
					-1 * iHowfar <<" Fib elements hight than befor, but is moved "<<
					-1 * iElementsMovedOver <<" Fib elements higher, but it chould "<<
					"be moved still further."<<endl;
				iReturn++;
			}
		}
	}
	//check the created Fib object
	if ( uiNumberOfAllFibElements !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElements<<
			") in the created Fib object."<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElements !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElements<<
			") in the created Fib object."<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElements !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElements<<
			") in the created Fib object."<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElements !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElements !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElements !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElements !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElements !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if-elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElements !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElements !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElements !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElements !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElements !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}



/**
 * This function tests the moveLimbElement() method for a given Fib object.
 * It trys to move a limbelement in direction lower.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- intFib moveLimbElement( const char cType, const unsignedIntFib  elementPoint, const intFib iHowfar>=0, bool bAbsolute );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bAbsolute the bAbsolute value for moveLimbElement()
 * @return the number of erros occured in the test
 */
int testMoveLimbElementDownOnObject( cFibElement * pFibObject, bool bAbsolute ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( (pFibObject == NULL) || (pFibObject->getType() != 'r' ) ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );
	
	unsigned int uiNumberOfAllElementsInResult =
		uiNumberOfAllFibElements;
	unsigned int uiNumberOfPropertyElementsInResult =
		uiNumberOfPropertyElements;
	unsigned int uiNumberOfAreaElementsInResult =
		uiNumberOfAreaElements;
	unsigned int uiNumberOfFunctionElementsInResult =
		uiNumberOfFunctionElements;
	unsigned int uiNumberOfCommentElementsInResult =
		uiNumberOfCommentElements;
	unsigned int uiNumberOfSetElementsInResult =
		uiNumberOfSetElements;
	unsigned int uiNumberOfMatrixElementsInResult =
		uiNumberOfMatrixElements;

	//choos a rondom calling Fib element
	const unsigned int uiCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement = pFibObject->getFibElement( uiCallingFibElement );
	//check the getType() methode from cList
	if ( pCallingFibElement == NULL ){
		cerr<<"Error: The "<< uiCallingFibElement <<
			"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//choos random Fib limbelement
	char cType;
	unsigned int uiNumberOfElementsOfType = 0;
	unsignedIntFib uiElementPoint   = 0;
	cFibElement * pToMoveFibElement = NULL;
	
	for ( unsigned int uiRetry = 1; uiRetry <= uiNumberOfAllFibElements / 10 + 20;
			uiRetry++ ){
		cType = choosRandomType();
		if ( bAbsolute ){
			switch ( cType ){
				case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
				break;
				case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
				break;
				case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
				break;
				case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
				break;
				case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
				break;
				case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
				break;
				case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
				break;
				case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
				break;
				case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
				break;
				case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
				break;
				case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
				break;
				case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
				break;
				case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
				break;
			}
		}else{
			uiNumberOfElementsOfType =
				pCallingFibElement->getNumberOfElements( cType );
		}
		uiElementPoint = rand() % ( uiNumberOfElementsOfType + 3 );
		
		pToMoveFibElement = pCallingFibElement->getFibElement( cType, uiElementPoint, bAbsolute );
		
		if ( (pToMoveFibElement != NULL) && ( pToMoveFibElement->isLimb() ) &&
				( pToMoveFibElement->getType() != 'c' ) ){
			//movebel Fib element found
			//TODO: move a comment element
			break;
		}
	}
	if ( (pToMoveFibElement == NULL) || ( ! pToMoveFibElement->isLimb() ) ||
			( pToMoveFibElement->getType() == 'c' ) ){
		//can't move Fib element -> skip
		cout<<"Couldn't choos a limbelement to move."<<endl;
		return iReturn;
	}
	unsigned int uiNumberOfToMoveElement = pToMoveFibElement->getNumberOfElement();
	char cTypeOfToMoveElement = pToMoveFibElement->getType();
	//mark the choosen limbelement with a new variable
	cRoot * pNextRoot = (cRoot*)pToMoveFibElement->getFibElement( 'r', -1 );
	
	pNextRoot->setNumberOfInputVariables(
		pNextRoot->getNumberOfInputVariables() + 1 );
	cFibVariable * pVariableMarker = pNextRoot->getInputVariable(
		pNextRoot->getNumberOfInputVariables() );
	
	switch ( pToMoveFibElement->getType() ){
		case 'y':{
			cProperty * pChoosenProperty = (cProperty*)pToMoveFibElement;
			if ( pChoosenProperty->getProperty()->getNumberOfElements() == 0){
				//can't mark the property element -> skip this test
				cout<<"Propertyelement with 0 vector elements choosen -> skip moving."<<endl;
				return iReturn;
			}
			pChoosenProperty->getProperty()->setVariable( 1, pVariableMarker );
		}break;
		case 'a':{
			cArea * pChoosenArea = (cArea*)pToMoveFibElement;
			pChoosenArea->getSubarea( 1 )->setVariable( 1, pVariableMarker );
		}break;
		case 'f':{
			cFunction * pChoosenFunction = (cFunction*)pToMoveFibElement;
			
			cFunctionVariable functionVariable( pVariableMarker );
			pChoosenFunction->setUnderFunction( functionVariable );
		}break;
		case 'v':{
			cFibSet * pChoosenSetElement = (cFibSet*)pToMoveFibElement;
			
			if ( pChoosenSetElement->getVector( 1 )->getNumberOfElements() == 0 ){
				//can't marke Fib element -> skip
				cout<<"Couldn't mark the set-element with a variable (no vector elements)."<<endl;
				return iReturn;
			}
			
			pChoosenSetElement->getVector( 1 )->setVariable( 1, pVariableMarker );
		}break;
		case 'm':{
			cFibMatrix * pChoosenMatrixElement = (cFibMatrix*)pToMoveFibElement;
			
			pChoosenMatrixElement->getArea( 1 )->setVariable( 1, pVariableMarker );
		}break;
		//TODO more limb elements
	}
	
	//choose howfar to move the Fib element
	intFib iHowfar = 0;
	if ( rand() % 3 < 2 ){
		iHowfar = (rand() % 10);
	}else{
		iHowfar = (rand() % uiNumberOfAllFibElements);
	}
	
	//store using elements of the variables, to check that they didn't change
	list< pair< cFibVariable*, set<cFibElement*> > > liOriginalDefinedVariables;
	list<cFibVariable*> liDefinedVariables =
		pToMoveFibElement->getDefinedVariables( ED_POSITION );
	
	for ( list<cFibVariable*>::iterator itrDefinedVariable = liDefinedVariables.begin();
			itrDefinedVariable != liDefinedVariables.end(); itrDefinedVariable++ ){
		
		liOriginalDefinedVariables.push_back( make_pair( (*itrDefinedVariable),
			(*itrDefinedVariable)->getUsingElements() ) );
	}
	
	//call moveLimbElement()
	cout<<"Calling moveLimbElement( cType='"<< cType <<"', elementPoint="<<
		uiElementPoint <<", iHowfar="<< iHowfar <<", bAbsolute="<<
		(bAbsolute?"true":"false") <<") from the "<< pCallingFibElement->getNumberOfElement() <<
		" Fib element with the type "<<
		pCallingFibElement->getType() <<" in the Fib object,"<<
		"to move the "<< uiNumberOfToMoveElement <<"'th Fib element."<<endl;
	
	const intFib iElementsMovedOver = pCallingFibElement->moveLimbElement(
		cType, uiElementPoint, iHowfar, bAbsolute );
	
	cout<<"Fib element moved "<< iElementsMovedOver <<" steps down."<<endl;
	/*test if the limbelement is moved up the correct number of steps*/
	set<cFibElement*> setMovedElements = pVariableMarker->getUsingElements();
	
	uiNumberOfAllElementsInResult =
		uiNumberOfAllFibElements - 1 + setMovedElements.size();
	switch ( cTypeOfToMoveElement ){
		case 'y':
			uiNumberOfPropertyElementsInResult =
				uiNumberOfPropertyElements - 1 + setMovedElements.size();
		break;
		case 'a':
			uiNumberOfAreaElementsInResult =
				uiNumberOfAreaElements - 1 + setMovedElements.size();
		break;
		case 'f':
			uiNumberOfFunctionElementsInResult =
				uiNumberOfFunctionElements - 1 + setMovedElements.size();
		break;
		case 'v':
			uiNumberOfSetElementsInResult =
				uiNumberOfSetElements - 1 + setMovedElements.size();
		break;
		case 'm':
			uiNumberOfMatrixElementsInResult =
				uiNumberOfMatrixElements - 1 + setMovedElements.size();
		break;
	}
	
	if ( setMovedElements.empty() ){
		cerr<<"Error: After moving the limbelement ther are "<<
			setMovedElements.size() <<" moved Fib elements."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//set moved over elements for thesting iElementsMovedOver
	set<cFibElement*> setAllMovedOverFibElements;
	
	cFibElement * pMovePosition = pFibObject->getFibElement( uiNumberOfToMoveElement );
	
	//check if every Fib element is moved iHowfar step down or can't be muved furter
	for ( set<cFibElement*>::iterator itrMovedFibElement = setMovedElements.begin();
			itrMovedFibElement != setMovedElements.end(); itrMovedFibElement++ ){
		
		int iElementsMovedOverActual = 0;
		cFibElement * pMovedFibElement = (*itrMovedFibElement);
		
		//evalue over how much elements the actual moved element was moved
		cFibElement * pSuperior;
		for ( pSuperior = pMovedFibElement;
				pSuperior != NULL;
				pSuperior = pSuperior->getSuperiorFibElement(),
				iElementsMovedOverActual++ ){
			
			if ( pSuperior != pMovedFibElement ){
				setAllMovedOverFibElements.insert( pSuperior );
			}
			if ( pSuperior == pMovePosition ){
				break;
			}
		}
		if ( pSuperior == NULL){
			cerr<<"Error: The moved Fib element with the number "<<
				pMovedFibElement->getNumberOfElement() <<
				" has not the move position higher."<<endl;
			iReturn++;
			iElementsMovedOverActual = 0;
		}
		
		if ( iHowfar != iElementsMovedOverActual ){
			
			//check if the moved limbelement can't move any further
			cFibElement * pNextToMove = pMovedFibElement->getNextFibElement();
			
			if ( pNextToMove == NULL ){
				cout<<"Moved till the last Fib element of the Fib object."<<endl;
			}else if ( pNextToMove->getType() == 'r' ){
				cout<<"Moved till the next root-element in the Fib object."<<endl;
			}else if ( ( pNextToMove->getType() == 'o' ) &&
					( ((cExtObject*)(pNextToMove))->getNumberOfSubobjects() == 0 ) ){
				cout<<"Moved till the next external object leaf element "<<
					"(it has no subobjects) in the Fib object."<<endl;
			}else if ( pNextToMove->isLeaf() ){
				cout<<"Moved till the next leaf element in the Fib subobject."<<endl;
			}else{
				set<cFibVariable*> setUsedVariables =
					pNextToMove->getUsedVariables( ED_POSITION );
				
				bool bDefiedVariableNeeded = false;
				for ( set<cFibVariable*>::iterator itrUsedVariable = setUsedVariables.begin();
						itrUsedVariable != setUsedVariables.end(); itrUsedVariable++ ){
					
					if ( pMovedFibElement->isDefinedVariable( *itrUsedVariable, ED_POSITION ) ){
						bDefiedVariableNeeded = true;
						break;
					}
				}
				if ( ! bDefiedVariableNeeded ){
					cerr<<"Error: The moved limbelement with the number "<<
						pMovedFibElement->getNumberOfElement()<<" should be moved "<<
						iHowfar <<" Fib elements lower than befor, but is moved "<<
						iElementsMovedOverActual <<" Fib elements lower, but it chould "<<
						"be moved still further (its next Fib element is has the number "<<
						pNextToMove->getNumberOfElement()<<" and the type "<<
						pNextToMove->getType()<<")."<<endl;
					iReturn++;
				}
			}
		}
		//check if all defined variables are still ther and used in the same places
		liDefinedVariables = pMovedFibElement->getDefinedVariables( ED_POSITION );
		
		if ( liDefinedVariables.size() != liOriginalDefinedVariables.size() ){
			cerr<<"Error: The moved limbelement with the number "<<
				pMovedFibElement->getNumberOfElement()<<" defines "<<
				liDefinedVariables.size() <<", but should define "<<
				liOriginalDefinedVariables.size() <<" variables."<<endl;
			iReturn++;
		}
		list< pair< cFibVariable*, set<cFibElement*> > >::iterator itrOriginalVariable =
			liOriginalDefinedVariables.begin();
		for ( list<cFibVariable*>::iterator itrDefinedVariable = liDefinedVariables.begin();
				(itrDefinedVariable != liDefinedVariables.end()) &&
				( itrOriginalVariable != liOriginalDefinedVariables.end() ) ;
				itrDefinedVariable++, itrOriginalVariable++ ){
			
			set<cFibElement*> setUsingElements = (*itrDefinedVariable)->getUsingElements();
			
			for ( set<cFibElement*>::iterator itrUsingElement = setUsingElements.begin();
					itrUsingElement != setUsingElements.end(); itrUsingElement++ ){
				
				const int iErased = itrOriginalVariable->second.erase( *itrUsingElement );
				if ( iErased != 1 ){
					cerr<<"Error: The moved limbelement with the number "<<
						pMovedFibElement->getNumberOfElement()<<" defines a variable "<<
						"that is used in a Fib element wher it wasn't used befor moving."<<endl;
					iReturn++;
				}
			}
		}
	}
	if ( (int)(setAllMovedOverFibElements.size()) != iElementsMovedOver ){
		cerr<<"Error: The moved Fib element was moved over "<<
			setAllMovedOverFibElements.size() <<" Fib elements, but "<<
			"moveLimbElement() gave back "<< iElementsMovedOver <<" Fib elements."<<endl;
		iReturn++;
	}
	/*check all variables used in the Fib object over the position wher to
	move from are defined higher*/
	unsigned int uiNumberOfElementsToCheck = pMovePosition->getNumberOfElements();
	for ( cFibElement * pActualElement =  pMovePosition;
			(pActualElement != NULL) && (0 < uiNumberOfElementsToCheck);
			pActualElement = pActualElement->getNextFibElement(),
			uiNumberOfElementsToCheck-- ){
		
		if ( ! pActualElement->variablesAreDefined( pActualElement->
				getUsedVariables( ED_POSITION ) , ED_HIGHER ) ){
			cerr<<"Error: Some variables used in the "<<
				pActualElement->getNumberOfElement() <<"'th Fib element "<<
				"are not defined higher."<<endl;
			iReturn++;
		}
	}
	for ( list< pair< cFibVariable*, set<cFibElement*> > >::iterator itrOriginalVariable =
				liOriginalDefinedVariables.begin();
			itrOriginalVariable != liOriginalDefinedVariables.end() ;
			itrOriginalVariable++ ){
		
		if ( ! itrOriginalVariable->second.empty() ){
			cerr<<"Error: Ther are Fib elements that used variables, the "<<
				"moved Fib element defined, befor moving, but not afterwards."<<endl;
			iReturn++;
		}
	}

	//check the created Fib object
	if ( uiNumberOfAllElementsInResult !=
			pFibObject->getNumberOfElements() ){
		cerr<<"Error: The number of Fib elements "<<
			pFibObject->getNumberOfElements() <<
			" isn't correct ("<< uiNumberOfAllFibElements<<
			") in the created Fib object."<< endl;
		iReturn++;
	}
	if ( uiNumberOfRootElements !=
			pFibObject->getNumberOfElements( 'r' ) ){
		cerr<<"Error: The number of root-elements "<<
			pFibObject->getNumberOfElements( 'r' ) <<
			" isn't correct ("<< uiNumberOfRootElements<<
			") in the created Fib object."<< endl;
		iReturn++;
	}
	if ( uiNumberOfPointElements !=
			pFibObject->getNumberOfElements( 'p' ) ){
		cerr<<"Error: The number of point elements "<<
			pFibObject->getNumberOfElements( 'p' ) <<
			" isn't correct ("<< uiNumberOfPointElements<<
			") in the created Fib object."<< endl;
		iReturn++;
	}
	if ( uiNumberOfListElements !=
			pFibObject->getNumberOfElements( 'l' ) ){
		cerr<<"Error: The number of list elements "<<
			pFibObject->getNumberOfElements( 'l' ) <<
			" isn't correct ("<< uiNumberOfListElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfPropertyElementsInResult !=
			pFibObject->getNumberOfElements( 'y' ) ){
		cerr<<"Error: The number of property elements "<<
			pFibObject->getNumberOfElements( 'y' ) <<
			" isn't correct ("<< uiNumberOfPropertyElementsInResult<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfAreaElementsInResult !=
			pFibObject->getNumberOfElements( 'a' ) ){
		cerr<<"Error: The number of area elements "<<
			pFibObject->getNumberOfElements( 'a' ) <<
			" isn't correct ("<< uiNumberOfAreaElementsInResult<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfFunctionElementsInResult !=
			pFibObject->getNumberOfElements( 'f' ) ){
		cerr<<"Error: The number of function elements "<<
			pFibObject->getNumberOfElements( 'f' ) <<
			" isn't correct ("<< uiNumberOfFunctionElementsInResult<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfIfElements !=
			pFibObject->getNumberOfElements( 'i' ) ){
		cerr<<"Error: The number of if-elements "<<
			pFibObject->getNumberOfElements( 'i' ) <<
			" isn't correct ("<< uiNumberOfIfElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfCommentElementsInResult !=
			pFibObject->getNumberOfElements( 'c' ) ){
		cerr<<"Error: The number of comment elements "<<
			pFibObject->getNumberOfElements( 'c' ) <<
			" isn't correct ("<< uiNumberOfCommentElementsInResult<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtObjectElements !=
			pFibObject->getNumberOfElements( 'o' ) ){
		cerr<<"Error: The number of external object elements "<<
			pFibObject->getNumberOfElements( 'o' ) <<
			" isn't correct ("<< uiNumberOfExtObjectElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfExtSubobjectElements !=
			pFibObject->getNumberOfElements( 's' ) ){
		cerr<<"Error: The number of external subobject elements "<<
			pFibObject->getNumberOfElements( 's' ) <<
			" isn't correct ("<< uiNumberOfExtSubobjectElements<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfSetElementsInResult !=
			pFibObject->getNumberOfElements( 'v' ) ){
		cerr<<"Error: The number of set elements "<<
			pFibObject->getNumberOfElements( 'v' ) <<
			" isn't correct ("<< uiNumberOfSetElementsInResult<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	if ( uiNumberOfMatrixElementsInResult !=
			pFibObject->getNumberOfElements( 'm' ) ){
		cerr<<"Error: The number of matrix elements "<<
			pFibObject->getNumberOfElements( 'm' ) <<
			" isn't correct ("<< uiNumberOfMatrixElementsInResult<<
			") in the created Fib object."<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject, false );
	}else{//print some more information about the checked Fib object
		iReturn += testStructurOnObject( pFibObject, true );
	}

	return iReturn;
}



/**
 * This function tests the clone() method for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- cFibElement *clone() const;
 *
 * (Nothing to change for different Fib elements.)
 *
 * @param pFibObject1 a pointer to the first Fib object to test
 * @param pFibObject2 a pointer to the second Fib object to test,
 * 	which is equal to pFibObject1
 * @return the number of erros occured in the test
 */
int testCloneOnObject( cFibElement * pFibObject1, cFibElement * pFibObject2 ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( (pFibObject1 == NULL) || (pFibObject2 == NULL) ){
		cerr<<"Error: No Fib objects to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject1->getNumberOfElements();
	
	//choos a rondom calling Fib element
	const unsigned int uiCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement = pFibObject1->getFibElement( uiCallingFibElement );
	//check the getType() methode from cList
	if ( pCallingFibElement == NULL ){
		cerr<<"Error: The "<< uiCallingFibElement <<
			"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cout<<"Calling clone() from the "<< uiNumberOfAllFibElements <<
		" Fib element with the type "<<
		pCallingFibElement->getType() <<" in the Fib object."<<endl;
	
	cFibElement * pFibObjectClone = pCallingFibElement->clone();
	
	if ( pFibObjectClone == NULL ){
		cerr<<"Error: The Fib object couldn't be cloned. (NULL returned)"<<endl;
		iReturn++;
		return iReturn;
	}
	
	if ( ! pFibObjectClone->equal( *pFibObject2 ) ){
		cerr<<"Error: The Fib object clone isn't equal to the original Fib object."<<endl;
		iReturn++;
	}
	if ( ! pFibObject1->equal( *pFibObject2 ) ){
		cerr<<"Error: The Fib object which was cloned isn't equal to the original Fib object."<<endl;
		iReturn++;
	}
	
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObjectClone, false );
	}else{//print some more information about the checked Fib object
		cout<<"Checking clone:"<<endl;
		iReturn += testStructurOnObject( pFibObjectClone, true );
	}
	if ( iReturn == 0 ){
		iReturn += testStructurOnObject( pFibObject1, false );
	}else{//print some more information about the checked Fib object
		cout<<"Checking cloned:"<<endl;
		iReturn += testStructurOnObject( pFibObject1, true );
	}
	pFibObjectClone->deleteObject();
	
	return iReturn;
}



/**
 * This method tests if the given Fib element is not conected to other
 * Fib elements.
 *
 * @param fibObject1 the Fib element to check
 * @return the number of errors occured in the test
 */
int testNotConnectedFibElement( const cFibElement &fibObject1 ){
	
	int iReturn=0;//return value of the test; the number of occured errors
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() == 1 ){
	
		cout<<"The Fib object includes just one Fib element."<<endl;
	}else{
		cerr<<"Error: The Fib object includes just not one Fib element, but "<<
			const_cast<cFibElement*>(&fibObject1)->getNumberOfElements() <<" ."<<endl;
		iReturn++;
	}
	
	//check the getNextFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getNextFibElement() == NULL ){
	
		cout<<"The next/ main Fib element pointer for the Fib elements is correctly NULL."<<endl;
	}else{
		cerr<<"Error: The next/ main Fib element pointer for the Fib elements is not NULL."<<endl;
		iReturn++;
	}
	//check the getFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getFibElement( -1 ) == NULL ){
	
		cout<<"The previous Fib element pointer for the Fib elements is correctly NULL."<<endl;
	}else{
		cerr<<"Error: The previous Fib element pointer for the Fib elements is not NULL."<<endl;
		iReturn++;
	}
	
	//check the getSuperiorFibElement() methode from cPoint
	if ( const_cast<cFibElement*>(&fibObject1)->getSuperiorFibElement() == NULL ){
	
		cout<<"The superior Fib element pointer for the Fib elements is correctly NULL."<<endl;
	}else{
		cerr<<"Error: The superior Fib element pointer for the Fib elements is not NULL."<<endl;
		iReturn++;
	}
	
	return iReturn;
}


/**
 * This function tests the copyElement() method for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- cFibElement *copyElement( const char cType, const unsignedIntFib elementPoint, bool bAbsolute ) const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @param bAbsolute the bAbsolute value for moveLimbElement()
 * @return the number of erros occured in the test
 */
int testCopyElementOnObject( cFibElement * pFibObject, bool bAbsolute ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( (pFibObject == NULL) || (pFibObject->getType() != 'r' ) ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );

	for ( unsigned int uiIteration = 1;
			uiIteration <= uiNumberOfAllFibElements / 100 + 10; uiIteration++ ){
		
		//choos a rondom calling Fib element
		const unsigned int uiCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
		const cFibElement * pCallingFibElement = pFibObject->getFibElement( uiCallingFibElement );
		//check the getType() methode from cList
		if ( pCallingFibElement == NULL ){
			cerr<<"Error: The "<< uiCallingFibElement <<
				"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
			iReturn++;
			continue;
		}
		
		//choos random Fib element
		char cType;
		unsigned int uiNumberOfElementsOfType = 0;
		unsignedIntFib uiElementPoint   = 0;
		cFibElement * pToCopyFibElement = NULL;
		
		cType = choosRandomType();
		if ( bAbsolute ){
			switch ( cType ){
				case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
				break;
				case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
				break;
				case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
				break;
				case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
				break;
				case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
				break;
				case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
				break;
				case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
				break;
				case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
				break;
				case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
				break;
				case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
				break;
				case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
				break;
				case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
				break;
				case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
				break;
			}
		}else{
			uiNumberOfElementsOfType =
				pCallingFibElement->getNumberOfElements( cType );
		}
		uiElementPoint = rand() % ( uiNumberOfElementsOfType + 3 );
		
		pToCopyFibElement = (const_cast<cFibElement*>(pCallingFibElement))->
			getFibElement( cType, uiElementPoint, bAbsolute );
		
		unsigned int uiNumberOfToCopyElement = 0;
		char cTypeToCopy = 'x';
		if ( pToCopyFibElement ){
			uiNumberOfToCopyElement = pToCopyFibElement->getNumberOfElement();
			cTypeToCopy = pToCopyFibElement->getType();
		}
		
		//copy the element
		cout<<"Calling copyElement( '"<<
			cType <<"', "<< uiElementPoint <<", bAbsolute="<<
			(bAbsolute?"true":"false") <<" ) from the "<<
			pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
			"(which is of type "<< pCallingFibElement->getType() <<"), "<<
			"to copy the "<< uiNumberOfToCopyElement <<"'th Fib element "<<
			"and has the type "<< cTypeToCopy <<" ."<<endl;

		cFibElement * pFibElementCopy = pCallingFibElement->copyElement( cType, uiElementPoint, bAbsolute );
		
		//check the copy
		cout<<"Checking copied Fib element:"<<endl;
		if ( pToCopyFibElement == NULL ){
			if ( pFibElementCopy ){
				cerr<<"Error: Ther was a Fib element number "<<
					pFibElementCopy->getNumberOfElement() <<
					"given back as the copy and not NULL."<<endl;
				iReturn++;
				delete pFibElementCopy;
			}else{
				cout<<"Ther is correctly no Fib element copied. (NULL was given back)"<<endl;
			}
			continue;
		}//else (pToCopyFibElement != NULL)
		
		if ( pFibElementCopy == NULL ){
			cerr<<"Error: Ther was no Fib element given back as the copy. (NULL returned)"<<endl;
			iReturn++;
			continue;
		}
		
		if ( pFibElementCopy->getType() != 'r' ){
		
			if ( ! pToCopyFibElement->equalElement( *pFibElementCopy ) ){
				cerr<<"Error: The copied Fib element is not equal to the to copy Fib element."<<endl;
				iReturn++;
			}
		}else{//root-element copies can't be compared with equalElement()
			//check if it is the same (equal() ) to calling the copyconstructor of the root-element
			cRoot * pRootCopy = new cRoot( *((cRoot*)pToCopyFibElement) );
			
			if ( ! pFibElementCopy->equalElement( *pRootCopy ) ){
				cerr<<"Error: The copied rootelement is not equal to the to copy rootelement."<<endl;
				iReturn++;
			}
			delete pRootCopy;
		}
		iReturn += testNotConnectedFibElement( *pFibElementCopy );
		
		delete pFibElementCopy;
	}
	return iReturn;
}


/**
 * This function tests the copy() method for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- cFibElement *copy( const unsignedIntFib iObjectPoint ) const;
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testCopyOnObject( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	
	//choos a rondom calling Fib element
	const unsigned int uiCallingFibElement = rand() % uiNumberOfAllFibElements + 1;
	cFibElement * pCallingFibElement = pFibObject->getFibElement( uiCallingFibElement );
	const cFibElement * pCallingFibElementConst = pFibObject->getFibElement( uiCallingFibElement );
	//check the getType() methode from cList
	if ( pCallingFibElement == NULL ){
		cerr<<"Error: The "<< uiCallingFibElement <<
			"'th Fib element of the Fib object couldn't be choosen as the calling."<<endl;
		iReturn++;
		return iReturn;
	}
	const unsigned int uiNumberOfObjectPoints =
		pCallingFibElement->getNumberOfObjectPoints();
	
	//choos random objectpoint
	const unsigned int uiObjectPoint = rand() % (uiNumberOfObjectPoints + 2);
	cFibElement * pDefiningFibElement = NULL;
	if ( uiObjectPoint <= uiNumberOfObjectPoints ){
		unsignedIntFib uiNumberOfDefiningElementFromCalling = pCallingFibElement->
			objectPointToElementPoint( uiObjectPoint );
		
		pDefiningFibElement = pCallingFibElement->getFibElement(
			uiNumberOfDefiningElementFromCalling );
	}
	unsigned int uiNumberOfDefiningElement = 0;
	//char cTypeOfDefiningElement = 'x';
	if ( pDefiningFibElement ){
		uiNumberOfDefiningElement = pDefiningFibElement->getNumberOfElement();
		//cTypeOfDefiningElement = pDefiningFibElement->getType();
	}
	
	//copy the element
	cout<<"Calling copy( "<< uiObjectPoint <<" ) from the "<<
		pCallingFibElement->getNumberOfElement()<<"'th Fib element "<<
		"(which is of type "<< pCallingFibElement->getType() <<"), "<<
		"to copy the part object which is defined with the "<<
		uiNumberOfDefiningElement <<"'th Fib element of type ("<<
		((pDefiningFibElement != NULL) ? pDefiningFibElement->getType() : '_')<<") ."<<endl;

	cFibElement * pFibObjectCopy = pCallingFibElementConst->copy( uiObjectPoint );
	
	//check the copy
	cout<<"Checking copied Fib object:"<<endl;
	
	if ( pFibObjectCopy == NULL ){
		
		if ( pDefiningFibElement == NULL ){
			cout<<"Correctly no Fib object copied. (NULL returned)"<<endl;
		}else{
			cerr<<"Error: Ther was no Fib object copied, but it should be copied one."<<endl;
			iReturn++;
		}
		return iReturn;
	}//else
	if ( pDefiningFibElement == NULL ){
		cerr<<"Error: Ther was an Fib object copied, but it shouldn't be copied one."<<endl;
		iReturn++;
		return iReturn;
	}
	
	cFibElement * pDefiningInCopy = pFibObjectCopy;
	if ( uiObjectPoint != 0 ){
		/*compare the Fib elements betwean the calling element/highest Fib element and the definingelements*/
		
		//get all the Fib elements betwan the calling and the defining Fib element
		list<cFibElement*> liWayToDefiningElement;
		liWayToDefiningElement.push_front( pDefiningFibElement );
		cFibElement * pSuperior = NULL;
		for ( pSuperior = pDefiningFibElement->getSuperiorFibElement();
				(pSuperior != NULL) && (pCallingFibElement != pSuperior);
				pSuperior = pSuperior->getSuperiorFibElement() ){
			/*cout<<"Fib element on way with number "<<pSuperior->getNumberOfElement()<<
				" and type "<<pSuperior->getType()<<endl;*/
			
			liWayToDefiningElement.push_front( pSuperior );
			
		}
		if ( pSuperior == NULL ){
			cerr<<"Error: No calling element found higher the defining element."<<endl;
			iReturn++;
		}
		if ( pCallingFibElement == pSuperior ){
			liWayToDefiningElement.push_front( pCallingFibElement );
		}
		
		cFibElement * pActualElementCopy = pFibObjectCopy;
		cFibElement * pActualElementOriginal = liWayToDefiningElement.front();
		while ( (pActualElementCopy != NULL) && (pActualElementOriginal != NULL) &&
				( ! liWayToDefiningElement.empty() ) ){
			
			pActualElementOriginal = liWayToDefiningElement.front();
			liWayToDefiningElement.pop_front();
			
			if ( ( pActualElementOriginal->getType() == 'l' ) ||
					( pActualElementOriginal->getType() == 'i' ) ){
				//skip lists and if-elements from the original, they won't be copied
				continue;
			}
			if ( ( pActualElementCopy->getType() != 'r' ) &&
					( pActualElementCopy->getType() != 'o' ) ){
				//compare the Fib elements without the links to external objects
				if ( ! pActualElementCopy->equalElement( *pActualElementOriginal, false ) ){
					cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
						"'th Fib element (type="<<pActualElementCopy->getType() <<
						") in the copy isn't equal to the "<<
						pActualElementOriginal->getNumberOfElement() <<"'th "<<
						"Fib element (type="<<pActualElementOriginal->getType() <<
						") in the original."<<endl;
					iReturn++;
				}
				if ( liWayToDefiningElement.empty() ){
					break;
				}
				pActualElementCopy = pActualElementCopy->getNextFibElement();
			}else{//check root-element subobjects or external object element
				
				if ( ( pActualElementCopy->getType() == 'r' ) &&
						( pActualElementOriginal->getType() == 'r' ) ){
					//check root-element subobjects
					cRoot * pActualRootCopy = (cRoot*)pActualElementCopy;
					cRoot * pActualRootOriginal = (cRoot*)pActualElementOriginal;
					//don't compare sub -root-objects
					cRoot * pActualRootCopySimple = new cRoot( *(pActualRootCopy) );
					cRoot * pActualRootOriginalSimple = new cRoot( *(pActualRootOriginal) );
	
					//compare the Fib elements without the links to external objects
					if ( ! pActualRootCopySimple->equalElement( *pActualRootOriginalSimple, false ) ){
						cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
							"'th Fib element (type="<<pActualElementCopy->getType() <<
							") in the copy isn't equal to the "<<
							pActualElementOriginal->getNumberOfElement() <<"'th "<<
							"Fib element (type="<<pActualElementOriginal->getType() <<
							") in the original."<<endl;
						iReturn++;
						
						if ( liWayToDefiningElement.empty() ){
							delete pActualRootCopySimple;
							delete pActualRootOriginalSimple;
							break;
						}
						pActualElementCopy = pActualElementCopy->getNextFibElement();
					}else //both are roots
						if ( liWayToDefiningElement.front()->getType() != 'r' ){
						//the objectpoint is in the main -Fib object
						//check the main Fib objects
						//check if all sub -root elements are equal
						if ( pActualRootCopy->getNumberOfSubRootObjects() ==
								pActualRootOriginal->getNumberOfSubRootObjects() ){
							for ( unsigned int uiActualSubRootObject = 1; uiActualSubRootObject <=
										pActualRootOriginal->getNumberOfSubRootObjects();
									uiActualSubRootObject++ ){
								
								pair<longFib, cRoot*> paSubRootObjectCopy =
									pActualRootCopy->getSubRootObject( uiActualSubRootObject );
								pair<longFib, cRoot*> paSubRootObjectOriginal =
									pActualRootOriginal->getSubRootObject( uiActualSubRootObject );
								
								//compare the Fib objects without the links to external objects
								if ( ! paSubRootObjectCopy.second->equal(
										*(paSubRootObjectOriginal.second), false ) ){
									cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
										"'th rootelement (type="<<pActualElementCopy->getType() <<
										") in the copy isn't equal to the "<<
										pActualElementOriginal->getNumberOfElement() <<"'th "<<
										"rootelement (type="<< pActualElementOriginal->getType() <<
										") in the original."<<endl;
									cerr<<"   The "<< uiActualSubRootObject <<
										"'th sub -rootobjects arn't equal."<<endl;
									iReturn++;
								}
							}
						}else{
							cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
								"'th Fib element (type="<<pActualElementCopy->getType() <<
								") in the copy isn't equal to the "<<
								pActualElementOriginal->getNumberOfElement() <<"'th "<<
								"Fib element (type="<<pActualElementOriginal->getType() <<
								") in the original."<<endl;
							cerr<<"   The rootelement copy has "<<
								pActualRootCopy->getNumberOfSubRootObjects() <<
								" sub -rootobjects but the original has "<<
								pActualRootOriginal->getNumberOfSubRootObjects() <<" ."<<endl;
							iReturn++;
						}
						if ( liWayToDefiningElement.empty() ){
							delete pActualRootCopySimple;
							delete pActualRootOriginalSimple;
							break;
						}
						pActualElementCopy = pActualElementCopy->getNextFibElement();
					}else{//the objectpoint is in a sub -root-object
						//compare the main -Fib objects
						cFibElement * pMainFibObjectCopy = pActualRootCopy->getNextFibElement();
						cFibElement * pMainFibObjectOriginal = pActualRootOriginal->getNextFibElement();
						//compare the Fib objects without the links to external objects
						if ( ! pMainFibObjectCopy->equal( *pMainFibObjectOriginal, false ) ){
							cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
								"'th rootelement (type="<<pActualElementCopy->getType() <<
								") in the copy isn't equal to the "<<
								pActualElementOriginal->getNumberOfElement() <<"'th "<<
								"rootelement (type="<<pActualElementOriginal->getType() <<
								") in the original."<<endl;
							cerr<<"   The main -Fib objects arn't equal."<<endl;
							iReturn++;
						}
						//go to the rootelement in the copied sub -root-object
						if ( liWayToDefiningElement.empty() ){
							delete pActualRootCopySimple;
							delete pActualRootOriginalSimple;
							break;
						}
						pActualElementCopy = (pActualRootCopy->getSubRootObject( 1 )).second;
					}
					delete pActualRootCopySimple;
					delete pActualRootOriginalSimple;
				}else if ( ( pActualElementCopy->getType() == 'o' ) &&
						( pActualElementOriginal->getType() == 'o' ) ){//check external object subobjects
					
					if ( pDefiningFibElement == pActualElementOriginal ){
						/*the external object element is the defining Fib element
						-> the entire external object element Fib object was copied*/
						if ( ! pActualElementCopy->equalElement( *pActualElementOriginal, false ) ){
							cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
								"'th Fib element (type="<<pActualElementCopy->getType() <<
								") in the copy isn't equal to the "<<
								pActualElementOriginal->getNumberOfElement() <<"'th "<<
								"Fib element (type="<<pActualElementOriginal->getType() <<
								") in the original."<<endl;
							iReturn++;
						}
					}else{/*the external object element is not the defining Fib element
						-> the just one subobject of the external object element was copied*/
						
						cExtObject * pActualExtObjCopy = (cExtObject*)pActualElementCopy;
						cExtObject * pActualExtObjOriginal = (cExtObject*)pActualElementOriginal;
						//compare the identifier
						if ( pActualExtObjCopy->getIdentifier() != pActualExtObjOriginal->getIdentifier() ){
							cerr<<"Error: The external object elements have not the same identifier."<<endl;
							cerr<<" number of copy external object element: "<< pActualElementCopy->getNumberOfElement() <<
								"; number of original external object element: "<<pActualElementOriginal->getNumberOfElement()<<endl;
							cerr<<" identifier of copy external object element: "<< pActualExtObjCopy->getIdentifier() <<
								"; identifier of original external object element: "<<pActualExtObjOriginal->getIdentifier()<<endl;
							iReturn++;
						}
						
						//compare the input values
						if ( ! pActualExtObjCopy->getInputVector()->equal(
								*(pActualExtObjOriginal->getInputVector()) ) ){
							cerr<<"Error: The external object elements have not the same input variables."<<endl;
							cerr<<" number of copy external object element: "<< pActualElementCopy->getNumberOfElement() <<
								"; number of original external object element: "<<pActualElementOriginal->getNumberOfElement()<<endl;
							cerr<<"input values of copy external object element:"<<endl;
							pActualExtObjCopy->getInputVector()->storeXml( cerr );
							cerr<<"input values of original external object element:"<<endl;
							pActualExtObjOriginal->getInputVector()->storeXml( cerr );
							iReturn++;
						}
						
						/*the external object element in the copy has just one subobject,
						the correcpondending subobject in the original is liWayToDefiningElement.front()*/
						//find liWayToDefiningElement.front() in pActualExtObjOriginal
						unsignedIntFib uiSubobject = 1;
						cFibElement * pSubObjectOnWay = liWayToDefiningElement.front();
						for ( ; uiSubobject <= pActualExtObjOriginal->getNumberOfSubobjects();
								uiSubobject++ ){
							
							if ( pActualExtObjOriginal->getSubobject(
									uiSubobject ) == pSubObjectOnWay ){
								break;
							}
						}
						if ( pActualExtObjOriginal->getNumberOfSubobjects() < uiSubobject ){
							cerr<<"Error: The original external object elements has not the "<<
								"next Fib element on the way ("<<pSubObjectOnWay<<
								" with number"<<pSubObjectOnWay->getNumberOfElement()<<
								" and type "<<pSubObjectOnWay->getType()<<
								") as its subobject (it has "<<
								pActualExtObjOriginal->getNumberOfSubobjects()<<" subobjects)."<<endl;
							cerr<<" number of copy external object element: "<< pActualElementCopy->getNumberOfElement() <<
								"; number of original external object element: "<<pActualElementOriginal->getNumberOfElement()<<endl;
							iReturn++;
						}else{
							//check if copy external object element has just uiSubobject subobject
							if ( pActualExtObjCopy->getNumberOfSubobjects() != uiSubobject ){
								cerr<<"Error: The copy external object element has not "<<uiSubobject<<" subobject, it has "<<
									pActualExtObjCopy->getNumberOfSubobjects()<<" subobjects."<<endl;
								iReturn++;
							}
							//check if all except the copied subobjects are NULL
							for ( unsignedIntFib uiActualSubobject = 0;
									uiActualSubobject < uiSubobject;
									uiActualSubobject++ ){
								
								if ( pActualExtObjCopy->getSubobject( uiActualSubobject ) != NULL ){
									cerr<<"Error: The copy external object element has as the "<<
										uiActualSubobject<<" subobject not NULL."<<endl;
									iReturn++;
								}
								if ( pActualExtObjCopy->getNumberOfOutputVariables( uiActualSubobject ) != 0 ){
									cerr<<"Error: The copy external object element has for the "<<
										uiActualSubobject<<" subobject output variables."<<endl;
									iReturn++;
								}
							}
							//compare number of there output variables
							if ( pActualExtObjCopy->getNumberOfOutputVariables( uiSubobject ) !=
									pActualExtObjOriginal->getNumberOfOutputVariables( uiSubobject ) ){
								cerr<<"Error: The external object elements have not the same number of output variables."<<endl;
								cerr<<" number of copy external object element: "<< pActualElementCopy->getNumberOfElement() <<
									"; number of original external object element: "<<pActualElementOriginal->getNumberOfElement()<<endl;
								cerr<<" number of output variables of copy external object element for the first subobject: "<<
										pActualExtObjCopy->getNumberOfOutputVariables( 1 ) <<
									"; number of output variables of original external object element for the "<<
									uiSubobject<<"'th subobject: "<<pActualExtObjOriginal->getNumberOfOutputVariables( uiSubobject )<<endl;
								iReturn++;
							}
						}
					}
					if ( liWayToDefiningElement.empty() ){
						break;
					}
					pActualElementCopy = pActualElementCopy->getNextFibElement();
				}else{
					cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
						"'th Fib element (type="<<pActualElementCopy->getType() <<
						") in the copy isn't equal to the "<<
						pActualElementOriginal->getNumberOfElement() <<"'th "<<
						"Fib element (type="<<pActualElementOriginal->getType() <<
						") in the original, because they have different typs."<<endl;
					iReturn++;
					
					if ( liWayToDefiningElement.empty() ){
						break;
					}
					pActualElementCopy = pActualElementCopy->getNextFibElement();
				}
			}
		}
		if ( pActualElementOriginal == NULL ){
			//error
			cerr<<"Error: The "<< pActualElementCopy->getNumberOfElement() <<
				"'th Fib element in the copy hasn't an equivalent Fib element "<<
				"in the original. (NULL was reached)"<<endl;
			iReturn++;
		}
		if ( pActualElementCopy == NULL ){
			//error
			cerr<<"Error: The "<< pActualElementOriginal->getNumberOfElement() <<
				"'th Fib element in the original hasn't an equivalent Fib element "<<
				"in the copy. (NULL was reached)"<<endl;
			iReturn++;
		}else{
			/*store the Fib element equivallant to the definingelement in the copied Fib objects*/
			pDefiningInCopy = pActualElementCopy;
		}
	}
	
	//check the part object under the defining elements
	if ( pDefiningInCopy ){
		//compare the Fib objects without the links to external objects
		if ( ! pDefiningInCopy->equal( *pDefiningFibElement, false ) ){
			cerr<<"Error: The Fib object of the "<< pDefiningInCopy->getNumberOfElement() <<
				"'th Fib element in the copy isn't equal to the Fib object of the "<<
				pDefiningFibElement->getNumberOfElement() <<"'th "<<
				"Fib element in the original. (definig original != defining copy)"<<endl;
			iReturn++;
			//store a file for the copied object with the error
			static unsigned int uiErrorFile = 0;
			uiErrorFile++;
			char szFileNameBuffer[256];
			sprintf ( szFileNameBuffer, "%s%s%uI%s",
				DIR_OUTPUT, "copyObjError", uiErrorFile ,".xml" );
				
			cerr<<"Error: The Fib object copy where the error occured will be writen to the file \""<< szFileNameBuffer <<"\" ."<<endl;
			
			ofstream * pFile = new ofstream( szFileNameBuffer );
			
			bool bStoreSuccesfull = pFibObjectCopy->storeXml( *pFile );
			delete pFile;
			
			if ( ! bStoreSuccesfull ){
	
				cerr<<"Error: Storing the data of the generated Fib object to the file \""<< szFileNameBuffer <<"\" failed."<<endl;
				iReturn++;
			}
		}
	}
	
	cFibElement::deleteObject( pFibObjectCopy );
	
	return iReturn;
}



/**
 * This function tests the assignValues() methods for a given Fib object.
 * ATTENTION: The random number generator should to be initialisized with srand()
 *
 * methods tested:
 * 	- bool assignValues( const cFibElement & fibElement );
 *
 * Fib elements tested:
 * 	- cRoot
 * 	- cList
 * 	- cPoint
 * 	- cProperty
 * 	- cArea
 * 	- cFunction
 * 	- cIf
 * 	- cComment
 * 	- cExtObject
 * 	- cExtSubobject
 * 	- cFibSet
 * 	- cFibMatrix
 *
 * @param pFibObject a pointer to the Fib object to test
 * @return the number of erros occured in the test
 */
int testAssignValues( cFibElement * pFibObject ){

	int iReturn = 0;//return value of the test; the number of occured errors
	
	if ( pFibObject == NULL ){
		cerr<<"Error: No Fib object to check ."<<endl;
		iReturn++;
		return iReturn;
	}
	//evalue the count values of the given Fib object
	const unsigned int uiNumberOfAllFibElements =
		pFibObject->getNumberOfElements();
	const unsigned int uiNumberOfRootElements =
		pFibObject->getNumberOfElements( 'r' );
	const unsigned int uiNumberOfPointElements =
		pFibObject->getNumberOfElements( 'p' );
	const unsigned int uiNumberOfListElements =
		pFibObject->getNumberOfElements( 'l' );
	const unsigned int uiNumberOfPropertyElements =
		pFibObject->getNumberOfElements( 'y' );
	const unsigned int uiNumberOfAreaElements =
		pFibObject->getNumberOfElements( 'a' );
	const unsigned int uiNumberOfFunctionElements =
		pFibObject->getNumberOfElements( 'f' );
	const unsigned int uiNumberOfIfElements =
		pFibObject->getNumberOfElements( 'i' );
	const unsigned int uiNumberOfCommentElements =
		pFibObject->getNumberOfElements( 'c' );
	const unsigned int uiNumberOfExtObjectElements =
		pFibObject->getNumberOfElements( 'o' );
	const unsigned int uiNumberOfExtSubobjectElements =
		pFibObject->getNumberOfElements( 's' );
	const unsigned int uiNumberOfSetElements =
		pFibObject->getNumberOfElements( 'v' );
	const unsigned int uiNumberOfMatrixElements =
		pFibObject->getNumberOfElements( 'm' );

	
	//choos random Fib element to assign
	char cType;
	unsigned int uiNumberOfElementsOfType = 0;
	unsignedIntFib uiElementPoint = 0;
	
	while ( uiNumberOfElementsOfType == 0 ){
		cType = choosRandomType();
		switch ( cType ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
	}//end while choose element
	uiElementPoint = 1 + rand() % uiNumberOfElementsOfType;
	
	cFibElement * pToAssignFibElement =
		(const_cast<cFibElement*>(pFibObject))->
			getFibElement( cType, uiElementPoint );
	
	if ( pToAssignFibElement == NULL ){
		cerr<<"Error: Could not choose to assign from Fib element."<<endl;
		iReturn++;
		return iReturn;
	}
	const unsigned int uiNumberOfToAssignElement =
		pToAssignFibElement->getNumberOfElement();
	const char cTypeToAssign = pToAssignFibElement->getType();
	
	uiNumberOfElementsOfType = 0;
	while ( uiNumberOfElementsOfType == 0 ){
		
		if ( ( rand() % 3 ) != 0 ){
			//choos random Fib element to assign to
			cType = choosRandomType();
		}//else choose Fib element of the same type
		switch ( cType ){
			case 'u':uiNumberOfElementsOfType = uiNumberOfAllFibElements;
			break;
			case 'r':uiNumberOfElementsOfType = uiNumberOfRootElements;
			break;
			case 'p':uiNumberOfElementsOfType = uiNumberOfPointElements;
			break;
			case 'l':uiNumberOfElementsOfType = uiNumberOfListElements;
			break;
			case 'y':uiNumberOfElementsOfType = uiNumberOfPropertyElements;
			break;
			case 'a':uiNumberOfElementsOfType = uiNumberOfAreaElements;
			break;
			case 'f':uiNumberOfElementsOfType = uiNumberOfFunctionElements;
			break;
			case 'i':uiNumberOfElementsOfType = uiNumberOfIfElements;
			break;
			case 'c':uiNumberOfElementsOfType = uiNumberOfCommentElements;
			break;
			case 'o':uiNumberOfElementsOfType = uiNumberOfExtObjectElements;
			break;
			case 's':uiNumberOfElementsOfType = uiNumberOfExtSubobjectElements;
			break;
			case 'v':uiNumberOfElementsOfType = uiNumberOfSetElements;
			break;
			case 'm':uiNumberOfElementsOfType = uiNumberOfMatrixElements;
			break;
		}
	}//end while choose element
	uiElementPoint = 1 + rand() % uiNumberOfElementsOfType;
	
	cFibElement * pToAssignToFibElement =
		(const_cast<cFibElement*>(pFibObject))->
			getFibElement( cType, uiElementPoint );
	if ( pToAssignToFibElement == NULL ){
		cerr<<"Error: Could not choose to assign to Fib element."<<endl;
		iReturn++;
		return iReturn;
	}
	
	const unsigned int uiNumberOfToAssignToElement =
		pToAssignToFibElement->getNumberOfElement();
	const char cTypeToAssignTo = pToAssignToFibElement->getType();
	
	
	//evalue if the element values can be assigned
	bool bValuesCanBeAssigned = true;
	//check if Fib elements of same type
	if ( cTypeToAssign != cTypeToAssignTo ){
		//Fib elements not of same type -> can not assign values
		bValuesCanBeAssigned = false;
	}
	if ( bValuesCanBeAssigned ){
		/*check if all used variables in the to assign from Fib element
		 have equal defined variables above the to assign to Fib element*/
		set<cFibVariable*> setUsedVariablesToAssign =
			pToAssignFibElement->getUsedVariables( ED_POSITION );
		
		list<cFibVariable*> liDefinedVariablesAboveToAssignTo =
			pToAssignToFibElement->getDefinedVariables( ED_HIGHER );
		for ( list<cFibVariable*>::iterator
				itrDefVariable = liDefinedVariablesAboveToAssignTo.begin();
				itrDefVariable != liDefinedVariablesAboveToAssignTo.end();
				itrDefVariable++ ){
			
			for ( set<cFibVariable*>::iterator
					itrUsedVariable = setUsedVariablesToAssign.begin();
					itrUsedVariable != setUsedVariablesToAssign.end();
					itrUsedVariable++ ){
				if ( (*itrDefVariable)->equal( **itrUsedVariable ) ){
					//equal variable defined above
					setUsedVariablesToAssign.erase( itrUsedVariable );
					break;//check next defined variable
				}
			}//for all used variables
		}//end for all defined variables
		if ( ! setUsedVariablesToAssign.empty() ){
			/*some variables used in the to assign Fib element have not
			equal defined above the to assign to Fib element*/
			bValuesCanBeAssigned = false;
		}
	}
	//if not a list element -> check if number of subobjects is the same
	if ( bValuesCanBeAssigned && ( cTypeToAssign != 'l' ) ){
		
		if ( pToAssignFibElement->getNumberOfSubobjects() !=
				pToAssignToFibElement->getNumberOfSubobjects() ){
			//can't assign values
			bValuesCanBeAssigned = false;
		}
	}
	if ( bValuesCanBeAssigned ){
		//check if a defined variable should be removed which is needed below
		if ( cTypeToAssignTo != 'o' ){
			//if not an external object element
			const list<cFibVariable*> liDefVarsToAssign =
				pToAssignFibElement->getDefinedVariables( ED_POSITION );
			const list<cFibVariable*> liDefVarsToAssignTo =
				pToAssignToFibElement->getDefinedVariables( ED_POSITION );
			if ( liDefVarsToAssign.size() < liDefVarsToAssignTo.size() ){
				//check if the to much defined variables can be deleted
				//go to first to delete variable
				list<cFibVariable*>::const_iterator
					itrDefVarToAssignTo = liDefVarsToAssignTo.begin();
				for ( list<cFibVariable*>::const_iterator
						itrDefVarToAssign = liDefVarsToAssign.begin();
						itrDefVarToAssign != liDefVarsToAssign.end();
						itrDefVarToAssign++, itrDefVarToAssignTo++ ){
					//nothing to do
				}//itrDefVarToAssignTo is the first defined variable to delete
				for ( ; itrDefVarToAssignTo != liDefVarsToAssignTo.end();
						itrDefVarToAssignTo++ ){
				
					if ( 0 < (*itrDefVarToAssignTo)->getNumberOfUsingElements() ){
						/*defined variable is used below
						-> defined variable can not be deleted
						-> values can't be assigned*/
						bValuesCanBeAssigned = false;
						break;
					}
				}
			}
		}else{//if an external object element
			//for every subobject: check if the to much defined variables can be deleted
			cExtObject * pToAssignExtObject =
				((cExtObject*)pToAssignFibElement);
			cExtObject * pToAssignToExtObject =
				((cExtObject*)pToAssignToFibElement);
			const unsignedIntFib uiNumberOfSubobjects =
				pToAssignToExtObject->getNumberOfSubobjects();
			
			for ( unsignedIntFib uiActualSubobject = 1;
					uiActualSubobject <= uiNumberOfSubobjects; uiActualSubobject++ ){
				
				const vector<cFibVariable*> vecDefVarsToAssign =
					pToAssignExtObject->getOutputVariables( uiActualSubobject );
				const vector<cFibVariable*> vecDefVarsToAssignTo =
					pToAssignToExtObject->getOutputVariables( uiActualSubobject );
				if ( vecDefVarsToAssign.size() < vecDefVarsToAssignTo.size() ){
					//check if the to much defined variables can be deleted
					//go to first to delete variable
					vector<cFibVariable*>::const_iterator
						itrDefVarToAssignTo = vecDefVarsToAssignTo.begin();
					for ( vector<cFibVariable*>::const_iterator
							itrDefVarToAssign = vecDefVarsToAssign.begin();
							itrDefVarToAssign != vecDefVarsToAssign.end();
							itrDefVarToAssign++, itrDefVarToAssignTo++ ){
						//nothing to do
					}//itrDefVarToAssignTo is the first defined variable to delete
					for ( ; itrDefVarToAssignTo != vecDefVarsToAssignTo.end();
							itrDefVarToAssignTo++ ){
					
						if ( 0 < (*itrDefVarToAssignTo)->getNumberOfUsingElements() ){
							/*defined variable is used below
							-> defined variable can not be deleted
							-> values can't be assigned*/
							bValuesCanBeAssigned = false;
							break;
						}
					}
				}
			}//end for all subobjects
		}//end if not external subobject
	}//end check if a variable should be removed which is needed above
	
	//copy original Fib object, so it can be used to check the result
	cFibElement * pFibObjectCopy = pFibObject->clone();
	
	cFibElement * pToAssignToFibElementCopy =
		pFibObjectCopy->getFibElement( uiNumberOfToAssignToElement );
	
	//try to assign the element values
	cout<<"Calling assignValues() from the "<<uiNumberOfToAssignToElement<<
		" Fib element of type "<<cTypeToAssignTo<<" to assign the values of the "<<
			uiNumberOfToAssignToElement<<" Fib element of type "<<cTypeToAssignTo<<
			" (to assign the values should be "<<
			( bValuesCanBeAssigned ? "possible)" : "not possible)" )<<endl;
	
	const bool bAssignResult = pToAssignToFibElement->assignValues( *pToAssignFibElement );
	cout<<"   returned "<<(bAssignResult?"true":"false")<<endl;
	
	if ( bAssignResult != bValuesCanBeAssigned ){
		cerr<<"Error: assignValues() returned "<<( bAssignResult ? "true" : "false")<<
			", but should return "<<( bValuesCanBeAssigned ? "true" : "false")<<" ."<<endl;
	}
	
	
	//check the assigned to Fib element is equal to the assigned from Fib element
	cout<<"Checking assigned Fib element:"<<endl;
	if ( bAssignResult ){
		if( ! pToAssignFibElement->equalElement( *pToAssignToFibElement, false ) ){
			cerr<<"Error: assignValues() returned true, but the assigned to "<<
				"and assigned from Fib element are not equal."<<endl;
			iReturn++;
		}
	}else{//assignValues() returned false
		if( pToAssignFibElement->equalElement( *pToAssignToFibElement, false ) ){
			cerr<<"Error: assignValues() returned false, but the assigned to "<<
				"and assigned from Fib element are equal."<<endl;
			iReturn++;
		}
		if( ! pToAssignToFibElement->equalElement( *pToAssignToFibElementCopy, false ) ){
			cerr<<"Error: assignValues() returned false, but the assigned to "<<
				"Fib element was changed."<<endl;
			iReturn++;
		}
	}
	
	//check if the Fib object hasn't changed except for the assigned to Fib element
	/*adapt above assigned to Fib element, because variables values could be changed
	 -> replace all used variables above assigned Fib element with dummy
	 variable (in both changed and copy, so the values set to it dosn't
	 matter) and check elements with equalElement() */
	cFibVariable varDummy( NULL );
	if ( bAssignResult &&
			( 0 < pToAssignToFibElement->getNumberOfSubobjects() ) ){
		/*if values where assigned, replace all used variables above assigned
		 *Fib element (in both changed and copy) with dummy variable*/
		
		cFibElement * pToAssignToFibElementNext =
			pToAssignToFibElement->getNextFibElement();
		set<cFibVariable*> setUsedVariables =
			pToAssignToFibElementNext->getUsedVariables( ED_BELOW_EQUAL );
		for ( set<cFibVariable*>::iterator
				itrUsedVariable = setUsedVariables.begin();
				itrUsedVariable != setUsedVariables.end(); itrUsedVariable++ ){
			//replace used variable with dummy variable
			pToAssignToFibElementNext->replaceVariable( *itrUsedVariable, &varDummy );
		}
		
		cFibElement * pToAssignToFibElementCopyNext =
			pToAssignToFibElementCopy->getNextFibElement();
		setUsedVariables =
			pToAssignToFibElementCopyNext->getUsedVariables( ED_BELOW_EQUAL );
		for ( set<cFibVariable*>::iterator
				itrUsedVariable = setUsedVariables.begin();
				itrUsedVariable != setUsedVariables.end(); itrUsedVariable++ ){
			//replace used variable with dummy variable
			pToAssignToFibElementCopyNext->replaceVariable( *itrUsedVariable, &varDummy );
		}
	}
	//compare all Fib elements except the Fib element to which the values where assigned
	cFibElement * pActualElement = pFibObject;
	cFibElement * pActualElementCopy = pFibObjectCopy;
	while ( ( pActualElement != NULL ) && ( pActualElementCopy != NULL ) ){
		if ( bAssignResult && ( pActualElement == pToAssignToFibElement ) ){
			if ( cTypeToAssignTo != 'r' ){
				//skip to assign to Fib element
				pActualElement = pActualElement->getNextFibElement();
				pActualElementCopy = pActualElementCopy->getNextFibElement();
			}else{/*to assign to Fib element is root element
				 *-> skip all its subroots (because assignValue()
				 * maybe changed the order of the sub roots)*/
				const unsignedIntFib uiFibElementsToSkip =
					pToAssignToFibElement->getNumberOfElement() + 1;
				pActualElement = pToAssignToFibElement->getFibElement(
					uiFibElementsToSkip );
				pActualElementCopy = pToAssignToFibElementCopy->getFibElement(
					uiFibElementsToSkip );
			}
			continue;
		}
		if ( ! pActualElement->equalElement( *pActualElementCopy, false ) ){
			cerr<<"Error: The "<<pActualElement->getNumberOfElement()<<
				" Fib element (of type "<<pActualElement->getType()<<
				") is not equal to its copy."<<endl;
			iReturn++;
		}
		//check next Fib element
		pActualElement = pActualElement->getNextFibElement();
		pActualElementCopy = pActualElementCopy->getNextFibElement();
	}
	if ( pActualElement != NULL ){
		cerr<<"Error: The "<<pActualElement->getNumberOfElement()<<
			" Fib element (of type "<<pActualElement->getType()<<
			") is not equal to its copy (which is NULL="<<pActualElementCopy<<")."<<endl;
		iReturn++;
	}
	if ( pActualElementCopy != NULL ){
		cerr<<"Error: The "<<pActualElementCopy->getNumberOfElement()<<
			" Fib element (of type "<<pActualElementCopy->getType()<<
			") is not equal to its original (which is NULL="<<pActualElement<<")."<<endl;
		iReturn++;
	}
	
	if ( cTypeToAssignTo == 'r' ){
		/* if to assign to Fib element is root element
		 * -> check if all sub root objects exists (beware assignValue()
		 * maybe changed the order of the sub roots)*/
		list< cFibElement * > liToAssignToSubobjects =
			pToAssignToFibElement->getSubobjects();
		list< cFibElement * > liToAssignToCopySubobjects =
			pToAssignToFibElementCopy->getSubobjects();
		
		//check if main Fib objects are equal (equal element)
		pActualElement = liToAssignToSubobjects.front();
		pActualElementCopy = liToAssignToCopySubobjects.front();
		//remove main Fib object
		liToAssignToSubobjects.pop_front();
		liToAssignToCopySubobjects.pop_front();
		cFibElement * pStopAtElement = liToAssignToCopySubobjects.front();
		cFibElement * pStopAtElementCopy = liToAssignToCopySubobjects.front();
		
		while ( ( pActualElement != NULL ) && ( pActualElementCopy != NULL ) &&
			//stop at the first sub root element
			( pActualElement != pStopAtElement ) &&
			( pActualElementCopy != pStopAtElementCopy ) ){
			
			if ( ! pActualElement->equalElement( *pActualElementCopy, false ) ){
				cerr<<"Error: The "<<pActualElement->getNumberOfElement()<<
					" Fib element (of type "<<pActualElement->getType()<<
					") is not equal to its copy."<<endl;
				iReturn++;
			}
			//check next Fib element
			pActualElement = pActualElement->getNextFibElement();
			pActualElementCopy = pActualElementCopy->getNextFibElement();
		}
		if ( ( pActualElementCopy == NULL ) && ( pActualElement != NULL ) ){
			cerr<<"Error: The "<<pActualElement->getNumberOfElement()<<
				" Fib element (of type "<<pActualElement->getType()<<
				") is not equal to its copy (which is NULL="<<pActualElementCopy<<")."<<endl;
			iReturn++;
		}
		if ( ( pActualElement == NULL ) && ( pActualElementCopy != NULL ) ){
			cerr<<"Error: The "<<pActualElementCopy->getNumberOfElement()<<
				" Fib element (of type "<<pActualElementCopy->getType()<<
				") is not equal to its original (which is NULL="<<pActualElement<<")."<<endl;
			iReturn++;
		}
		
		//check if all subroot objects exists
		list< cFibElement * >::iterator itrActualSubRootCopy;
		list< cFibElement * >::iterator itrNextSubRoot;
		for ( list< cFibElement * >::iterator
				itrActualSubRoot = liToAssignToSubobjects.begin();
				itrActualSubRoot != liToAssignToSubobjects.end(); ){
			//try to find the sub root element in the copy
			for ( itrActualSubRootCopy = liToAssignToCopySubobjects.begin();
					itrActualSubRootCopy != liToAssignToCopySubobjects.end();
					itrActualSubRootCopy++ ){
				if ( (*itrActualSubRoot)->equal( **itrActualSubRootCopy, false ) ){
					//equal sub root elements found -> mark it as found (erase it)
					itrNextSubRoot = itrActualSubRoot;
					itrNextSubRoot++;
					liToAssignToSubobjects.erase( itrActualSubRoot );
					itrActualSubRoot = itrNextSubRoot;
					liToAssignToCopySubobjects.erase( itrActualSubRootCopy );
					break;
				}
			}
			if ( itrActualSubRootCopy == liToAssignToSubobjects.end() ){
				//equal sub root elements not found
				itrActualSubRoot++;
			}
		}
		if ( ! liToAssignToSubobjects.empty() ){
			cerr<<"Error: There where subroot objects missing in the "<<
				"assigned to root element."<<endl;
			iReturn++;
		}
	}//end check if the assigned to Fib element is a root element
	
	//check if the assigned from Fib element hasn't changed
	cFibElement * pToAssignFibElementCopy =
		pFibObjectCopy->getFibElement( uiNumberOfToAssignElement );
	if ( ! pToAssignFibElement->equalElement( *pToAssignFibElementCopy, false ) ){
		cerr<<"Error: The assigned from Fib element has changed."<<endl;
		iReturn++;
	}
	
	//delete Fib object copy
	pFibObjectCopy->deleteObject();
	
	return iReturn;
}







