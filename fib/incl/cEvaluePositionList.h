/**
 * @class cEvaluePositionList
 * file name: cEvaluePositionList.h
 * @author Betti Oesterholz
 * @date 18.04.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list.
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
 * This file contains the class for evaluing fib -objects and storing
 * the evalued data into a list (@see liEvaluedPositionData).
 * When the fib -object is evalued this method is called every time a
 * pointelement is reached. The parameter for the method are the
 * positionsvector of the point and properties of the point.
 */
/*
History:
18.04.2010  Oesterholz  created
05.07.2010  Oesterholz  distanceOfProperties() moved from
	cFibObjectFitnessBasicAlgorithm to hear
19.10.2010  Oesterholz  toFibObject() added
*/

#ifndef ___C_EVALUE_POSITION_LIST__
#define ___C_EVALUE_POSITION_LIST__

#include "version.h"

#include "iEvaluePosition.h"

#include "cVectorPosition.h"
#include "cVectorProperty.h"


#include <list>


using std::list;

namespace fib{

class cEvaluePositionList: public iEvaluePosition{
public:

	/**
	 * The list for the evalued fib -object data.
	 *
	 * The first pairelement is the position and the second are the
	 * properties for the position.
	 */
	list< pair< cVectorPosition, list< cVectorProperty > > >
		liEvaluedPositionData;

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
	 * standardconstructor
	 */
	cEvaluePositionList();

	/**
	 * The method with wich the evalued points with ther properties are
	 * inserted. Everytime a point (to evalue) is reached in the
	 * evaluation, this method is called with the position and the
	 * properties of the point and stores the copies of this data
	 * to the end of the list @see liEvaluedPositionData .
	 *
	 * @see liEvaluedPositionData
	 * @param vPosition the position of the point, which is evalued
	 * @param vProperties a list of the properties of the point
	 */
	virtual bool evaluePosition( const cVectorPosition & vPosition,
		const list<cVectorProperty> & vProperties );

	/**
	 * This method clears the data from the list with the evalued position data
	 * liEvaluedPositionData. 
	 * After the function call the liEvaluedPositionData list will be empty.
	 *
	 * @see liEvaluedPositionData
	 */
	void clear();

	/**
	 * This function sorts the list liEvaluedPositionData of
	 * positions with ther values.
	 * It also sorts the property sublists.
	 * A vector is lower if it has less elements than the other vector or
	 * it's i'th element is lower und all j'th elements with i > j are
	 * equal.
	 * The positions with ther properties are sorted in the order as the
	 * positionsvectors.
	 * Propertyvectors with lower propertypvalues are sorted befor
	 * propertyvectors with higer propertypvalues, independent of ther
	 * elements.
	 * Also equal/duplicate positions will be removed, ther properties will be
	 * merged. Properties of a later positions in the given list will
	 * overwrite properties earlier in the list, if neccessary.
	 * Positions without porperties will be removed.
	 *
	 * @see liEvaluedPositionData
	 * @param bDeleteEmptyPoints if true points without properties will be
	 * 	deleted, else (if false) points without properties won't be deleted
	 */
	void sortPositionsData( bool bDeleteEmptyPoints=true );
	
	/**
	 * This function sorts the given list of positions with ther values.
	 * It also sorts the property sublists.
	 * A vector is lower if it has less elements than the other vector or
	 * it's i'th element is lower und all j'th elements with i > j are
	 * equal.
	 * The positions with ther properties are sorted in the order as the
	 * positionsvectors.
	 * Propertyvectors with lower propertypvalues are sorted befor
	 * propertyvectors with higer propertypvalues, independent of ther
	 * elements.
	 * Also equal/duplicate positions will be removed, ther properties will be
	 * merged. Properties of a later positions in the given list will
	 * overwrite properties earlier in the list, if neccessary.
	 * Positions without porperties will be removed.
	 *
	 * @param liEvaluedPositionData a pointer to the positionsdata to sort
	 * @param bDeleteEmptyPoints if true points without properties will be
	 * 	deleted, else (if false) points without properties won't be deleted
	 */
	static void sortPositionsData( list< pair< cVectorPosition,
		list< cVectorProperty > > > * liEvaluedPositionData,
		bool bDeleteEmptyPoints=true );

	/**
	 * This function compares two positions with ther properties.
	 * For that just the positionsvectors are compared.
	 * A (position)vector is lower if it has less elements than the other
	 * vector or it's i'th element is lower and all j'th elements with i > j
	 * are equal.
	 *
	 * @param paPosition1 the first pair of position with it's properties to compare
	 * @param paPosition2 the second pair of position with it's properties to compare
	 * @return true if the positionsvector of paPosition1 is lower than that
	 * 	of paPosition2, else false
	 */
	static bool lowerPositionPair(
		const pair< cVectorPosition, list< cVectorProperty > > & paPosition1,
		const pair< cVectorPosition, list< cVectorProperty > > & paPosition2 );
	
	/**
	 * This function mergs the two given propertylists.
	 * All Properties of the second list liProperties2 that,
	 * aren't overwritten by properties in the first propertylist,
	 * liProperties1 are added to it.
	 *
	 * @param liProperties1 the propertielist to add to
	 * @param liProperties2 the list with the properties to be added
	 * @return a lis with the properties from the list liProperties1 and
	 * 	the properties from the list liProperties2 which arn't overwirtten
	 * 	by properties from list liProperties1
	 */
	static list< cVectorProperty > mergeProperties(
		const list< cVectorProperty > & liProperties1,
		const list< cVectorProperty > & liProperties2 );
	
	/**
	 * This function evalues the difference betwean the two propertielists.
	 * Both propertylist have to be sorted in the order of lowerPropertyVector().
	 *
	 * @see cVectorProperty::lowerPropertyVector()
	 * @see cVectorProperty::distanceOfProperty()
	 * @see cVectorProperty::distanceOfPropertyToNull()
	 * @param liPropertiesOriginal the positions with ther properties of the
	 * 	original fib -object
	 * @param liPropertiesGiven the positions with ther properties of the
	 * 	given fib -object, for which the distance to the original fib -object
	 * 	(liPropertiesOriginal) should be evalued
	 * @return the sum of the distance of the properties of the points
	 * 	(for missing properties, ther value to the nullvector will be added)
	 */
	static doubleFib distanceOfProperties( const list< cVectorProperty > & liPropertiesOriginal,
		const list< cVectorProperty > & liPropertiesGiven );

	/**
	 * This function creats a fib -object, which represents the given data.
	 * Beware: You have to care, that the created fib -object is deleted.
	 *
	 * @param vecPosition the position for the to create point
	 * @param liProperties the properties of the create point
	 * @return a fib -object with a point on the given position, wich is
	 * 	an underobject of propertyelements, with the given properties
	 */
	static cFibElement * toFibObject( const cVectorPosition & vecPosition,
		const list< cVectorProperty > & liProperties );


	/**
	 * This function prints the given list of positions with ther values.
	 * It also prints the property sublists.
	 *
	 * @param liEvaluedPositionData a reference to the positionsdata to print
	 * @param strOutput the stream wher to print the data to
	 */
	static void printPositionsData( const list< pair< cVectorPosition,
		list< cVectorProperty > > > & liEvaluedPositionData,
		ostream & strOutput );
	
};//class cEvaluePositionList

};

#endif


