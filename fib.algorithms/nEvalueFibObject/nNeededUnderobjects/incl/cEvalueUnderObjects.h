/**
 * @class cEvalueUnderObjects
 * file name: cEvalueUnderObjects.h
 * @author Betti Oesterholz
 * @date 08.12.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This is a helpclass to evalue the positions with ther properties and
 * the number of underobjects in which they are contained.
 *
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
 * This is a helpclass to evalue the positions with ther properties and
 * the number of underobjects in which they are contained.
 *
 */
/*
History:
08.12.2010  Oesterholz  created
*/


#ifndef ___N_NEEDED_UNDEROBJECTS_C_EVALUE_UNDER_OBJECTS_H__
#define ___N_NEEDED_UNDEROBJECTS_C_EVALUE_UNDER_OBJECTS_H__


#include "version.h"
#include "fibDatatyps.h"

#include "cPositionData.h"
#include "cPointData.h"
#include "cPropertyData.h"
#include "cUnderobject.h"

#include "cFibElement.h"
#include "cPoint.h"
#include "cProperty.h"
#include "cDomainVectorBasis.h"
#include "cVectorPosition.h"


#include <list>
#include <map>

using namespace std;


namespace fib{
namespace algorithms{
namespace nEvalueFibObject{
namespace nNeededUnderobjects{


class cEvalueUnderObjects: public iEvalueFibElement{
public:
	
	
	/**
	 * The set for the evalued fib -object position data.
	 */
	map< cVectorPosition, cPositionData > mapEvaluedPositionData;
	
	
	/**
	 * The set for the property data.
	 */
	map< cProperty*, cPropertyData > mapPropertyData;
	
	/**
	 * The set for the point data.
	 */
	map< cPoint*, cPointData > mapPointData;
	
	/**
	 * The list with the properties for the next evalued position.
	 */
	list< pair< cProperty *, cVectorProperty > > liActualProperties;
	
	/**
	 * The dimensions in which bounderies the positions should lay.
	 */
	cDomainVectorBasis * pVecDomainDimension;
	
private:
	
	/**
	 * List with the fib-element typs to evalue.
	 * To speed evaluation up.
	 */
	list<char> liCFibElementTyps;
	
public:
	
	/**
	 * standardconstructor
	 *
	 * @param pInVecDomainDimension The dimension domain for the positions.
	 * 	No position outside this domain will be added.
	 * 	If NULL no check will be executed. (@see pVecDomainDimension)
	 */
	cEvalueUnderObjects( const cDomainVectorBasis * pInVecDomainDimension = NULL );
	
	/**
	 * desconstructor
	 */
	~cEvalueUnderObjects();

	/**
	 * The method with wich the evalued fib -elements with ther properties
	 * are inserted /evalued. Everytime a fib -element of the choosen type
	 * (to evalue) is reached in the evaluation, this method is called with
	 * the fib -element and the properties of the fib -element.
	 *
	 * @param pFibElement the fib -element to evalue
	 * @param vProperties a list with the properties of the fib -element
	 */
	bool evalueElement( cFibElement & fibElement,
			const list<cVectorProperty> & vProperties );
	
	/**
	 * This method finds all the property- and pointelements in the given
	 * fib -object and adds them to the datasets.
	 *
	 * @see mapPropertyData
	 * @see mapPointData
	 * @param pFibObject the fib -object, wher to find the fib -element data
	 */
	void findAllFibElementData( cFibElement & pFibObject );
	
	/**
	 * This function creates the underobject tree for the evalued points.
	 * Beware: You have to care that the created underobject tree will
	 * 	be deleted.
	 *
	 * @return a pointer to the created underobject tree
	 */
	cUnderobject<cPointData> * createUnderobjectTree();
	
	/**
	 * This method marks all the property- and pointelements wich aren't
	 * needed.
	 *
	 * This are:
	 * 	- all overwritten properties
	 * 	- all properties, wich overwrites the background, but are also equal to it
	 * 	- all points which have no properties, which are not overwritten
	 *
	 * @see mapPropertyData
	 * @see mapPointData
	 * @see mapEvaluedPositionData
	 * @return true if some fib -elements wher marked, else false
	 */
	bool markOverwrittenFibElements();
	
//TODO
	/**
	 * This method marks all the property- and pointelements wich aren't
	 * needed if the given properties are the background properties.
	 * This are all properties, wich overwrites the given background
	 * 	properties, but are also equal to it.
	 * Beware: Call @see markOverwrittenFibElements() befor calling this method.
	 *
	 * @see mapPropertyData
	 * @see mapPointData
	 * @see mapEvaluedPositionData
	 * @param liBackgroundProperties the background properties
	 * @return true if some fib -elements wher marked, else false
	 */
	bool markOverwrittenByBgFibElements(
		const list<cVectorProperty> &  liBackgroundProperties);

/*TODO bool markOverwrittenByBgFibElements(
		const list<cVectorProperty> &  liBackgroundProperties, doubleFib dDistance );
*/
	
//background methods
	
	/**
	 * This method evalues wich propertys can remove how many
	 * propertyelements(of the evalued data) as a background property.
	 * You should call the @see markOverwrittenFibElements() methods befor
	 * jusing this method.
	 *
	 * @return a list with the pairs:
	 * 	- first: a property vector(without variables)
	 * 	- second: how many fib property elements can be removed, if this
	 * 	property is used as an background property
	 */
	list< pair< cVectorProperty, unsigned long> >
		countPropertyElementsOverwritebelByBg() const;

	
	
#ifdef DEBUG
	/**
	 * Prints the evalued data.
	 *
	 * @param stream the strem wher to print the data to
	 */
	void print( ostream & stream ) const;
#endif //DEBUG

};//class cEvalueUnderObjects



}//end namespace nNeededUnderobjects
}//end namespace nEvalueFibObject
}//end namespace algorithms
}//end namespace fib



#endif //___N_NEEDED_UNDEROBJECTS_C_EVALUE_UNDER_OBJECTS_H__
