/**
 * @file nConvertToFib
 * file name: nConvertToFib.cpp
 * @author Betti Oesterholz
 * @date 23.02.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This header specifies functions with which multimediaobjects in non fib
 * multimediaformats can be converted into fib -objects.
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
 * This header specifies functions with which multimediaobjects in non fib
 * multimediaformats can be converted into fib -objects.
 *
 */
/*
History:
23.02.2010  Oesterholz  created
07.03.2011  Oesterholz  function convertOptimized() added
11.03.2011  Oesterholz  function convertReduced() added
16.08.2011  Oesterholz  Bugfix (Speicherzugriffsfehler): in choos a
	property which is often used by all points;
	if mapWigthedCountsForProperty are all 0 no property was choosen
28.01.2013  Oesterholz  COLOR_SW changed to COLOR_GRAYSCALE
*/


#include "cRoot.h"
#include "cPoint.h"
#include "cList.h"
#include "cProperty.h"
#include "cTypeProperty.h"
#include "cTypeDimension.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"

#include "nReduceFibObject.h"
#include "../nD1/incl/cDataPoint.h"
#include "nD2.h"
#include "nBits.h"

#include "nConvertToFib.h"

#include <cmath>


#ifdef FEATURE_BALANCED_LOAD

	#include "nBalanceLists.h"

	using namespace fib::algorithms::nTidyFibObjects::nBalanceLists;

#endif //FEATURE_ALGORITHM_WITH_BALANCED_FIB_OBJECT


using namespace nConvertToFib;

using namespace fib::algorithms;
using namespace fib::algorithms::nAnalyse::nFibObject::nBits;


/*TODO debugging:
#define DEBUG
#undef ___DEBUG_OUT_H__
#include "debugOut.inc"
*/

//minimal point for creating an area
#define MIN_POINTS_FOR_AREA 14

//when converting don't create single points
//#define N_CONVERT_TO_FIB_NO_POINTS

//when converting don't create areas
//#define N_CONVERT_TO_FIB_NO_AREAS

//when correcting wrong points (bCorrectPoints=true) just output the corrected points
//#define DEBUG_N_CONVERT_TO_FIB__JUST_CORRECTED_WRONG_POINTS



//combines just two combinebel neighbours at a time
#define FEATURE_N_CONVERT__SAVE_COMBINING_AREAS

namespace fib{

namespace nConvertToFib{

namespace nConvertReduced{


/**
 * @class cAreaNeighbourNode
 * Helperclass for the @see convertReduced() function.
 * It stores the information for the graph of areas, which can be combined.
 */
template< class tValue >
class cAreaNeighbourNode{
protected:
	/**
	 * The points of the area.
	 */
	set< nD1::cDataPoint< tValue, tValue > > setPointsOfArea;
	
	
	/**
	 * The counts of the points with the different properties.
	 * key: The property for which the points are counted.
	 * value:
	 * 	first: the number of points with the property
	 * 	second: if true all point with this property are not areas
	 * 	(@see reduceNeighbours ulMaxDiff)
	 */
	map< cVectorProperty, pair< unsigned long, bool > > mapCountsForProperties;
	
	/**
	 * The number of points of the area.
	 * @see setPointsOfArea
	 * @see mapCountsForProperties
	 */
	unsigned long ulNumberOfPointsNeighbourhood;
	
	/**
	 * The list of the neighbour areas, which can be combined with the area.
	 */
	set< cAreaNeighbourNode< tValue > * > setNeighbourNodes;
	
public:
	
	/**
	 * parameterconstructor
	 *
	 * @param setInPointsOfArea the points for the area
	 * @param vecPropertyOfPoints the vector of the property of all points
	 * 	in setInPointsOfArea
	 * @param bJustSinglePoints if true all point with this property are not areas
	 * 	(@see reduceNeighbours ulMaxDiff)
	 */
	cAreaNeighbourNode( const set< nD1::cDataPoint< tValue,
			tValue > > & setInPointsOfArea,
			const cVectorProperty & vecPropertyOfPoints,
			const bool bJustSinglePoints=false ):
			setPointsOfArea( setInPointsOfArea ),
			ulNumberOfPointsNeighbourhood( 0 ){
		
		mapCountsForProperties[ vecPropertyOfPoints ] = pair< unsigned long, bool >(
			setInPointsOfArea.size(), bJustSinglePoints );
	}
	
	
	/**
	 * @returns the number of points of the area (@see setPointsOfArea)
	 */
	const unsigned long getNumberOfAreaPoints() const{
		
		return setPointsOfArea.size();
	}
	
	
	/**
	 * @returns the set of the points of the area (@see setPointsOfArea)
	 */
	const set< nD1::cDataPoint< tValue, tValue > > & getPointsOfArea() const{
		
		return setPointsOfArea;
	}
	
	
	/**
	 * This method removes the given data point.
	 * Attention: The area should be just for one property type.
	 * 	The romoving of the data point will not change this area
	 * 	connections to its neighbours.
	 *
	 * @see setPointsOfArea
	 * @param dataPoint the data point to remove
	 * @param ulMinPoints if the area count has less or equal points than
	 * 		this number, the points are not counted as an area
	 * 		(@see mapCountsForProperties value.second)
	 * @returns true if the data point was removed, else false
	 */
	const bool removePoint( const nD1::cDataPoint< tValue, tValue > &
			dataPoint, const unsigned long ulMinPoints=0 ){
		
		typename set< nD1::cDataPoint< tValue, tValue > >::iterator
			itrDataPoint = setPointsOfArea.find( dataPoint );
		
		if ( itrDataPoint == setPointsOfArea.end() ){
			//no such point in this area
			return false;
		}
		setPointsOfArea.erase( itrDataPoint );
		//update property counters (the area should be just for one property type)
		if ( ! mapCountsForProperties.empty() ){
			
			mapCountsForProperties.begin()->second.first--;
			if ( mapCountsForProperties.begin()->second.first == 0 ){
				mapCountsForProperties.erase(
					mapCountsForProperties.begin() );
				
			}else if ( ( ! mapCountsForProperties.begin()->second.second ) &&
					( mapCountsForProperties.begin()->second.first <= ulMinPoints ) ){
				//points are not counted as an area
				mapCountsForProperties.begin()->second.second = true;
			}
		}
		
		for ( typename set< cAreaNeighbourNode< tValue > * >::const_iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end(); itrNeighbour++ ){
		
			(*itrNeighbour)->ulNumberOfPointsNeighbourhood--;
		}//else no neighbour area, of wich this point is part found
		return true;
	}
	
	
	/**
	 * @see setPointsOfArea
	 * @param dataPoint the data point wich should be part of the area
	 * @returns true if the given data point is in the set of the points of
	 * 	the area, else false
	 */
	bool isPointOfArea( const nD1::cDataPoint< tValue, tValue > &
			dataPoint ) const{
		
		return ( setPointsOfArea.find( dataPoint ) != setPointsOfArea.end() );
	}
	
	
	/**
	 * @see setNeighbourNodes
	 * @see setPointsOfArea
	 * @param dataPoint the data point, wich should be part of a neighbour area
	 * @returns true if the given data point is in a neighbour area, else false
	 */
	bool isPointOfNeighbourArea( const nD1::cDataPoint< tValue, tValue > &
			dataPoint ) const{
		
		for ( typename set< cAreaNeighbourNode< tValue > * >::const_iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end(); itrNeighbour++ ){
		
			if  ( (*itrNeighbour)->setPointsOfArea.find( dataPoint ) !=
					(*itrNeighbour)->setPointsOfArea.end() ){
				//neighbour area, of wich this point is part found
				return true;
			}
		}//else no neighbour area, of wich this point is part found
		return false;
	}

	
	/**
	 * @return the number of points in neighbour areas, which can be combined,
	 * 	with this area (@see ulNumberOfPointsNeighbourhood)
	 */
	unsigned long getNumberOfPointsInNeighbourhood() const{
		
		return ulNumberOfPointsNeighbourhood;
	}
	
	/**
	 * @see mapCountsForProperties
	 * @return the a map with the number of points for the different
	 * 	properties in the area;
	 * 	key: The property for which the points are counted.
	 * 	value:
	 * 		first: the number of points with the property
	 * 		second: if true all point with this property are not areas
	 * 		(@see reduceNeighbours ulMaxDiff)
	 */
	map< cVectorProperty, pair< unsigned long, bool> > getCountsForProperties() const{
		
		return mapCountsForProperties;
	}

	
	/**
	 * @returns the set of the neighbour nodes of this area (@see setNeighbourNodes)
	 */
	set< cAreaNeighbourNode< tValue > * > & getNeighbourNodes(){
		
		return setNeighbourNodes;
	}

	
	/**
	 * This method adds the given neighbour area to the neighbourhood of this
	 * area.
	 *
	 * @see setNeighbourNodes
	 * @see ulNumberOfPointsNeighbourhood
	 * @param pNeighbourNode the pointer to the neighbour area to add
	 */
	void addNeighbour( cAreaNeighbourNode< tValue > * pNeighbourNode ){
		
		if ( pNeighbourNode == this ){
			//can'T be neighbour to itself
			return;
		}
		if ( setNeighbourNodes.find( pNeighbourNode ) != setNeighbourNodes.end() ){
			//already existing neighbour area of this area
			return;
		}
		ulNumberOfPointsNeighbourhood +=
			pNeighbourNode->setPointsOfArea.size();
		setNeighbourNodes.insert( pNeighbourNode );
		
		pNeighbourNode->ulNumberOfPointsNeighbourhood +=
			setPointsOfArea.size();
		pNeighbourNode->setNeighbourNodes.insert( this );
	}
	
	
	/**
	 * This method remove the given neighbour area from the neighbourhood of this
	 * area.
	 *
	 * @see setNeighbourNodes
	 * @see ulNumberOfPointsNeighbourhood
	 * @param pNeighbourNode the pointer to area to remove
	 * @return true if the neighbourNode area was removed, else false
	 */
	bool removeNeighbour( cAreaNeighbourNode< tValue > * pNeighbourNode ){
		
		if ( setNeighbourNodes.find( pNeighbourNode ) == setNeighbourNodes.end() ){
			//already not neighbour area of this area
			return false;
		}
		ulNumberOfPointsNeighbourhood -=
			pNeighbourNode->setPointsOfArea.size();
		setNeighbourNodes.erase( pNeighbourNode );
		
		pNeighbourNode->ulNumberOfPointsNeighbourhood -=
			setPointsOfArea.size();
		pNeighbourNode->setNeighbourNodes.erase( this );
		
		return true;
	}
	
	
	/**
	 * This method reduce the the neighbour areas of this area, to the
	 * neighbour areas, which fulfill the conditions.
	 *
	 * @see setNeighbourNodes
	 * @see ulNumberOfPointsNeighbourhood
	 * @see mapCountsForProperties
	 * @param ulMaxAreaDiff the maximal difference of color values in an area
	 * 	(as the sum of the color vector element distances)
	 * @param ulMaxDiff all points which are not point of a property area
	 * 	(mapCountsForProperties[i].second == true) will be combined with
	 * 	this area, if ther property difference is equal or less than ulMaxDiff
	 */
	void reduceNeighbours( const unsigned long ulMaxAreaDiff, const unsigned long ulMaxDiff ){
		
		 set< cAreaNeighbourNode< tValue > * > setNeighboursToRemove;
		 
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrNeighbourArea = setNeighbourNodes.begin();
				itrNeighbourArea != setNeighbourNodes.end(); itrNeighbourArea++ ){
			//check no two point properties have a to big distance
			bool bRemoveNeighbour = false;
			cAreaNeighbourNode< tValue > & neighbourNode = **itrNeighbourArea;
			
			//check all propertie combinations of this and the neighbour area
			for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
					itrPropertyCounts1 = mapCountsForProperties.begin();
					itrPropertyCounts1 != mapCountsForProperties.end();
					itrPropertyCounts1++ ){
				
				for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
						itrPropertyCounts2 = neighbourNode.mapCountsForProperties.begin();
						itrPropertyCounts2 != neighbourNode.mapCountsForProperties.end();
						itrPropertyCounts2++ ){
					
					if ( itrPropertyCounts1->first != itrPropertyCounts2->first ){
						
						const unsignedLongFib ulDistance = roundToLongFib( cVectorProperty::
							distanceOfProperty( itrPropertyCounts1->first,
								itrPropertyCounts2->first ) );
						
						if ( itrPropertyCounts1->second.second ||
								itrPropertyCounts2->second.second ){
							/*one point count, is a count for points, which are not point of a property area
							-> compare as non areas*/
							if ( ulMaxDiff < ulDistance ){
								//areas can't be combined
								bRemoveNeighbour = true;
								break;
							}
						}else{
							/*ther are more than ulMinPoints points of the type in one neighbour area
							-> compare as areas to combine*/
							if ( ulMaxAreaDiff < ulDistance ){
								//areas can't be combined
								bRemoveNeighbour = true;
								break;
							}
						}
					}
				}//for properties of neighbour area properties
				if ( bRemoveNeighbour ){
					/*remove actual neighbour*/
					setNeighboursToRemove.insert( &neighbourNode );
					//no more properties to check -> check next neighbour node
					break;
				}
			}//for properties of this area properties
		}//for all neighbour nodes
		//remove to remove neighbour nodes
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrNeighbourAreaToRemove = setNeighboursToRemove.begin();
				itrNeighbourAreaToRemove != setNeighboursToRemove.end();
				itrNeighbourAreaToRemove++ ){
			/*remove actual neighbour*/
			cAreaNeighbourNode< tValue > & actualNeighbourNode =
				(**itrNeighbourAreaToRemove);
			ulNumberOfPointsNeighbourhood -=
				actualNeighbourNode.setPointsOfArea.size();
			setNeighbourNodes.erase( &actualNeighbourNode );
			
			actualNeighbourNode.ulNumberOfPointsNeighbourhood -=
				setPointsOfArea.size();
			actualNeighbourNode.setNeighbourNodes.erase( this );
		}
	}
	
	
	/**
	 * This method combines this area with all its neighbour areas.
	 * Beware: Don't forget to @see reduceNeighbours(), if needed.
	 *
	 * @return a set of with pointers to neighbour areas, with wich this
	 * 	area was combined
	 */
	set< cAreaNeighbourNode< tValue > * > combineWithNeighbourNodes(){
		
		const set< cAreaNeighbourNode< tValue > * > setOldNeighbours =
			setNeighbourNodes;
		
		//add points of neighbours to this and update counters of this
		for ( typename set< cAreaNeighbourNode< tValue > * >::const_iterator
				itrOldNeighbour = setOldNeighbours.begin();
				itrOldNeighbour != setOldNeighbours.end();
				itrOldNeighbour++ ){
			
			cAreaNeighbourNode< tValue > * pOldNeighbourNode = (*itrOldNeighbour);
			
			setPointsOfArea.insert( pOldNeighbourNode->setPointsOfArea.begin(),
				pOldNeighbourNode->setPointsOfArea.end() );
			
			//add counts of old neighbour node to this
			for ( map< cVectorProperty, pair< unsigned long, bool> >::const_iterator
					itrNeighbourCount = pOldNeighbourNode->mapCountsForProperties.begin();
					itrNeighbourCount != pOldNeighbourNode->mapCountsForProperties.end();
					itrNeighbourCount++ ){
				
				map< cVectorProperty, pair< unsigned long, bool> >::iterator
					itrThisCount = mapCountsForProperties.find( itrNeighbourCount->first );
				
				if ( itrThisCount != mapCountsForProperties.end() ){
					//add values to existing entry
					pair< unsigned long, bool > & paActualCount =
						itrThisCount->second;
					paActualCount.first += itrNeighbourCount->second.first;
					paActualCount.second &= itrNeighbourCount->second.second;
				}else{//new count entry ->add neighbour entry
					mapCountsForProperties.insert( *itrNeighbourCount );
				}
			}
		}
		//update neighbours
		set< cAreaNeighbourNode< tValue > * > setOldNeighbourNeighbours;
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrOldNeighbour = setOldNeighbours.begin();
				itrOldNeighbour != setOldNeighbours.end();
				itrOldNeighbour++ ){
			
			const set< cAreaNeighbourNode< tValue > * > setOldActualNeighbourNeighbours =
				(*itrOldNeighbour)->setNeighbourNodes;
			
			setOldNeighbourNeighbours.insert(
				setOldActualNeighbourNeighbours.begin(),
				setOldActualNeighbourNeighbours.end() );
			
			//remove all neighbours from old neighbour
			for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
					itrOldNeighbourNeighbour = setOldActualNeighbourNeighbours.begin();
					itrOldNeighbourNeighbour != setOldActualNeighbourNeighbours.end();
					itrOldNeighbourNeighbour++ ){
				
				(*itrOldNeighbour)->removeNeighbour( *itrOldNeighbourNeighbour );
			}
		}
		//don't add this or one of the removed neighbours
		setOldNeighbourNeighbours.erase( this );
		
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrOldNeighbour = setOldNeighbours.begin();
				itrOldNeighbour != setOldNeighbours.end();
				itrOldNeighbour++ ){
			
			setOldNeighbourNeighbours.erase( *itrOldNeighbour );
		}
		//add remaining (not this or old neighbour) old neighbours neighbours
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrOldNeighbourNeighbour = setOldNeighbourNeighbours.begin();
				itrOldNeighbourNeighbour != setOldNeighbourNeighbours.end();
				itrOldNeighbourNeighbour++ ){
			
			addNeighbour( *itrOldNeighbourNeighbour );
		}
		return setOldNeighbours;
	}
	
	
	/**
	 * This method combines this area with its biggest neighbour areas.
	 * Beware: Don't forget to @see reduceNeighbours(), if needed.
	 *
	 * @return the pointers to the neighbour area, with wich this area was
	 * 	combined or NULL if it wasn't combined
	 */
	cAreaNeighbourNode< tValue > * combineWithBiggestNeighbourNode(){
		
		if ( setNeighbourNodes.empty() ){
			//no neighbour area to combine with
			return NULL;
		}
		//find the biggest neighbour area node
		cAreaNeighbourNode< tValue > * pBiggestNeighbourNode = NULL;
		unsigned long ulMaxPointsInNeighbourNode = 0;
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end();
				itrNeighbour++ ){
			
			if ( ulMaxPointsInNeighbourNode <
					(*itrNeighbour)->getNumberOfAreaPoints() ){
					
				pBiggestNeighbourNode = (*itrNeighbour);
				ulMaxPointsInNeighbourNode =
					(*itrNeighbour)->getNumberOfAreaPoints();
			}
		}
		if ( pBiggestNeighbourNode == NULL ){
			//no biggest neighbour area to combine with
			return NULL;
		}
		const unsigned long ulOldNumberOfPoints = setPointsOfArea.size();
		//add points of neighbours to this and update counters of this
		setPointsOfArea.insert( pBiggestNeighbourNode->setPointsOfArea.begin(),
			pBiggestNeighbourNode->setPointsOfArea.end() );
		//correct number of neighbours of remaining neighbour nodes
		const unsigned long ulDeltaNumberOfPoints = setPointsOfArea.size() - ulOldNumberOfPoints;
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end();
				itrNeighbour++ ){
			
			if ( *itrNeighbour != pBiggestNeighbourNode ){
				//an not to subsume neighbour node -> add number of new points in neighbourhood
				(*itrNeighbour)->ulNumberOfPointsNeighbourhood +=
					ulDeltaNumberOfPoints;
			}//else neighbour node to subsume
		}
		
		//add counts of old neighbour node to this
		for ( map< cVectorProperty, pair< unsigned long, bool> >::const_iterator
				itrNeighbourCount = pBiggestNeighbourNode->mapCountsForProperties.begin();
				itrNeighbourCount != pBiggestNeighbourNode->mapCountsForProperties.end();
				itrNeighbourCount++ ){
			
			map< cVectorProperty, pair< unsigned long, bool> >::iterator
				itrThisCount = mapCountsForProperties.find( itrNeighbourCount->first );
			
			if ( itrThisCount != mapCountsForProperties.end() ){
				//add values to existing entry
				pair< unsigned long, bool > & paActualCount =
					itrThisCount->second;
				paActualCount.first += itrNeighbourCount->second.first;
				paActualCount.second &= itrNeighbourCount->second.second;
			}else{//new count entry ->add neighbour entry
				mapCountsForProperties.insert( *itrNeighbourCount );
			}
		}
		//update neighbours
		set< cAreaNeighbourNode< tValue > * > setOldNeighbourNeighbours =
			pBiggestNeighbourNode->setNeighbourNodes;
			
		setOldNeighbourNeighbours.insert( setOldNeighbourNeighbours.begin(),
			setOldNeighbourNeighbours.end() );
		
		//remove all neighbours from old neighbour
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrOldNeighbourNeighbour = setOldNeighbourNeighbours.begin();
				itrOldNeighbourNeighbour != setOldNeighbourNeighbours.end();
				itrOldNeighbourNeighbour++ ){
			
			pBiggestNeighbourNode->removeNeighbour( *itrOldNeighbourNeighbour );
		}
		//don't add this or one of the removed neighbours
		setOldNeighbourNeighbours.erase( this );
		
		//add remaining (not this or old neighbour) old neighbours neighbours
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrOldNeighbourNeighbour = setOldNeighbourNeighbours.begin();
				itrOldNeighbourNeighbour != setOldNeighbourNeighbours.end();
				itrOldNeighbourNeighbour++ ){
			
			addNeighbour( *itrOldNeighbourNeighbour );
		}
		return pBiggestNeighbourNode;
	}
	
	
	/**
	 * This method subsumes all/combines with all neibour node areas, with
	 * less than the given number of points.
	 * The count for the points of the subsumed areas will be added to the
	 * property point count with the most points.
	 *
	 * @param uiNumberOfPoints maximal the number of points of the areas to
	 * 	subsume
	 * @return a set of with pointers to neighbour areas, with wich this
	 * 	area was combined
	 */
	set< cAreaNeighbourNode< tValue > * > combineWithSmallNeighbours(
			unsigned int uiNumberOfPoints=1 ){
		
		set< cAreaNeighbourNode< tValue > * > setToSubsumeNeighbours;
		//find the to subsume neighbours
		for ( typename set< cAreaNeighbourNode< tValue > * >::const_iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end();
				itrNeighbour++ ){
			
			if ( (*itrNeighbour)->getNumberOfAreaPoints() <= uiNumberOfPoints ){
				setToSubsumeNeighbours.insert( * itrNeighbour );
			}
		}
		//update counters
		//find most property with the most points for it
		map< cVectorProperty, pair< unsigned long, bool> >::iterator
			itrMostCommenProperty = mapCountsForProperties.begin();
		unsigned long ulMaxPointsForProperty = itrMostCommenProperty->second.first;
		for ( map< cVectorProperty, pair< unsigned long, bool> >::iterator
				itrPropertyCount = mapCountsForProperties.begin();
				itrPropertyCount != mapCountsForProperties.end();
				itrPropertyCount++ ){
			
			if ( ulMaxPointsForProperty < itrPropertyCount->second.first ){
				ulMaxPointsForProperty = itrPropertyCount->second.first;
				itrMostCommenProperty = itrPropertyCount;
			}
		}
		//add counts of to subsume neighbours
		const unsigned long ulOldNumberOfPoints = setPointsOfArea.size();
		for ( typename set< cAreaNeighbourNode< tValue > * >::const_iterator
				itrToSubsumeNeighbour = setToSubsumeNeighbours.begin();
				itrToSubsumeNeighbour != setToSubsumeNeighbours.end();
				itrToSubsumeNeighbour++ ){
			
			setPointsOfArea.insert( (*itrToSubsumeNeighbour)->setPointsOfArea.begin(),
				(*itrToSubsumeNeighbour)->setPointsOfArea.end() );
			
			for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
					itrNeighbourCount = (*itrToSubsumeNeighbour)->mapCountsForProperties.begin();
					itrNeighbourCount != (*itrToSubsumeNeighbour)->mapCountsForProperties.end();
					itrNeighbourCount++ ){
				
				itrMostCommenProperty->second.first += itrNeighbourCount->second.first;
			}
		}
		//correct number of neighbours of remaining neighbour nodes
		const unsigned long ulDeltaNumberOfPoints = setPointsOfArea.size() - ulOldNumberOfPoints;
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end();
				itrNeighbour++ ){
			
			if ( setToSubsumeNeighbours.find( *itrNeighbour ) ==
					setToSubsumeNeighbours.end() ){
				//an not to subsume neighbour node -> add number of new points in neighbourhood
				(*itrNeighbour)->ulNumberOfPointsNeighbourhood +=
					ulDeltaNumberOfPoints;
			}//else neighbour node to subsume
		}
		//update neighbours
		set< cAreaNeighbourNode< tValue > * > setOldNeighbourNeighbours;
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrToSubsumeNeighbour = setToSubsumeNeighbours.begin();
				itrToSubsumeNeighbour != setToSubsumeNeighbours.end();
				itrToSubsumeNeighbour++ ){
			
			const set< cAreaNeighbourNode< tValue > * > setOldActualNeighbourNeighbours =
				(*itrToSubsumeNeighbour)->setNeighbourNodes;
			
			setOldNeighbourNeighbours.insert(
				setOldActualNeighbourNeighbours.begin(),
				setOldActualNeighbourNeighbours.end() );
			
			//remove all neighbours from old neighbour
			for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
					itrToSubsumeNeighbourNeighbour = setOldActualNeighbourNeighbours.begin();
					itrToSubsumeNeighbourNeighbour != setOldActualNeighbourNeighbours.end();
					itrToSubsumeNeighbourNeighbour++ ){
				
				(*itrToSubsumeNeighbour)->removeNeighbour( *itrToSubsumeNeighbourNeighbour );
			}
		}
		//don't add this or one of the removed neighbours
		setOldNeighbourNeighbours.erase( this );
		
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrToSubsumeNeighbour = setToSubsumeNeighbours.begin();
				itrToSubsumeNeighbour != setToSubsumeNeighbours.end();
				itrToSubsumeNeighbour++ ){
			
			setOldNeighbourNeighbours.erase( *itrToSubsumeNeighbour );
		}
		//add remaining (not this or old neighbour) old neighbours neighbours
		for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
				itrToSubsumeNeighbourNeighbour = setOldNeighbourNeighbours.begin();
				itrToSubsumeNeighbourNeighbour != setOldNeighbourNeighbours.end();
				itrToSubsumeNeighbourNeighbour++ ){
			
			addNeighbour( *itrToSubsumeNeighbourNeighbour );
		}
		return setToSubsumeNeighbours;
	}
	
	
	/**
	 * This method removes the area if it isn't needed.
	 * An area is not needed, if all its points are in neighbour areas.
	 *
	 * @return true if this area node was not needed
	 */
	bool removeIfNotNeeded(){
		
		bool bNotNeeded = setPointsOfArea.empty();
		if ( ! bNotNeeded ){
			//check if points are in neighbour areas
			set< nD1::cDataPoint< tValue, tValue > >
				setPointsNotInNeibourArea = setPointsOfArea;
			//remove all points wich are in the neighbour areas from setPointsNotInNeibourArea
			for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
					itrOldNeighbour = setNeighbourNodes.begin();
					itrOldNeighbour != setNeighbourNodes.end();
					itrOldNeighbour++ ){
				
				const set< nD1::cDataPoint< tValue, tValue > > &
					setActualNeibourNodes = (*itrOldNeighbour)->setPointsOfArea;
				
				for ( typename set< nD1::cDataPoint< tValue, tValue > >::const_iterator
						itrPoint = setActualNeibourNodes.begin();
						itrPoint != setActualNeibourNodes.end(); itrPoint++ ){
					
					setPointsNotInNeibourArea.erase( *itrPoint );
				}
				if ( setPointsNotInNeibourArea.empty() ){
					//no more to remove
					break;
				}
			}
			bNotNeeded = setPointsNotInNeibourArea.empty();
		}
		if ( bNotNeeded ){
			//area not needed -> clear data of this node
	
			for ( typename set< cAreaNeighbourNode< tValue > * >::iterator
					itrOldNeighbour = setNeighbourNodes.begin();
					itrOldNeighbour != setNeighbourNodes.end();
					itrOldNeighbour++ ){
				
				removeNeighbour( *itrOldNeighbour );
			}
			setNeighbourNodes.clear();
			ulNumberOfPointsNeighbourhood = 0;
			mapCountsForProperties.clear();
			return true;//=bNotNeeded
		}//else area needed
		return false;//=bNotNeeded
	}
	
	
	/**
	 * @param node the cAreaNeighbourNode node to compare with
	 * @return true if the this node has more points ( @see ulNumberOfPointsNeighbourhood)
	 * 	in the neighbourhood as the given node, else false
	 */
	bool operator<( const cAreaNeighbourNode< tValue > & node ) const{
		
		if ( node.ulNumberOfPointsNeighbourhood != ulNumberOfPointsNeighbourhood ){
			return ( node.ulNumberOfPointsNeighbourhood < ulNumberOfPointsNeighbourhood );
		}//else compare pointers, so every object is unique
		return ( this < (&node) );
	}
	
	
	/**
	 * This method print the cAreaNeighbourNode object in a readebel form
	 * to the given output stream outputSream.
	 *
	 * @param outputSream the stream wher to print this inequation to
	 */
	void print( ostream & outputStream ) const{
		
		outputStream<<"area node "<<this<<" :"<<endl;
		//prints point in area
		outputStream<<setPointsOfArea.size()<<" points in area :";
		for ( typename set< nD1::cDataPoint< tValue, tValue > >::const_iterator
				itrPoint = setPointsOfArea.begin();
				itrPoint != setPointsOfArea.end(); itrPoint++ ){
			
			outputStream<<" ( "<<itrPoint->x<<" ,"<<itrPoint->y<<" );";
		}
		outputStream<<endl;
		//print count of properties;
		for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
				itrPointCount = mapCountsForProperties.begin();
				itrPointCount != mapCountsForProperties.end(); itrPointCount++ ){
			
			outputStream<<itrPointCount->second.first<<" points in area which have the property (and are "<<((itrPointCount->second.second)?"":"not ")<<
				"counted as an property area) :"<<endl;
			itrPointCount->first.storeXml( outputStream );
		}
		outputStream<<endl<<"number of neighbour points:"<<ulNumberOfPointsNeighbourhood<<endl;
		outputStream<<"neighbour areas: ";
		for ( typename set< cAreaNeighbourNode< tValue > * >::const_iterator
				itrNeighbour = setNeighbourNodes.begin();
				itrNeighbour != setNeighbourNodes.end(); itrNeighbour++ ){
			
			outputStream<<(*itrNeighbour)<<" ;";
		}
		outputStream<<endl<<endl;
	}

	
};//end class cAreaNeighbourNode

	/**
	 * Class to store the information for areas to reduce the number of bits.
	 */
	class cAreasBitInfo{
	public:
		
		/**
		 * The sum of the number of values (value underfunctions) in all
		 * area objects for the bit number.
		 * @see liAreas
		 */
		unsigned long ulNumberOfValues;
		
		/**
		 * The sum of the number of points in all areas for the bit number.
		 */
		unsigned long ulNumberOfPoints;
		
		/**
		 * The list with the given fib-objects, wich need as minimum the
		 * correspondending number of bits.
		 */
		list< cFibElement * > liAreas;
		
		/**
		 * parameterconstructor
		 *
		 * @param ulInNumberOfValues the number of values (value underfunctions) in the
		 * 	first area object (pAreaObject) for the bit number.
		 * @param ulInNumberOfPoints the number of points in the first area
		 * 	(pAreaObject)
		 * @param pAreaObject the first area, wich need as minimum the
		 * 	correspondending number of bits.
		 */
		cAreasBitInfo( const unsigned long ulInNumberOfValues=0,
				const unsigned long ulInNumberOfPoints=0, cFibElement * pAreaObject=NULL ):
				ulNumberOfValues( ulInNumberOfValues ),
				ulNumberOfPoints( ulInNumberOfPoints ){
			
			if ( pAreaObject ){
				liAreas.push_back( pAreaObject );
			}
		}
		
	};//end class cAreasBitInfo


	/**
	 * Class to compare two cAreaNeighbourNode classes via pointers to them.
	 */
	template< class tValue >
	class cAreaNeighbourNodePointerCompare{
	public:
		bool operator() ( const cAreaNeighbourNode< tValue > * area1, const cAreaNeighbourNode< tValue > * area2 ) const{
			return ( (*area1) < (*area2) );
		}
	};
	
	
	/**
	 * @param paFirstPoint the first point to campare
	 * @param paSecondPoint the second point to campare
	 * @return true if the first element of the first pair is lower than
	 * 	that of the second, else if bouth first elements are equal
	 * 	true if the first data point is lower, else false
	 */
	template< class tValue >
	bool sortNumberOrNeighbours( const pair< unsigned char,
				nD1::cDataPoint< tValue, tValue > > & paFirstPoint,
			const pair< unsigned char,
				nD1::cDataPoint< tValue, tValue > > & paSecondPoint ){
		
		if ( paFirstPoint.first != paSecondPoint.first ){
			return (paFirstPoint.first < paSecondPoint.first);
		}
		return (paFirstPoint.second < paSecondPoint.second);
	}


	/**
	 * This function is for sorting neighbour node areas, with the area
	 * with the most points at the front.
	 *
	 * @param pArea1 the first area neighbour node
	 * @param pArea2 the second area neighbour node
	 * @return if the first neighbour node has more points than the second true, else
	 * 	true if the first point has a lower pointer
	 */
	template< class tValue >
	bool higherPNeighboursPoints( const cAreaNeighbourNode< tValue > * pArea1,
			const cAreaNeighbourNode< tValue > * pArea2 ){
		
		const unsigned long ulPointsInArea1 = pArea1->getNumberOfAreaPoints();
		const unsigned long ulPointsInArea2 = pArea2->getNumberOfAreaPoints();
		if ( ulPointsInArea2 < ulPointsInArea1 ){
			return true;
		}//else
		if ( ulPointsInArea1 < ulPointsInArea2 ){
			return false;
		}//else
		return pArea1 < pArea2;
	}


};//end namespace nConvertReduced
};//end namespace nConvertToFib
};//end namespace fib





/**
 * This function converts the given multimediaobject into a fib -object.
 * It creats a fib -object with one master root -element which contains a
 * listelement as main -fib -object, which contains every point of the image.
 *
 * @param multimediaObject the multimedaobject to convert into fib;
 * 	the inputformat is in the FreeImagePlus fipImage object
 * @return the created fib -object
 */
cFibElement * fib::nConvertToFib::convert( const fipImage & multimediaObject ){
	
	DEBUG_OUT_L1( <<"fib::nConvertToFib::convert() started"<<endl; );
	
	const unsigned long ulWidth  = multimediaObject.getWidth();
	const unsigned long ulHeight = multimediaObject.getHeight();
	
	DEBUG_OUT_L1( <<"image size width="<< ulWidth <<" height="<< ulHeight <<endl; );
	
	/*for every point in the image include the corresponding point into the
	fib -object*/
	
	cTypeProperty typeProperty( cTypeProperty::COLOR_RGB );
	bool bSWColor = false;
	if ( multimediaObject.isGrayscale() ){
		typeProperty = cTypeProperty( cTypeProperty::COLOR_GRAYSCALE );
		bSWColor = true;
	}else{
		typeProperty = cTypeProperty( cTypeProperty::COLOR_RGB );
	}
	
	RGBQUAD * colorRGBValue = new RGBQUAD();
	BYTE * indexValue = new BYTE();
	
	RGBQUAD * colorPalette = multimediaObject.getPalette();
	const unsigned long ulPaletteSize = (colorPalette == NULL) ?
		0 : multimediaObject.getPaletteSize();
	//list with the underobjects for the pixels
	list<cFibElement*> liUnderobjects;
	
	if ( multimediaObject.hasFileBkColor() ){
		//evalue the backgroud color
		DEBUG_OUT_L1( <<"evalue the backgroud color"<<endl );
		
		const bool bBgColor = multimediaObject.getFileBkColor( colorRGBValue );
		if ( bBgColor ){
			cVectorPosition vecPosition( 0 );
			cPoint * pBackgroundPoint = new cPoint( &vecPosition );
			
			cVectorProperty vecProperty( typeProperty );
			//set the property values
			if ( colorPalette != NULL ){
				//till 8 bit -> convert index to RGB -Colorvalue
				
				if ( (colorRGBValue->rgbReserved) < ulPaletteSize ){
					*colorRGBValue = colorPalette[ colorRGBValue->rgbReserved ];
				}
			}
			if ( bSWColor ){
				vecProperty.setValue( 1, colorRGBValue->rgbRed );
			}else{
				vecProperty.setValue( 1, colorRGBValue->rgbRed );
				vecProperty.setValue( 2, colorRGBValue->rgbGreen );
				vecProperty.setValue( 3, colorRGBValue->rgbBlue );
			}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			cProperty * pProperty = new cProperty( vecProperty, pBackgroundPoint);
#else //FEATURE_SIMPLE_CONSTRUCTOR
			cProperty * pProperty = new cProperty( vecProperty, NULL, NULL, pBackgroundPoint);
#endif //FEATURE_SIMPLE_CONSTRUCTOR
			
			liUnderobjects.push_back( pProperty );
		}
	}
	bool bColor;
	cVectorPosition vecPosition( 2 );
	cVectorProperty vecProperty( typeProperty );
	for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
		
		list<cFibElement*> liUnderobjects2;
		for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
			//evalue the color of the point
			
			DEBUG_OUT_L1( <<"evalue point X="<< ulX <<" Y="<< ulY <<endl );
			
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue = colorPalette[ *indexValue ];
			}else{
				//from 16 bit upwards
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
			}
			
			if ( bColor ){
				vecPosition.setValue( 1, ulX );
				vecPosition.setValue( 2, ulY );
				cPoint * pPoint = new cPoint( &vecPosition );
				
				//set the property values
				if ( bSWColor ){
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
				}else{
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
					vecProperty.setValue( 2, colorRGBValue->rgbGreen );
					vecProperty.setValue( 3, colorRGBValue->rgbBlue );
				}
				
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
				cProperty * pProperty = new cProperty( vecProperty, pPoint);
#else //FEATURE_SIMPLE_CONSTRUCTOR
				cProperty * pProperty = new cProperty( vecProperty, NULL, NULL, pPoint);
#endif //FEATURE_SIMPLE_CONSTRUCTOR
				
				liUnderobjects2.push_back( pProperty );
			}
		}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
#ifdef FEATURE_BALANCED_LOAD
		cList * pUnderList = createBalancedList(
			liUnderobjects2, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
		cList * pUnderList = new cList( liUnderobjects2 );
#endif //FEATURE_BALANCED_LOAD
#else //FEATURE_SIMPLE_CONSTRUCTOR
		cList * pUnderList = new cList( NULL, NULL );
		pUnderList->addUnderobjects( liUnderobjects2 );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
		liUnderobjects.push_back( pUnderList );
	}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
#ifdef FEATURE_BALANCED_LOAD
	cList * pMainList = createBalancedList(
		liUnderobjects, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
	cList * pMainList = new cList( liUnderobjects );
#endif //FEATURE_BALANCED_LOAD
	
	cRoot * pMasterRoot = new cRoot( pMainList );
#else //FEATURE_SIMPLE_CONSTRUCTOR
	cList * pMainList = new cList( NULL, NULL );
	pMainList->addUnderobjects( liUnderobjects );
	
	cRoot * pMasterRoot = new cRoot( NULL, NULL, pMainList );
#endif //FEATURE_SIMPLE_CONSTRUCTOR
	
	/*evalue the size of the image and include a corresponding dimension
	domain in the root -element*/
	
	//set domains of master root -object
	cDomainNaturalNumber domainWidth( ulWidth );
	cDomainNaturalNumber domainHeight( ulHeight );
	//set the dimension domain
	cTypeDimension typeDimension( 2 );
	vector<cDomainSingle*> vecDomainsDimension;
	vecDomainsDimension.push_back( &domainWidth );
	vecDomainsDimension.push_back( &domainHeight );
	cDomainVector vectorDomainDimension( vecDomainsDimension );
	
	pMasterRoot->getDomains()->addDomain( typeDimension, vectorDomainDimension );

	/*evalue which properties are needed and include ther domains in the
	root -element*/
	//TODO include palletized domains
	
	unsigned int uiBitsPerColor = 0;
	if ( colorPalette == NULL ){
		uiBitsPerColor = multimediaObject.getBitsPerPixel();
	}else{
		if ( bSWColor ){
			uiBitsPerColor = 8;
		}else{
			uiBitsPerColor = 24;
		}
	}
	
	vector<cDomainSingle*> * pVecDomainColor = NULL;
	if ( bSWColor ){
		pVecDomainColor = new vector<cDomainSingle*>( 1, ((cDomainSingle*)NULL) );
		(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor );
	}else{
		pVecDomainColor = new vector<cDomainSingle*>( 3, ((cDomainSingle*)NULL) );
		if ( multimediaObject.getColorType() == FIC_RGB ){
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
		}else{//TODO include other color typs
			//for FIC_RGBALPHA
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
		}
	}
	cDomainVector vectorDomainProperty( *pVecDomainColor );
	
	for ( unsigned int uiVectorElement = 0;
			uiVectorElement < pVecDomainColor->size(); uiVectorElement++ ){
		
		delete ((*pVecDomainColor)[ uiVectorElement ]);
	}
	delete pVecDomainColor;
	
	pMasterRoot->getDomains()->addDomain( typeProperty, vectorDomainProperty );
	
	/*include image description data into the optionalpart of the
	root -element*/
	//TODO

	
	//clean
	delete colorRGBValue;
	delete indexValue;

	DEBUG_OUT_L1( <<"fib::nConvertToFib::convert() ended correctly"<<endl );
	
	return pMasterRoot;
}






/**
 * This function converts the given multimediaobject into a fib -object.
 * It creats a fib -object with one master root -element which contains a
 * listelement as main -fib -object.
 * the function will try to compress the pictur data. It will:
 * 	- sperate the points in respect of ther colors (properties)
 * 	- will create area fib-objects, for areas with the same color
 * if bCreatebackground is true;
 * 	- will set a background color, if non is given
 *
 * @see convert()
 * @param multimediaObject the multimedaobject to convert into fib;
 * 	the inputformat is in the FreeImagePlus fipImage object
 * @param bCreatebackground if true, this function will set a background
 * 	color, if non is given
 * @param bCorrectPoints if wrong points should be corrected, in the
 * 	last compressing step
 * @return the created fib -object
 */
cFibElement * fib::nConvertToFib::convertOptimized( const fipImage & multimediaObject,
		bool bCreatebackground, const bool bCorrectPoints ){
	
	DEBUG_OUT_L1( <<"fib::nConvertToFib::convertOptimized() started"<<endl; );
	
	const unsigned long ulWidth  = multimediaObject.getWidth();
	const unsigned long ulHeight = multimediaObject.getHeight();
	
	DEBUG_OUT_L1( <<"image size width="<< ulWidth <<" height="<< ulHeight <<endl; );
	
	/*for every point in the image include the corresponding point into the
	fib -object*/
	
	cTypeProperty typeProperty( cTypeProperty::COLOR_RGB );
	bool bSWColor = false;
	if ( multimediaObject.isGrayscale() ){
		typeProperty = cTypeProperty( cTypeProperty::COLOR_GRAYSCALE );
		bSWColor = true;
	}else{
		typeProperty = cTypeProperty( cTypeProperty::COLOR_RGB );
	}
	
	RGBQUAD * colorRGBValue = new RGBQUAD();
	BYTE * indexValue = new BYTE();
	
	RGBQUAD * colorPalette = multimediaObject.getPalette();
	const unsigned long ulPaletteSize = (colorPalette == NULL) ?
		0 : multimediaObject.getPaletteSize();
	//list with the underobjects for the pixels
	list< cFibElement* > liUnderobjects;
	
	cProperty * pBackgroundProperty = NULL;
	
	if ( multimediaObject.hasFileBkColor() ){
		//don't create a background property
		bCreatebackground = false;
		//evalue the backgroud color
		DEBUG_OUT_L1( <<"evalue the backgroud color"<<endl );
		const bool bBgColor = multimediaObject.getFileBkColor( colorRGBValue );
		if ( bBgColor ){
			cVectorPosition vecPosition( 0 );
			cPoint * pBackgroundPoint = new cPoint( &vecPosition );
			
			cVectorProperty vecProperty( typeProperty );
			//set the property values
			if ( colorPalette != NULL ){
				//till 8 bit -> convert index to RGB -Colorvalue
				
				if ( (colorRGBValue->rgbReserved) < ulPaletteSize ){
					*colorRGBValue = colorPalette[ colorRGBValue->rgbReserved ];
				}
			}
			if ( bSWColor ){
				vecProperty.setValue( 1, colorRGBValue->rgbRed );
			}else{
				vecProperty.setValue( 1, colorRGBValue->rgbRed );
				vecProperty.setValue( 2, colorRGBValue->rgbGreen );
				vecProperty.setValue( 3, colorRGBValue->rgbBlue );
			}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			pBackgroundProperty = new cProperty( vecProperty, pBackgroundPoint);
#else //FEATURE_SIMPLE_CONSTRUCTOR
			pBackgroundProperty = new cProperty( vecProperty, NULL, NULL, pBackgroundPoint);
#endif //FEATURE_SIMPLE_CONSTRUCTOR
			
			liUnderobjects.push_back( pBackgroundProperty );
		}
	}
//sperate the points in respect of ther colors (properties)
	/*the map with the data for the pictur:
		- first element: the color of the points
		- second element: the points with the color*/
	typedef set< nD1::cDataPoint< unsigned long, unsigned long > >
				typeSetPoints;
	map< cVectorProperty, typeSetPoints > mapPicturPointData;
	
	DEBUG_OUT_L1(<<"loading pointdata"<<endl );
	bool bColor;
	cVectorProperty vecProperty( typeProperty );
	for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
		
		for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
			//evalue the color of the point
			
//			DEBUG_OUT_L4( <<"evalue point X="<< ulX <<" Y="<< ulY <<endl );
			
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue = colorPalette[ *indexValue ];
			}else{
				//from 16 bit upwards
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
			}
			
			if ( bColor ){
				//set the property values
				if ( bSWColor ){
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
				}else{
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
					vecProperty.setValue( 2, colorRGBValue->rgbGreen );
					vecProperty.setValue( 3, colorRGBValue->rgbBlue );
				}
				
				mapPicturPointData[ vecProperty ].insert(
					nD1::cDataPoint< unsigned long, unsigned long >( ulX, ulY ) );
			}
		}
	}
//create area fib-objects, for areas with the same color
	
	/*if a background property should be created, this map contains the
	bits for the fib-objects for the different properties*/
	map< cVectorProperty, unsignedLongFib > mapBitsPerProperty;
	/*TODO?: a set with the points created till now
	set< nD1::cDataPoint< unsigned long , unsigned long > > setOverlapedPoints;*/
	
	DEBUG_OUT_L1(<<"create area fib-objects, for areas with the same color"<<endl );
	for ( map< cVectorProperty, typeSetPoints >::iterator
			itrProperty = mapPicturPointData.begin();
			itrProperty != mapPicturPointData.end(); itrProperty++ ){
		//build an underobject for all points for the property
		list<cFibElement*> liUnderobjectsForProperty;
		
		typeSetPoints & setOfPoints = itrProperty->second;
		cVectorPosition vecPosition( 2 );
		
		if ( bCreatebackground ){
			//this property uses 0 bits till now
			mapBitsPerProperty[ itrProperty->first ] = 0;
		}
		while ( ! setOfPoints.empty() ){
			//find the are for the first point in the set
			
			//a set with the neighbourpoints to check the neighbours of
			typeSetPoints setPointsToCheck;
			setPointsToCheck.insert( *(setOfPoints.begin()) );
			setOfPoints.erase( setOfPoints.begin() );
			//a set with the neighbourpoints which neighbours are checked
			typeSetPoints setCheckedPoints;
			
			while ( ! setPointsToCheck.empty() ){
				
				typeSetPoints::iterator itrPointToCheck = setPointsToCheck.begin();
				
				const unsigned long ulActualPosDim1 = itrPointToCheck->x;
				const unsigned long ulActualPosDim2 = itrPointToCheck->y;
				setCheckedPoints.insert( * itrPointToCheck );
				setPointsToCheck.erase( itrPointToCheck );
				
				//check the 8 neighbours of the point
				//compare the properties of the points with the properties of the original point
				for ( unsigned int uiNeighbour = 0; uiNeighbour < 8; uiNeighbour++ ){
					
					nD1::cDataPoint< unsigned long , unsigned long > actualPosition;
					switch ( uiNeighbour ){
						case 0:
							if ( ulActualPosDim1 <= 0 ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1 - 1;
							actualPosition.y = ulActualPosDim2;
						break;
						case 1:
							if ( ulWidth <= ulActualPosDim1 ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1 + 1;
							actualPosition.y = ulActualPosDim2;
						break;
						case 2:
							if ( ulActualPosDim2 <= 0 ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1;
							actualPosition.y = ulActualPosDim2 - 1;
						break;
						case 3:
							if ( ulHeight <= ulActualPosDim2 ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1;
							actualPosition.y = ulActualPosDim2 + 1;
						break;
						case 4:
							if ( (ulActualPosDim1 <= 0) || (ulActualPosDim2 <= 0) ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1 - 1;
							actualPosition.y = ulActualPosDim2 - 1;
						break;
						case 5:
							if ( (ulActualPosDim1 <= 0) || (ulHeight <= ulActualPosDim2) ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1 - 1;
							actualPosition.y = ulActualPosDim2 + 1;
						break;
						case 6:
							if ( (ulWidth <= ulActualPosDim1) || (ulActualPosDim2 <= 0) ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1 + 1;
							actualPosition.y = ulActualPosDim2 - 1;
						break;
						case 7:
							if ( (ulWidth <= ulActualPosDim1) || (ulHeight <= ulActualPosDim2) ){
								continue;//no neighbour in direction
							}
							actualPosition.x  = ulActualPosDim1 + 1;
							actualPosition.y = ulActualPosDim2 + 1;
						break;
						default:
							continue;//unknown neighbour -> switch it
					}
					//check if point was checked befor
					if ( ( setCheckedPoints.find( actualPosition ) == setCheckedPoints.end() ) &&
							( setPointsToCheck.find( actualPosition ) == setPointsToCheck.end() ) ){
						/*point not checked befor and not allready notified to check
						-> check if it has the correct properties*/
						
						//if the point is in the actual property set -> it has the correct properties
						const typeSetPoints::iterator itrActualPoint =
							setOfPoints.find( actualPosition );
						
						if ( itrActualPoint == setOfPoints.end() ){
							//no such point -> check next point
							continue;
						}
						//add point to the area
						setPointsToCheck.insert( actualPosition );
						//actual point isn't needed anymore
						setOfPoints.erase( itrActualPoint );
					}
				}
			}
/*TODO			setOverlapedPoints.insert( setCheckedPoints.begin(),
				setCheckedPoints.end() );*/
			if ( setCheckedPoints.size() < MIN_POINTS_FOR_AREA ){
#ifndef N_CONVERT_TO_FIB_NO_POINTS
				/*if area has less than tree points
				-> don't create an area object and add the points directly*/
				DEBUG_OUT_L2(<<"less than "<<MIN_POINTS_FOR_AREA<<" ("<<setCheckedPoints.size()<< ") points in area -> store points directly"<<endl<<flush);
				for ( typeSetPoints::iterator itrPoint = setCheckedPoints.begin();
						itrPoint != setCheckedPoints.end(); itrPoint++ ){
					
					vecPosition.setValue( 1, itrPoint->x );
					vecPosition.setValue( 2, itrPoint->y );
					cPoint * pPoint = new cPoint( &vecPosition );
					
					liUnderobjectsForProperty.push_front( pPoint );
				}
				if ( bCreatebackground ){
					//add bits for setCheckedPoints.size() points
					mapBitsPerProperty[ itrProperty->first ] += setCheckedPoints.size() *
						liUnderobjectsForProperty.back()->getCompressedSize();
				}
#endif //N_CONVERT_TO_FIB_NO_POINTS
			}else{//create area object for point area
#ifndef N_CONVERT_TO_FIB_NO_AREAS
				cFibVariable * pVariableX = new cFibVariable( NULL );
				cFibVariable * pVariableY = new cFibVariable( NULL );
				cVectorPosition vecPositionVariable( 2 );
				vecPositionVariable.setVariable( 1, pVariableX );
				vecPositionVariable.setVariable( 2, pVariableY );
				
				cPoint * pNewPoint = new cPoint( & vecPositionVariable );
				
				set< nD1::cDataPoint< unsigned long , unsigned long > > setActualMissingPoints;
#ifdef FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
				DEBUG_OUT_L2(<<"createNSplineBorderAreasForPoints( #setPointsOfArea="<<setCheckedPoints.size()<<" )"<<endl<<flush);
				cFibElement * pAreaFibObject = nD2::createNSplineBorderAreasForPoints< unsigned long >(
						setCheckedPoints, setCheckedPoints, pNewPoint, pVariableX, pVariableY, 4,
						& setActualMissingPoints );
#else //FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
				DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints( #setPointsOfArea="<<setCheckedPoints.size()<<" )"<<endl<<flush);
//				DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints( #setPointsOfArea="<<setCheckedPoints.size()<<", #setOverlapedPoints="<<setOverlapedPoints.size()<<" )"<<endl<<flush);
				cFibElement * pAreaFibObject = nD2::createSplineItrFastBorderAreasForPoints< unsigned long >(
						setCheckedPoints, setCheckedPoints, pNewPoint, pVariableX, pVariableY, 4,
						& setActualMissingPoints );
#endif //FEATURE_CONVERT_TO_FIB_AREA_GENERATOR

				delete pVariableX;
				delete pVariableY;
				if ( pAreaFibObject ){
					liUnderobjectsForProperty.push_front( pAreaFibObject );
					
					if ( bCreatebackground ){
						//add bits for the created underobject
						mapBitsPerProperty[ itrProperty->first ] +=
							pAreaFibObject->getCompressedSize();
					}
					for ( set< nD1::cDataPoint< unsigned long , unsigned long > >::iterator itrPoint = setActualMissingPoints.begin();
							itrPoint != setActualMissingPoints.end(); itrPoint++ ){
						
						vecPosition.setValue( 1, itrPoint->x );
						vecPosition.setValue( 2, itrPoint->y );
						cPoint * pPoint = new cPoint( &vecPosition );
						
						liUnderobjectsForProperty.push_front( pPoint );
					}
					if ( bCreatebackground ){
						//add bits for setCheckedPoints.size() points
						mapBitsPerProperty[ itrProperty->first ] += setActualMissingPoints.size() *
							liUnderobjectsForProperty.back()->getCompressedSize();
					}
				}else{
					DEBUG_OUT_EL2(<<"Error: Area creation function returned NULL."<<endl<<flush);
					pNewPoint->deleteObject();
					//add points
					for ( typeSetPoints::iterator itrPoint = setCheckedPoints.begin();
							itrPoint != setCheckedPoints.end(); itrPoint++ ){
						
						vecPosition.setValue( 1, itrPoint->x );
						vecPosition.setValue( 2, itrPoint->y );
						cPoint * pPoint = new cPoint( &vecPosition );
						
						liUnderobjectsForProperty.push_front( pPoint );
					}
					if ( bCreatebackground ){
						//add bits for setCheckedPoints.size() points
						mapBitsPerProperty[ itrProperty->first ] += setCheckedPoints.size() *
							liUnderobjectsForProperty.back()->getCompressedSize();
					}
				}
#endif //N_CONVERT_TO_FIB_NO_AREAS
			}
		}
#ifdef DEBUG
		cout<<liUnderobjectsForProperty.size()<<" created fib-underobjects for color: "<<endl;
		itrProperty->first.storeXml( cout );
		cout<<endl<<flush;
#endif //DEBUG
		if ( 2 <= liUnderobjectsForProperty.size() ){
#ifdef FEATURE_BALANCED_LOAD
			cList * pUnderListProperty = createBalancedList(
				liUnderobjectsForProperty, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
			cList * pUnderListProperty = new cList( liUnderobjectsForProperty );
#endif //FEATURE_BALANCED_LOAD
			cProperty * pProperty = new cProperty( itrProperty->first, pUnderListProperty );
			
			liUnderobjects.push_front( pProperty );
		}else if ( ! liUnderobjectsForProperty.empty() ){
			
			cProperty * pProperty = new cProperty( itrProperty->first,
				liUnderobjectsForProperty.front() );
			liUnderobjects.push_front( pProperty );
		}//else error no underobject -> nothing to insert
	}
	
	if ( ( bCreatebackground ) && ( ! multimediaObject.hasFileBkColor() ) &&
			( ! mapBitsPerProperty.empty() ) ){
		//set a background color, if non is given
		DEBUG_OUT_L1(<<endl<<"set a background color, if non is given"<<endl );
		//search for the propertie which uses the most bits
		const cVectorProperty * pPropertyUsesMostBits;
		unsignedLongFib ulMaxBits = 0;
		for ( map< cVectorProperty, unsignedLongFib >::iterator
				itrProperty = mapBitsPerProperty.begin();
				itrProperty != mapBitsPerProperty.end(); itrProperty++ ){
			
			if ( ulMaxBits < itrProperty->second ){
				//actual property uses most bits till now
				pPropertyUsesMostBits = &(itrProperty->first);
				ulMaxBits = itrProperty->second;
			}
		}
#ifdef DEBUG
		cout<<"the founded background color with the most (="<<ulMaxBits<<
			") bits is:"<<endl;
		pPropertyUsesMostBits->storeXml( cout );
#endif //DEBUG
		//remove fib-object for property, which uses the most bits
		for ( list< cFibElement* >::iterator
				itrPropertyUnderobject = liUnderobjects.begin();
				itrPropertyUnderobject != liUnderobjects.end(); itrPropertyUnderobject++ ){
			
			if ( (*itrPropertyUnderobject)->getType() != 'y' ){
				//error 
				DEBUG_OUT_EL2(<<"actual fib-object has no property as its top most element "<<endl );
				continue;
			}
			cProperty * pProperty = ((cProperty*)(*itrPropertyUnderobject));
			
			if ( pProperty->getProperty()->equal( *pPropertyUsesMostBits ) ){
				/*this is the new background property
				-> remove this fib-element and done*/
				DEBUG_OUT_L2(<<"removing fib-object for background property "<<endl );
				pProperty->deleteObject();
				liUnderobjects.erase( itrPropertyUnderobject );
				break;
			}
		}
		//add new background property
		DEBUG_OUT_L2(<<"adding background property "<<endl );
		cVectorPosition vecPositionBackground( 0 );
		cPoint * pBackgroundPoint = new cPoint( &vecPositionBackground );
		pBackgroundProperty = new cProperty( *pPropertyUsesMostBits, pBackgroundPoint );
		liUnderobjects.push_back( pBackgroundProperty );
	}
	
	//set domains of master root -object
	cDomainNaturalNumber domainWidth( ulWidth );
	cDomainNaturalNumber domainHeight( ulHeight );
	//set the dimension domain
	cTypeDimension typeDimension( 2 );
	vector<cDomainSingle*> vecDomainsDimension;
	vecDomainsDimension.push_back( &domainWidth );
	vecDomainsDimension.push_back( &domainHeight );
	cDomainVector vectorDomainDimension( vecDomainsDimension );

	//correct wrong points
	if ( bCorrectPoints ){
		DEBUG_OUT_L2(<<endl<<"correcting wrong points"<<endl );
		//compare with background color
		bool matrixCorrectPoints[ ulWidth ][ ulHeight ];
		
		if ( pBackgroundProperty ){
			DEBUG_OUT_L2(<<"evaluing if background is correct "<<endl );
			
			const cVectorProperty & vecBgProperty =
				*(pBackgroundProperty->getProperty());
			for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
				for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
					//evalue the color of the point
					
					if ( colorPalette != NULL ){
						//till 8 bit
						bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
						
						if ( ulPaletteSize <= *indexValue ){
							continue;//skip pixel
						}
						*colorRGBValue = colorPalette[ *indexValue ];
					}else{
						//from 16 bit upwards
						bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
					}
					
					if ( bColor ){
						//set the property values
						if ( bSWColor ){
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
						}else{
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
							vecProperty.setValue( 2, colorRGBValue->rgbGreen );
							vecProperty.setValue( 3, colorRGBValue->rgbBlue );
						}
					}
					//compare with background color
					if ( vecBgProperty == vecProperty ){
						matrixCorrectPoints[ ulX ][ ulY ] = true;
					}else{
						matrixCorrectPoints[ ulX ][ ulY ] = false;
					}
				}
			}
		}else{//no background property
			DEBUG_OUT_L2(<<"set all points to wrong "<<endl );
			for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
				for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
					//evalue the color of the point
					matrixCorrectPoints[ ulX ][ ulY ] = false;
				}
			}
		}
		//compare with points
		const unsignedLongFib ulNumberOfPoints = ulWidth * ulHeight;
		for ( list< cFibElement* >::iterator itrUnderobject = liUnderobjects.begin();
				itrUnderobject != liUnderobjects.end(); itrUnderobject++ ){
			
			const cVectorProperty & vecActualProperty =
				*( ((cProperty*)(*itrUnderobject))->getProperty() );
			//evalue the underobject
#ifdef DEBUG
			cout<<"evaluing error points for property:"<<endl;
			vecActualProperty.storeXml( cout );
#endif //DEBUG
			cEvaluePositionListLimit evaluedPositionData( ulNumberOfPoints * 2,
				& vectorDomainDimension, true, 0, ulNumberOfPoints * 64 );
			
			//discard the property element
			const cFibElement * pFibObjectToEvalue =
				(*itrUnderobject)->getNextFibElement();
			
			const bool bObjectEvalued = pFibObjectToEvalue->evalueObjectSimple(
				evaluedPositionData );
			if ( ! bObjectEvalued ){
				DEBUG_OUT_EL1( <<"Error: The fib -object couldn't be evalued."<<endl );
				continue;
			}
			
			const list< pair< cVectorPosition, list< cVectorProperty > > > &
				liPoints = evaluedPositionData.liEvaluedPositionData;
			//compare evalued points with the picture
			for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
					itrActualPoint = liPoints.begin();
					itrActualPoint != liPoints.end(); itrActualPoint++ ){
				
				const cVectorPosition & position = itrActualPoint->first;
				const unsigned long ulX = roundToLongFib( position.getValue( 1 ) );
				const unsigned long ulY = roundToLongFib( position.getValue( 2 ) );
					
				if ( colorPalette != NULL ){
					//till 8 bit
					bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
					
					if ( ulPaletteSize <= *indexValue ){
						continue;//skip pixel
					}
					*colorRGBValue = colorPalette[ *indexValue ];
				}else{
					//from 16 bit upwards
					bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
				}
				
				if ( bColor ){
					//set the property values
					if ( bSWColor ){
						vecProperty.setValue( 1, colorRGBValue->rgbRed );
					}else{
						vecProperty.setValue( 1, colorRGBValue->rgbRed );
						vecProperty.setValue( 2, colorRGBValue->rgbGreen );
						vecProperty.setValue( 3, colorRGBValue->rgbBlue );
					}
				}
				//compare with background color
				if ( vecActualProperty == vecProperty ){
					matrixCorrectPoints[ ulX ][ ulY ] = true;
				}else{
					matrixCorrectPoints[ ulX ][ ulY ] = false;
				}
			}
		}
		//add wrong points
		map< cVectorProperty, list< cFibElement * > > mapWrongPoints;
		bool bWrongPointsExists = false;
		cVectorPosition vecPosition( 2 );
		for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
			for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
				//evalue the color of the point
				if ( ! matrixCorrectPoints[ ulX ][ ulY ] ){
					//wrong point -> correct point
					bWrongPointsExists = true;
					
					if ( colorPalette != NULL ){
						//till 8 bit
						bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
						
						if ( ulPaletteSize <= *indexValue ){
							continue;//skip pixel
						}
						*colorRGBValue = colorPalette[ *indexValue ];
					}else{
						//from 16 bit upwards
						bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
					}
					
					if ( bColor ){
						//set the property values
						if ( bSWColor ){
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
						}else{
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
							vecProperty.setValue( 2, colorRGBValue->rgbGreen );
							vecProperty.setValue( 3, colorRGBValue->rgbBlue );
						}
					}
					vecPosition.setValue( 1, ulX );
					vecPosition.setValue( 2, ulY );
					cPoint * pPoint = new cPoint( &vecPosition );
#ifdef DEBUG
					cout<<"founded wrong point ("<<ulX<<", "<<ulY<<") for property:"<<endl;
					vecProperty.storeXml( cout );
#endif //DEBUG
					mapWrongPoints[ vecProperty ].push_back( pPoint );
				}
			}
		}
		if ( bWrongPointsExists ){
			//insert wrong points in underobject
			for ( list< cFibElement* >::iterator itrUnderobject = liUnderobjects.begin();
					itrUnderobject != liUnderobjects.end(); itrUnderobject++ ){
				
				cFibElement * pPropertyElement = (*itrUnderobject);
				const cVectorProperty & vecActualProperty =
					*( ((cProperty*)(pPropertyElement))->getProperty() );
				
				map< cVectorProperty, list< cFibElement * > >::iterator
					itrWrongPointsForProperty = mapWrongPoints.find( vecActualProperty );
				
				if ( ( itrWrongPointsForProperty != mapWrongPoints.end() ) &&
						( ! itrWrongPointsForProperty->second.empty() ) ){
#ifdef DEBUG
					cout<<"adding wrong points for property:"<<endl;
					vecActualProperty.storeXml( cout );
#endif //DEBUG
					//ther are wrong points for the actual property
					cFibElement * pNextElement =
						pPropertyElement->getNextFibElement();
					
					if ( pNextElement->getType() == 'l' ){
						//if list
						((cList*)pNextElement)->addUnderobjects(
							itrWrongPointsForProperty->second );
					}else{//if point
						//create new listelement
						itrWrongPointsForProperty->second.push_back( pNextElement );
						cList * pNewList = new cList( itrWrongPointsForProperty->second );
						pPropertyElement->overwriteObjectWithObject( pNewList, 'u', 0, false );
					}
				}
			}
		}
	}//end correct wrong points
	
	cFibElement * pMainFibObject = NULL;
	if ( 2 <= liUnderobjects.size() ){
#ifdef FEATURE_BALANCED_LOAD
		pMainFibObject = createBalancedList(
			liUnderobjects, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
		pMainFibObject = new cList( liUnderobjects );
#endif //FEATURE_BALANCED_LOAD
	}else if ( ! liUnderobjects.empty() ){
		
		pMainFibObject = liUnderobjects.front();
	}else{
		DEBUG_OUT_EL2(<<"Error: no underobjects to create the fib object"<<endl<<flush);
		DEBUG_OUT_EL2( <<"fib::nConvertToFib::convertOptimized() done"<<endl );
		return NULL;
	}
	cRoot * pMasterRoot = new cRoot( pMainFibObject );
	
	/*evalue the size of the image and include a corresponding dimension
	domain in the root -element*/
	
	
	pMasterRoot->getDomains()->addDomain( typeDimension, vectorDomainDimension );

	/*evalue which properties are needed and include ther domains in the
	root -element*/
	//TODO include palletized domains
	
	unsigned int uiBitsPerColor = 0;
	if ( colorPalette == NULL ){
		uiBitsPerColor = multimediaObject.getBitsPerPixel();
	}else{
		if ( bSWColor ){
			uiBitsPerColor = 8;
		}else{
			uiBitsPerColor = 24;
		}
	}
	
	vector<cDomainSingle*> * pVecDomainColor = NULL;
	if ( bSWColor ){
		pVecDomainColor = new vector<cDomainSingle*>( 1, ((cDomainSingle*)NULL) );
		(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor );
	}else{
		pVecDomainColor = new vector<cDomainSingle*>( 3, ((cDomainSingle*)NULL) );
		if ( multimediaObject.getColorType() == FIC_RGB ){
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
		}else{//TODO include other color typs
			//for FIC_RGBALPHA
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
		}
	}
	cDomainVector vectorDomainProperty( *pVecDomainColor );
	
	for ( unsigned int uiVectorElement = 0;
			uiVectorElement < pVecDomainColor->size(); uiVectorElement++ ){
		
		delete ((*pVecDomainColor)[ uiVectorElement ]);
	}
	delete pVecDomainColor;
	
	pMasterRoot->getDomains()->addDomain( typeProperty, vectorDomainProperty );
	//generate domains for the function and area elements
	pMasterRoot->generateNeededDomains();
	
	/*include image description data into the optionalpart of the
	root -element*/
	//TODO
	
	
	//clean
	delete colorRGBValue;
	delete indexValue;

	DEBUG_OUT_L1( <<"fib::nConvertToFib::convertOptimized() ended correctly"<<endl );
	
	return pMasterRoot;
}



/**
 * This function converts the given multimediaobject into a fib -object.
 * It will reduce the data to compress, so not all points in the created
 * fib-object will have the correct color.
 * It creats a fib -object with one master root -element which contains a
 * listelement as main -fib -object.
 * the function will try to compress the pictur data. It will:
 * 	- sperate the points in respect of ther colors (properties)
 * 	- will create area fib-objects, for areas with the similar color
 * if bCreatebackground is true;
 * 	- will set a background color, if non is given
 *
 * @see convert()
 * @param multimediaObject the multimedaobject to convert into fib;
 * 	the inputformat is in the FreeImagePlus fipImage object
 * @param bCreatebackground if true, this function will set a background
 * 	color, if non is given
 * @param ulMaxAreaDiff the maximal difference of color values in an area
 * 	(as the sum of the color vector element distances)
 * @param ulMinPoints if an area with less than ulMinPoints points exists and
 * 	it layes beside an area with a color, wich has a less difference as
 * 	ulMaxDiff to the color of the first area, both areas will be
 * 	combinde with the color of the second area (if the first area has
 * 	more than one area as a neighbour, which fulfill ulMaxDiff, the one
 * 	with the minimum color distance is taken)
 * @param ulMaxDiff @see ulMinPoints
 * @param uiMinPointsNeighbourAreas all neighbour areas with less than
 * 	this number of points, will be subsumed by the area
 * @param bCorrectPoints if wrong points should be corrected, in the
 * 	last compressing step
 * @param bCorrectMissingPoints correct points, wich are missing in the
 * 	created area fib-objects
 * @param bAddNeighbours add to the areas ther neighbours and remove not needed areas
 * @param bReduceFunctionDomains reduce the bits to store the function (values)
 * @param bReplaceAreasWithPoints rreplace areas, which need more bits
 * 	to store than ther points, with ther points
 * @param uiInMinPointsForArea the minimal number of points an area
 * 	should have, to create an area object for it;
 * 	if 0 the standad value will be taken
 * @param maxError the maximal error for the area border polynoms to find;
 * 	the error on the interpolated polynoms for the borders of the areas
 * 	will beequal or less than maxError
 * @return the created fib -object
 */
cFibElement * fib::nConvertToFib::convertReduced( const fipImage & multimediaObject,
		bool bCreatebackground, const unsigned long ulMaxAreaDiff,
		const unsigned long ulMinPoints, const unsigned long ulMaxDiff,
		const unsigned int uiMinPointsNeighbourAreas,
		const bool bCorrectPoints,  const bool bCorrectMissingPoints,
		const bool bAddNeighbours, const bool bReduceFunctionDomains,
		const bool bReplaceAreasWithPoints, const unsigned int uiInMinPointsForArea,
		const double maxError ){
	
	DEBUG_OUT_L1( <<"fib::nConvertToFib::convertReduced( multimediaObject, bCreatebackground="<<bCreatebackground<<", ulMaxAreaDiff="<<ulMaxAreaDiff<<", ulMinPoints="<<ulMinPoints<<", ulMaxDiff="<<ulMaxDiff<<", bCorrectPoints="<<bCorrectPoints<<", bCorrectMissingPoints="<<bCorrectMissingPoints<<", bAddNeighbours="<<bAddNeighbours<<", bReduceFunctionDomains="<<bReduceFunctionDomains<<", bReplaceAreasWithPoints="<<bReplaceAreasWithPoints<<", uiInMinPointsForArea="<<uiInMinPointsForArea<<"  ) started"<<endl; );
	
	if ( ( ulMaxAreaDiff == 0 ) && ( ulMinPoints == 0 ) && ( ulMaxDiff == 0 ) ){
		//don*t need this function -> use simpler function
		return convertOptimized( multimediaObject, bCreatebackground=true, bCorrectPoints );
	}
	
	
	const unsigned long ulWidth  = multimediaObject.getWidth();
	const unsigned long ulHeight = multimediaObject.getHeight();
	
	DEBUG_OUT_L1(<<"image size width="<<ulWidth<<" height="<<ulHeight<<endl; );
	
	const unsigned int uiMinPointsForArea = (uiInMinPointsForArea != 0) ?
		uiInMinPointsForArea : ( bReplaceAreasWithPoints ? 5 :
		(bReduceFunctionDomains ? (MIN_POINTS_FOR_AREA / 2) : MIN_POINTS_FOR_AREA) );
	DEBUG_OUT_L1(<<"minimal points to create an area object="<<uiMinPointsForArea<<endl; );
	
	/*for every point in the image include the corresponding point into the
	fib -object*/
	
	cTypeProperty typeProperty( cTypeProperty::COLOR_RGB );
	bool bSWColor = false;
	if ( multimediaObject.isGrayscale() ){
		typeProperty = cTypeProperty( cTypeProperty::COLOR_GRAYSCALE );
		bSWColor = true;
	}else{
		typeProperty = cTypeProperty( cTypeProperty::COLOR_RGB );
	}
	
	RGBQUAD * colorRGBValue = new RGBQUAD();
	BYTE * indexValue = new BYTE();
	
	RGBQUAD * colorPalette = multimediaObject.getPalette();
	const unsigned long ulPaletteSize = (colorPalette == NULL) ?
		0 : multimediaObject.getPaletteSize();
	//list with the underobjects for the pixels
	list< cFibElement* > liUnderobjects;
	cProperty * pBackgroundProperty = NULL;
	
	if ( multimediaObject.hasFileBkColor() ){
		//don't create a background property
		bCreatebackground = false;
		//evalue the backgroud color
		DEBUG_OUT_L1( <<"evalue the backgroud color"<<endl );
		const bool bBgColor = multimediaObject.getFileBkColor( colorRGBValue );
		if ( bBgColor ){
			cVectorPosition vecPosition( 0 );
			cPoint * pBackgroundPoint = new cPoint( &vecPosition );
			
			cVectorProperty vecProperty( typeProperty );
			//set the property values
			if ( colorPalette != NULL ){
				//till 8 bit -> convert index to RGB -Colorvalue
				
				if ( (colorRGBValue->rgbReserved) < ulPaletteSize ){
					*colorRGBValue = colorPalette[ colorRGBValue->rgbReserved ];
				}
			}
			if ( bSWColor ){
				vecProperty.setValue( 1, colorRGBValue->rgbRed );
			}else{
				vecProperty.setValue( 1, colorRGBValue->rgbRed );
				vecProperty.setValue( 2, colorRGBValue->rgbGreen );
				vecProperty.setValue( 3, colorRGBValue->rgbBlue );
			}
#ifdef FEATURE_SIMPLE_CONSTRUCTOR
			pBackgroundProperty = new cProperty( vecProperty, pBackgroundPoint);
#else //FEATURE_SIMPLE_CONSTRUCTOR
			pBackgroundProperty = new cProperty( vecProperty, NULL, NULL, pBackgroundPoint);
#endif //FEATURE_SIMPLE_CONSTRUCTOR
			
			liUnderobjects.push_back( pBackgroundProperty );
		}
	}
//sperate the points in respect of ther colors (properties)
	/*the map with the data for the pictur:
		- first element: the color of the points
		- second element: the points with the color*/
	typedef unsigned int typeValue;
	typedef nD1::cDataPoint< typeValue, typeValue > typeDataPoint;
	typedef set< typeDataPoint > typeSetPoints;
	map< cVectorProperty, typeSetPoints > mapPicturPointData;
	
	DEBUG_OUT_L1(<<"loading pointdata"<<endl );
	bool bColor;
	cVectorProperty vecProperty( typeProperty );
	for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
		
		for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
			//evalue the color of the point
			
//			DEBUG_OUT_L4( <<"evalue point X="<< ulX <<" Y="<< ulY <<endl );
			
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue = colorPalette[ *indexValue ];
			}else{
				//from 16 bit upwards
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
			}
			
			if ( bColor ){
				//set the property values
				if ( bSWColor ){
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
				}else{
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
					vecProperty.setValue( 2, colorRGBValue->rgbGreen );
					vecProperty.setValue( 3, colorRGBValue->rgbBlue );
				}
				
				mapPicturPointData[ vecProperty ].insert( typeDataPoint( ulX, ulY ) );
			}
		}
	}
	if ( pBackgroundProperty ){
		//remove background points
#ifdef DEBUG
		cout<<"removing points for background property: "<<endl;
		(pBackgroundProperty->getProperty())->storeXml( cout );
#endif //DEBUG
		mapPicturPointData.erase( *(pBackgroundProperty->getProperty()) );
	}
//create area fib-objects, for areas with the same color

	DEBUG_OUT_L1(<<"finding same color areas"<<endl );

	/*The map with the same color areas of the picture:
		- key: the color of the areas
		- value: list of pairs:
			- first element: the points of the area
			- second element: the neighbour points of the area

	*/
	typedef map< cVectorProperty, list< pair< typeSetPoints, typeSetPoints > > > typeMapAreas;
	typeMapAreas mapAreas;
	
	for ( map< cVectorProperty, typeSetPoints >::iterator
			itrProperty = mapPicturPointData.begin();
			itrProperty != mapPicturPointData.end(); itrProperty++ ){
		//build an underobject for all points for the property
		
		const cVectorProperty & actualProperty = itrProperty->first;
		
		typeSetPoints & setOfPoints = itrProperty->second;
		cVectorPosition vecPosition( 2 );
		
		while ( ! setOfPoints.empty() ){
			//find the are for the first point in the set
			
			//a set with the neighbourpoints to check the neighbours of
			typeSetPoints setPointsToCheck;
			setPointsToCheck.insert( *(setOfPoints.begin()) );
			setOfPoints.erase( setOfPoints.begin() );
			//a set with the neighbourpoints which neighbours are checked
			typeSetPoints setCheckedPoints;
			typeSetPoints setNeighbourPoints;
			
			while ( ! setPointsToCheck.empty() ){
				
				typeSetPoints::iterator itrPointToCheck = setPointsToCheck.begin();
				
				const unsigned long ulActualPosDim1 = itrPointToCheck->x;
				const unsigned long ulActualPosDim2 = itrPointToCheck->y;
				setCheckedPoints.insert( * itrPointToCheck );
				setPointsToCheck.erase( itrPointToCheck );
				
				//check the 8 neighbours of the point
				//compare the properties of the points with the properties of the original point
				for ( unsigned int uiNeighbour = 0; uiNeighbour < 8; uiNeighbour++ ){
					
					typeDataPoint actualPosition;
					switch ( uiNeighbour ){
						case 0:
							if ( ulActualPosDim1 <= 0 ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1 - 1;
							actualPosition.y = ulActualPosDim2;
						break;
						case 1:
							if ( ulWidth <= ulActualPosDim1 ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1 + 1;
							actualPosition.y = ulActualPosDim2;
						break;
						case 2:
							if ( ulActualPosDim2 <= 0 ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1;
							actualPosition.y = ulActualPosDim2 - 1;
						break;
						case 3:
							if ( ulHeight <= ulActualPosDim2 ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1;
							actualPosition.y = ulActualPosDim2 + 1;
						break;
						case 4:
							if ( (ulActualPosDim1 <= 0) || (ulActualPosDim2 <= 0) ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1 - 1;
							actualPosition.y = ulActualPosDim2 - 1;
						break;
						case 5:
							if ( (ulActualPosDim1 <= 0) || (ulHeight <= ulActualPosDim2) ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1 - 1;
							actualPosition.y = ulActualPosDim2 + 1;
						break;
						case 6:
							if ( (ulWidth <= ulActualPosDim1) || (ulActualPosDim2 <= 0) ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1 + 1;
							actualPosition.y = ulActualPosDim2 - 1;
						break;
						case 7:
							if ( (ulWidth <= ulActualPosDim1) || (ulHeight <= ulActualPosDim2) ){
								continue;//no neighbour in direction
							}
							actualPosition.x = ulActualPosDim1 + 1;
							actualPosition.y = ulActualPosDim2 + 1;
						break;
						default:
							continue;//unknown neighbour -> switch it
					}
					//check if point was checked befor
					if ( ( setCheckedPoints.find( actualPosition ) == setCheckedPoints.end() ) &&
							( setPointsToCheck.find( actualPosition ) == setPointsToCheck.end() ) ){
						/*point not checked befor and not allready notified to check
						-> check if it has the correct properties*/
						
						//if the point is in the actual property set -> it has the correct properties
						const typeSetPoints::iterator itrActualPoint =
							setOfPoints.find( actualPosition );
						
						if ( itrActualPoint == setOfPoints.end() ){
							//no such point -> is neighbour point -> check next point
							setNeighbourPoints.insert( actualPosition );
							continue;
						}
						//add point to the area
						setPointsToCheck.insert( actualPosition );
						//actual point isn't needed anymore
						setOfPoints.erase( itrActualPoint );
					}//else the point is already in the area
				}
			}
			//store evalued area
			mapAreas[ actualProperty ].push_back( make_pair(
				setCheckedPoints, setNeighbourPoints ) );
		}
#ifdef DEBUG
		cout<<mapAreas[ actualProperty ].size()<<" created areas for color: "<<endl;
		itrProperty->first.storeXml( cout );
		cout<<endl<<flush;
#endif //DEBUG
	}
	
	//data don't needed anymore -> delete it
	mapPicturPointData.clear();

//combine areas with similar colors
	DEBUG_OUT_L2(<<"combine areas with similar colors"<<endl );
	//evalue the graph of areas and the area neighbours which can be combined
	typedef set< nConvertReduced::cAreaNeighbourNode< typeValue > * > typeSetAreas;
	typeSetAreas setAreas;
	//the mapping betwean the area nodes and the areas
	map< const nConvertReduced::cAreaNeighbourNode< typeValue > *,
		const typeSetPoints * > mapNeighbourAreas;
	
	//the mapping betwean the area nodes and the original areas (if needed)
	map< const nConvertReduced::cAreaNeighbourNode< typeValue > *,
		const typeSetPoints * > mapOriginalAreas;
	
	//the mapping betwean the points and area nodes
	map< typeDataPoint, nConvertReduced::cAreaNeighbourNode< typeValue > * > mapPointToAreas;
	
	DEBUG_OUT_L2(<<"creating area nodes"<<endl );
	for ( typeMapAreas::const_iterator
			itrActualPropertyAreas = mapAreas.begin();
			itrActualPropertyAreas != mapAreas.end(); itrActualPropertyAreas++ ){
		
		const list< pair< typeSetPoints, typeSetPoints > > & liActualAreas =
			itrActualPropertyAreas->second;
		const cVectorProperty & actualProperty = itrActualPropertyAreas->first;
		
		for ( list< pair< typeSetPoints, typeSetPoints > >::const_iterator
				itrArea = liActualAreas.begin();
				itrArea != liActualAreas.end(); itrArea++ ){
			
			const typeSetPoints & areaPoints = itrArea->first;
			const typeSetPoints & neighbourPoints = itrArea->second;
			
			nConvertReduced::cAreaNeighbourNode< typeValue > * pNewAreaNode = NULL;
			
			if ( bAddNeighbours ){
				//enlarge the area with its neighbours
				typeSetPoints areaPointsAndNeighbours = areaPoints;
				areaPointsAndNeighbours.insert( neighbourPoints.begin(),
					neighbourPoints.end() );
				
				pNewAreaNode = new nConvertReduced::cAreaNeighbourNode< typeValue >(
					areaPointsAndNeighbours, actualProperty,
					( areaPoints.size() <= ulMinPoints ) );
				
				mapOriginalAreas.insert( make_pair( pNewAreaNode, &(areaPoints) ) );
			}else{
				pNewAreaNode = new nConvertReduced::cAreaNeighbourNode< typeValue >(
					areaPoints, actualProperty, ( areaPoints.size() <= ulMinPoints ) );
			}
			setAreas.insert( pNewAreaNode );
			
			mapNeighbourAreas.insert( make_pair( pNewAreaNode, &(neighbourPoints) ) );
			//connect points with area node
			for ( typeSetPoints::const_iterator itrPoint = areaPoints.begin();
					itrPoint != areaPoints.end(); itrPoint++ ){
				
				mapPointToAreas[ *itrPoint ] = pNewAreaNode;
			}
		}
	}//create connections to neighbour areas
	
	DEBUG_OUT_L2(<<"connecting the "<<setAreas.size()<<" area nodes with ther neighbour areas"<<endl );
	for ( typeSetAreas::iterator itrArea = setAreas.begin();
			itrArea != setAreas.end(); itrArea++ ){
		
		DEBUG_OUT_L3(<<"creating connections for area "<<(*itrArea)<<endl );
		const typeSetPoints & setActualAreaNeighbours = *(mapNeighbourAreas[ *itrArea ]);
		//for all border points
		for ( typeSetPoints::iterator
				itrNeighbourPoint = setActualAreaNeighbours.begin();
				itrNeighbourPoint != setActualAreaNeighbours.end(); itrNeighbourPoint++ ){
			
			map< typeDataPoint, nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
					itrNeibourArea = mapPointToAreas.find( *itrNeighbourPoint );
			
			if ( itrNeibourArea != mapPointToAreas.end() ){
				(*itrArea)->addNeighbour( itrNeibourArea->second );
			}
		}//for all neighbour points
	}//for all areas
	//don't needed anymore -> delete it
	mapNeighbourAreas.clear();
	
	if ( bAddNeighbours ){
		DEBUG_OUT_L2(<<"remove not needed areas"<<endl );
		list< nConvertReduced::cAreaNeighbourNode< typeValue > * > liNotNeededAreas;
		
		//remove not needed neighbour points

		//area nodes changed in the last run
		set< nConvertReduced::cAreaNeighbourNode< typeValue > * > setChangedAreaNodes =
			setAreas;
		//points just in one area
		set< typeDataPoint > setSinglePoints;
		//while area nodes are changed
		while ( ! setChangedAreaNodes.empty() ){
			DEBUG_OUT_L2(<<"   to checked area nodes:"<<setChangedAreaNodes.size()<<endl );
			
			set< nConvertReduced::cAreaNeighbourNode< typeValue > * > setChangedAreaNodesNew;
			set< typeDataPoint > setCheckedPoint;
			/*map with the deletebel points of the areas:
				-key: area node wher the point can be deleted
				-value: list of deletebel points for the area
					-first: number of neighbours of the point in the area
					-second: the point to delete*/
			map< nConvertReduced::cAreaNeighbourNode< typeValue > *, list< pair< unsigned char, typeDataPoint > > >
				mapPointsDeletebel;
			
			//for every point in every changed area
			for ( set< nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
					itrArea = setChangedAreaNodes.begin();
					itrArea != setChangedAreaNodes.end(); itrArea++ ){
				
				const set< typeDataPoint > & setPointsOfArea = (*itrArea)->getPointsOfArea();
				for ( typeSetPoints::iterator itrPoint = setPointsOfArea.begin();
						itrPoint != setPointsOfArea.end(); itrPoint++ ){
					
					//check if the point is in more than one area
					if ( setSinglePoints.find( *itrPoint ) != setSinglePoints.end() ){
						//point is just in one area -> skip it
						continue;
					}
					//check if the actual point was checked befor
					if ( setCheckedPoint.find( *itrPoint ) != setCheckedPoint.end() ){
						//point was checked befor -> skip it
						continue;
					}
					setCheckedPoint.insert( *itrPoint );
					
					//evalue the number of neighbours of the point in every area
					/*the map with the area noods and the number neighbours in the area
						-key: a pointer to the area node
						-value: the number of neighbours the data point has in the area*/
					map< nConvertReduced::cAreaNeighbourNode< typeValue > *, unsigned char >
						mapPointNeighbourCounts;
					//point is in actual area
					mapPointNeighbourCounts[ *itrArea ] = 0;
					//evalue areas the point is in
					set< nConvertReduced::cAreaNeighbourNode< typeValue > * > & setNeighbourNodes =
						(*itrArea)->getNeighbourNodes();
					
					for ( set< nConvertReduced::cAreaNeighbourNode< typeValue > * >::const_iterator
							itrNeighbourArea = setNeighbourNodes.begin();
							itrNeighbourArea != setNeighbourNodes.end(); itrNeighbourArea++ ){
						
						const set< typeDataPoint > & setPointsOfNeighbourArea =
							(*itrNeighbourArea)->getPointsOfArea();
						
						if ( setPointsOfNeighbourArea.find( *itrPoint ) !=
								setPointsOfNeighbourArea.end() ){
							
							mapPointNeighbourCounts[ *itrNeighbourArea ] = 0;
						}
					}
					if ( mapPointNeighbourCounts.size() <= 1 ){
						//point is just in one area -> skip it and remember it
						setSinglePoints.insert( *itrPoint );
						//DEBUG_OUT_L4(<<"      single point ("<<itrPoint->x<<", "<<itrPoint->y<<") found"<<endl );
						continue;
					}//else point is in more than one area
					list< typeDataPoint > liNeibourPoints;
					//evalue the 8 neighbours of the point
					for ( unsigned int uiNeighbour = 0; uiNeighbour < 8; uiNeighbour++ ){
						
						typeDataPoint actualPosition = *itrPoint;
						switch ( uiNeighbour ){
							case 0:
								if ( actualPosition.x <= 0 ){
									continue;//no neighbour in direction
								}
								actualPosition.x--;
							break;
							case 1:
								if ( ulWidth <= actualPosition.x ){
									continue;//no neighbour in direction
								}
								actualPosition.x++;
							break;
							case 2:
								if ( actualPosition.y <= 0 ){
									continue;//no neighbour in direction
								}
								actualPosition.y--;
							break;
							case 3:
								if ( ulHeight <= actualPosition.y ){
									continue;//no neighbour in direction
								}
								actualPosition.y++;
							break;
							case 4:
								if ( (actualPosition.x <= 0) || (actualPosition.y <= 0) ){
									continue;//no neighbour in direction
								}
								actualPosition.x--;
								actualPosition.y--;
							break;
							case 5:
								if ( (actualPosition.x <= 0) || (ulHeight <= actualPosition.y) ){
									continue;//no neighbour in direction
								}
								actualPosition.x--;
								actualPosition.y++;
							break;
							case 6:
								if ( (ulWidth <= actualPosition.x) || (actualPosition.y <= 0) ){
									continue;//no neighbour in direction
								}
								actualPosition.x++;
								actualPosition.y--;
							break;
							case 7:
								if ( (ulWidth <= actualPosition.x) || (ulHeight <= actualPosition.y) ){
									continue;//no neighbour in direction
								}
								actualPosition.x++;
								actualPosition.y++;
							break;
							default:
								continue;//unknown neighbour -> switch it
						}
						liNeibourPoints.push_back( actualPosition );
					}//end evalue the 8 neighbours of the point
					//count the number of neighbours in the areas the point is in
					for ( map< nConvertReduced::cAreaNeighbourNode< typeValue > *, unsigned char >::iterator
							itrNeighbourArea = mapPointNeighbourCounts.begin();
							itrNeighbourArea != mapPointNeighbourCounts.end(); itrNeighbourArea++ ){
						
						const set< typeDataPoint > & setPointsOfNeighbourArea =
							itrNeighbourArea->first->getPointsOfArea();
						
						for ( list< typeDataPoint >::const_iterator
								itrNeighbourPoint = liNeibourPoints.begin();
								itrNeighbourPoint != liNeibourPoints.end(); itrNeighbourPoint++ ){
							
							if ( setPointsOfNeighbourArea.find( *itrNeighbourPoint ) !=
									setPointsOfNeighbourArea.end() ){
								//neighbour point is in this area
								itrNeighbourArea->second++;
							}
						}
					}
					
					//evalue the maximum number of neighbours
					unsigned char maxNeibours = 0;
					for ( map< nConvertReduced::cAreaNeighbourNode< typeValue > *, unsigned char >::const_iterator
							itrNeighbourArea = mapPointNeighbourCounts.begin();
							itrNeighbourArea != mapPointNeighbourCounts.end(); itrNeighbourArea++ ){
						
						if ( maxNeibours < itrNeighbourArea->second ){
							maxNeibours = itrNeighbourArea->second;
						}
					}
					/*remove the point from all areas, in which it has less than the
					maximum number of neighbours of the areas and less than 5 neighbours*/
					for ( map< nConvertReduced::cAreaNeighbourNode< typeValue > *, unsigned char >::iterator
							itrNeighbourArea = mapPointNeighbourCounts.begin();
							itrNeighbourArea != mapPointNeighbourCounts.end(); itrNeighbourArea++ ){
						
						const unsigned char neighbourPoints = itrNeighbourArea->second;
						if ( ( neighbourPoints <= 5 ) && ( neighbourPoints < maxNeibours ) ){
							
							//mark point as removebel
							//DEBUG_OUT_L4(<<"      mark point ("<<itrPoint->x<<", "<<itrPoint->y<<") from node "<<itrNeighbourArea->first<<" with "<<((int)neighbourPoints)<<" neigbours (maxNeibours="<<((int)maxNeibours)<<") as removebel"<<endl );
							mapPointsDeletebel[ itrNeighbourArea->first ].push_back( make_pair(
								neighbourPoints, *itrPoint ) );
						}
					}
					
				}//end for point of area
			}//end for changed area nodes
			
			
			//remove removebel point
			for (  map< nConvertReduced::cAreaNeighbourNode< typeValue > *,
					list< pair< unsigned char, typeDataPoint > > >::iterator
						itrNeighbourNode = mapPointsDeletebel.begin();
					itrNeighbourNode != mapPointsDeletebel.end(); itrNeighbourNode++ ){
				
				nConvertReduced::cAreaNeighbourNode< typeValue > * pNeighbourNode =
					itrNeighbourNode->first;
				const unsigned long ulPointsInArea =
					pNeighbourNode->getNumberOfAreaPoints();
				
				const typeSetPoints * pOriginalArea =
					mapOriginalAreas[ pNeighbourNode ];
				const unsigned long ulPointsInOriginalArea = pOriginalArea->size();
				
				if ( ( uiMinPointsForArea <= ulPointsInArea ) &&
						( ulPointsInArea <= (ulPointsInOriginalArea * 0.9) ) ){
					//don't remove any more points from the area
					continue;
				}
				
				list< pair< unsigned char, typeDataPoint > > &
					liDeletebelPoints = itrNeighbourNode->second;
				
				liDeletebelPoints.sort( nConvertReduced::sortNumberOrNeighbours< typeValue > );
				DEBUG_OUT_L3(<<"      "<<liDeletebelPoints.size()<<" deletebel points for node "<<pNeighbourNode<<endl );
				
				unsigned long ulPointToRemove =
					ulPointsInArea - (ulPointsInOriginalArea * 0.9);
				
				//try to remove points not in original area
				bool bPointsRemoved = false;
				for ( list< pair< unsigned char, typeDataPoint > >::iterator
						itrActualPoint = liDeletebelPoints.begin();
						( itrActualPoint != liDeletebelPoints.begin() ) &&
						( ulPointToRemove != 0 ); ){
					
					typeDataPoint & actualPoint = itrActualPoint->second;
					if ( pOriginalArea->find( actualPoint ) != pOriginalArea->end() ){
						//point in original area -> skip it
						itrActualPoint++;
						continue;
					}
					//DEBUG_OUT_L4(<<"      remove point ("<<actualPoint.x<<", "<<actualPoint.y<<") from node "<<pNeighbourNode<<" with "<<itrActualPoint->first<<" neigbours, wich was not in original area "<<endl );
					//remove point
					pNeighbourNode->removePoint( actualPoint, ulMinPoints );
					//remember changed areas
					setChangedAreaNodesNew.insert( pNeighbourNode );
					
					itrActualPoint = liDeletebelPoints.erase( itrActualPoint );
					ulPointToRemove--;
					bPointsRemoved = true;
				}
				if ( ( ulPointsInOriginalArea < uiMinPointsForArea ) || ( ! bPointsRemoved ) ){
					//protect points in big areas
					//remove remaining points
					while ( (ulPointToRemove != 0) && ( ! liDeletebelPoints.empty() ) ){
						
						//DEBUG_OUT_L4(<<"      remove point ("<<liDeletebelPoints.front().second.x<<", "<<liDeletebelPoints.front().second.y<<") from node "<<pNeighbourNode<<" with "<<((int)liDeletebelPoints.front().first)<<" neigbours, wich was in original area (points to remove:"<<ulPointToRemove<<")"<<endl );
						//remove point
						pNeighbourNode->removePoint( liDeletebelPoints.front().second, ulMinPoints );
						//remember changed areas
						setChangedAreaNodesNew.insert( pNeighbourNode );
						
						liDeletebelPoints.pop_front();
						ulPointToRemove--;
					}
				}
			}//for all neighbour nodes with removebel points
			
			
			setChangedAreaNodes = setChangedAreaNodesNew;
		}//end while area nodes are changed
		
		for ( typeSetAreas::iterator itrArea = setAreas.begin();
				itrArea != setAreas.end(); itrArea++ ){
			
			const bool bIsNotNeeded = (*itrArea)->removeIfNotNeeded();
			if ( bIsNotNeeded ){
				liNotNeededAreas.push_back( *itrArea );
			}
		}//for all areas
		for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
				itrAreaToRemove = liNotNeededAreas.begin();
				itrAreaToRemove != liNotNeededAreas.end();
				itrAreaToRemove++ ){
			
			setAreas.erase( *itrAreaToRemove );
			delete *itrAreaToRemove;
		}
	}//if add neighbours
	//don't needed anymore ->delete it
	mapOriginalAreas.clear();
	mapAreas.clear();
	
	
	if ( 0 < uiMinPointsNeighbourAreas ){
		DEBUG_OUT_L2(<<"subsume all areas with less than "<<uiMinPointsNeighbourAreas<<" points"<<endl );
		//subsume all areas with less than uiMinPointsNeighbourAreas
		list< nConvertReduced::cAreaNeighbourNode< typeValue > * > liChangedAreaNodes;
		
		for ( set< nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
				itrAreaNode = setAreas.begin();
				itrAreaNode != setAreas.end(); itrAreaNode++ ){
			
			if ( (*itrAreaNode)->getNumberOfAreaPoints() <= uiMinPointsNeighbourAreas ){
				//the area has less than uiMinPointsNeighbourAreas points itself ->skip it
				continue;
			}//else
			liChangedAreaNodes.push_back( *itrAreaNode );
		}
		
		while ( ! liChangedAreaNodes.empty() ){
			//sort liChangedAreaNodes bigges areas first
			liChangedAreaNodes.sort( nConvertReduced::higherPNeighboursPoints< typeValue > );
			
			list< nConvertReduced::cAreaNeighbourNode< typeValue > * > liChangedAreaNodesNew;
			
			while ( ! liChangedAreaNodes.empty() ){
				const set< nConvertReduced::cAreaNeighbourNode< typeValue > * > setRemovedAreaNodes =
					liChangedAreaNodes.front()->combineWithSmallNeighbours( uiMinPointsNeighbourAreas );
				
				if ( ! setRemovedAreaNodes.empty() ){
					//the area node was changed
					liChangedAreaNodesNew.push_back( liChangedAreaNodes.front() );
					
					for ( set< nConvertReduced::cAreaNeighbourNode< typeValue > * >::const_iterator
							itrRemovedArea = setRemovedAreaNodes.begin();
							itrRemovedArea != setRemovedAreaNodes.end(); itrRemovedArea++ ){
						
						delete (*itrRemovedArea);
						setAreas.erase( *itrRemovedArea );
					}
				}//end some neighbour nodes removed
				liChangedAreaNodes.pop_front();
			}//for all changed area nodes
			
			
			//TODO?? more iterations, like the parameter said
			//liChangedAreaNodes = liChangedAreaNodesNew;
			
			
		}//while neighbour nodes changed
	}//subsume all areas with less than uiMinPointsNeighbourAreas
	
	//reduce area neighbours to possible neighbours
	DEBUG_OUT_L2(<<"reduce area neighbours to possible neighbours"<<endl );
	for ( typeSetAreas::iterator itrArea = setAreas.begin();
			itrArea != setAreas.end(); itrArea++ ){
	
		(*itrArea)->reduceNeighbours( ulMaxAreaDiff, ulMaxDiff );
#ifdef DEBUG
		cout<<"reduced area:"<<endl;
		(*itrArea)->print( cout );
#endif //DEBUG
	}
	/*combine areas with the most points in the neighbourhood, till no area
	has points left in the combinebel neighbourhood*/
	DEBUG_OUT_L2(<<"searching for areas without neighbourhood"<<endl );
	//the areas wich cant be combined with any neighbour areas
	typeSetAreas setAreasWithoutNeighbourhood;
	for ( typeSetAreas::iterator itrArea = setAreas.begin();
			itrArea != setAreas.end(); itrArea++ ){
		
		if ( (*itrArea)->getNumberOfPointsInNeighbourhood() == 0 ){
			setAreasWithoutNeighbourhood.insert( *itrArea );
		}
	}
	for ( typeSetAreas::iterator itrArea = setAreasWithoutNeighbourhood.begin();
			itrArea != setAreasWithoutNeighbourhood.end(); itrArea++ ){
		setAreas.erase( *itrArea );
	}
	DEBUG_OUT_L2(<<"combine "<<setAreas.size()<<" areas with the most points in the neighbourhood ("<<setAreasWithoutNeighbourhood.size()<<" areas without neighbourhood)"<<endl );
	
	while ( ! setAreas.empty() ){
		
#ifdef FEATURE_N_CONVERT__SAVE_COMBINING_AREAS
		
		//find point with maximal number of neibour points
		nConvertReduced::cAreaNeighbourNode< typeValue > * pAreaWithMostPoints = NULL;
		unsigned long ulMaxNumberOfPoints = 0;
		for ( typeSetAreas::iterator itrArea = setAreas.begin();
				itrArea != setAreas.end(); itrArea++ ){
			
			if ( ulMaxNumberOfPoints < (*itrArea)->getNumberOfAreaPoints() ){
				//new area with maximal number of neibour points found
				ulMaxNumberOfPoints = (*itrArea)->getNumberOfAreaPoints();
				pAreaWithMostPoints = (*itrArea);
			}
		}
		if ( pAreaWithMostPoints == NULL ){
			//no area can be combined with an other area
			break;
		}
#ifdef DEBUG
		cout<<"combining area with neighbours (from "<<setAreas.size()<<" areas wich can be combined):"<<endl;
		pAreaWithMostPoints->print( cout );
#endif //DEBUG
		
		while ( pAreaWithMostPoints->getNumberOfPointsInNeighbourhood() != 0 ){
			//combine with all possible neighbour areas
			nConvertReduced::cAreaNeighbourNode< typeValue > * pCombinedWithNeighbourNode =
				pAreaWithMostPoints->combineWithBiggestNeighbourNode();
			
			DEBUG_OUT_L3(<<"area "<<pAreaWithMostPoints<<" combined with area "<<pCombinedWithNeighbourNode<<", which will be removed"<<endl );
			if ( pCombinedWithNeighbourNode == NULL ){
				break;//nothing combined
			}
			delete pCombinedWithNeighbourNode;
			setAreas.erase( pCombinedWithNeighbourNode );
		
			pAreaWithMostPoints->reduceNeighbours(
				ulMaxAreaDiff, ulMaxDiff );
		}//end while neighbourhood exists
		//no neighbours left
		setAreasWithoutNeighbourhood.insert( pAreaWithMostPoints );
		setAreas.erase( pAreaWithMostPoints );
#else //FEATURE_N_CONVERT__SAVE_COMBINING_AREAS
		//find point with maximal number of neibour points
		nConvertReduced::cAreaNeighbourNode< typeValue > * pAreaWithMostPointsInNeighbourhood = NULL;
		unsigned long ulMaxNeighbourhoodPoint = 0;
		for ( typeSetAreas::iterator itrArea = setAreas.begin();
				itrArea != setAreas.end(); itrArea++ ){
			
			if ( ulMaxNeighbourhoodPoint < (*itrArea)->getNumberOfPointsInNeighbourhood() ){
				//new area with maximal number of neibour points found
				ulMaxNeighbourhoodPoint = (*itrArea)->getNumberOfPointsInNeighbourhood();
				pAreaWithMostPointsInNeighbourhood = (*itrArea);
			}
		}
		if ( pAreaWithMostPointsInNeighbourhood == NULL ){
			//no area can be combined with an other area
			break;
		}
#ifdef DEBUG
		cout<<"combining area with neighbours (from "<<setAreas.size()<<" areas wich can be combined):"<<endl;
		pAreaWithMostPointsInNeighbourhood->print( cout );
#endif //DEBUG
		
		set< nConvertReduced::cAreaNeighbourNode< typeValue > * > setRemovedAreas =
			pAreaWithMostPointsInNeighbourhood->combineWithNeighbourNodes();
		
		pAreaWithMostPointsInNeighbourhood->reduceNeighbours(
			ulMaxAreaDiff, ulMaxDiff );
		
		for ( set< nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
				itrRemovedArea = setRemovedAreas.begin();
				itrRemovedArea != setRemovedAreas.end(); itrRemovedArea++ ){
			
			delete (*itrRemovedArea);
			setAreas.erase( (*itrRemovedArea) );
		}
		if ( pAreaWithMostPointsInNeighbourhood->getNumberOfPointsInNeighbourhood() == 0 ){
			//no neighbours left
			setAreasWithoutNeighbourhood.insert( pAreaWithMostPointsInNeighbourhood );
			setAreas.erase( pAreaWithMostPointsInNeighbourhood );
		}
#endif //FEATURE_N_CONVERT__SAVE_COMBINING_AREAS
	}
	setAreasWithoutNeighbourhood.insert( setAreas.begin(), setAreas.end() );
	setAreas.clear();
	
	//assign areas to properties
	DEBUG_OUT_L2(<<"assign areas to properties"<<endl );
	map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >
		mapPropertyAreaNodes;
	
	list< nConvertReduced::cAreaNeighbourNode< typeValue > * > removedAreaNodes;
	list< nConvertReduced::cAreaNeighbourNode< typeValue > * > newAreaNodes;
	
	for ( typeSetAreas::iterator itrArea = setAreasWithoutNeighbourhood.begin();
			itrArea != setAreasWithoutNeighbourhood.end(); itrArea++ ){
		
		const map< cVectorProperty, pair< unsigned long, bool> > mapCountsForProperty =
			(*itrArea)->getCountsForProperties();
		const set< typeDataPoint > & setPointsOfArea = (*itrArea)->getPointsOfArea();
		
		if ( ( setPointsOfArea.size() < uiMinPointsForArea ) &&
				( 1 < mapCountsForProperty.size() ) ){
			
			/*if area has less uiMinPointsForArea points with different color,
			create area for every point with its property*/
			removedAreaNodes.push_back( *itrArea );
			
			for ( typeSetPoints::iterator itrPoint = setPointsOfArea.begin();
					itrPoint != setPointsOfArea.end(); itrPoint++ ){
				
				const unsigned long ulX = itrPoint->x;
				const unsigned long ulY = itrPoint->y;
				
				//load property
				if ( colorPalette != NULL ){
					//till 8 bit
					bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
					
					if ( ulPaletteSize <= *indexValue ){
						continue;//skip pixel
					}
					*colorRGBValue = colorPalette[ *indexValue ];
				}else{
					//from 16 bit upwards
					bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
				}
				
				if ( bColor ){
					//set the property values
					if ( bSWColor ){
						vecProperty.setValue( 1, colorRGBValue->rgbRed );
					}else{
						vecProperty.setValue( 1, colorRGBValue->rgbRed );
						vecProperty.setValue( 2, colorRGBValue->rgbGreen );
						vecProperty.setValue( 3, colorRGBValue->rgbBlue );
					}
					
					set< typeDataPoint > setPointOfNewArea;
					setPointOfNewArea.insert( *itrPoint );
					
					nConvertReduced::cAreaNeighbourNode< typeValue > * pNewAreaNode =
						new nConvertReduced::cAreaNeighbourNode< typeValue >(
							setPointOfNewArea, vecProperty );
					
					newAreaNodes.push_back( pNewAreaNode );
					mapPropertyAreaNodes[ vecProperty ].push_back( pNewAreaNode );
				}
			}//end for points

		}else{//create area
			//TODO choos a property which is often used by all points
#ifdef DEBUG
			cout<<"choos a property which is often used by all points (#mapCountsForProperty="<<
				mapCountsForProperty.size()<<")"<<endl;
#endif //DEBUG
			
			const cVectorProperty * pMostCommonProperty = NULL;
			if ( mapCountsForProperty.size() != 1 ){
				
				map< cVectorProperty, unsigned long > mapWigthedCountsForProperty;
				//tranfer conts for colors
				for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
						itrPropertyCount = mapCountsForProperty.begin();
						itrPropertyCount != mapCountsForProperty.end();
						itrPropertyCount++ ){
					
					mapWigthedCountsForProperty.insert( pair< cVectorProperty, unsigned long >(
						itrPropertyCount->first, itrPropertyCount->second.first ) );
				}
				//add factors for neighbour colors
				const float fRegression = 1.0 - 1.0 / (float)ulMaxAreaDiff;
				for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
						itrPropertyCount1 = mapCountsForProperty.begin();
						itrPropertyCount1 != mapCountsForProperty.end();
						itrPropertyCount1++ ){
					for ( map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
							itrPropertyCount2 = mapCountsForProperty.begin();
							itrPropertyCount2 != mapCountsForProperty.end();
							itrPropertyCount2++ ){
						
						if ( itrPropertyCount1 == itrPropertyCount2 ){
							//same propertie -> was added allready -> skip
							continue;
						}
						const unsignedLongFib ulDistance = roundToLongFib( cVectorProperty::
							distanceOfProperty( itrPropertyCount1->first, itrPropertyCount2->first ) );
						
						mapWigthedCountsForProperty[ itrPropertyCount1->first ] +=
							( mapCountsForProperty.find( itrPropertyCount2->first )->second.first *
								pow( fRegression, ulDistance ) );
					}
				}
#ifdef DEBUG
				for ( map< cVectorProperty, unsigned long >::const_iterator
						itrPointCount = mapWigthedCountsForProperty.begin();
						itrPointCount != mapWigthedCountsForProperty.end(); itrPointCount++ ){
					
					cout<<"value "<<itrPointCount->second<<" for points, which have the property :"<<endl;
					itrPointCount->first.storeXml( cout );
				}
#endif //DEBUG
				//find the property with the maximum value
				map< cVectorProperty, pair< unsigned long, bool > >::const_iterator
					itrCountForProperty = mapCountsForProperty.begin();
				map< cVectorProperty, unsigned long >::const_iterator
					itrPropertyValue = mapWigthedCountsForProperty.begin();
				
				unsigned long ulMaxValue = itrPropertyValue->second;
				pMostCommonProperty = &(itrCountForProperty->first);
				
				itrCountForProperty++;
				itrPropertyValue++;
				
				for ( ; itrPropertyValue != mapWigthedCountsForProperty.end();
						itrPropertyValue++, itrCountForProperty++ ){
					
					if ( ulMaxValue < itrPropertyValue->second ){
						ulMaxValue = itrPropertyValue->second;
						pMostCommonProperty = &(itrCountForProperty->first);
					}
				}
			}else{//yust one propert -> take it as the property for the area
#ifdef DEBUG
				cout<<"yust one propert -> take it as the property for the area"<<endl;
#endif //DEBUG
				pMostCommonProperty = &(mapCountsForProperty.begin()->first);
			}
#ifdef DEBUG
			cout<<"area ("<<(*itrArea)<<") has property ("<<pMostCommonProperty<<") :"<<endl;
			pMostCommonProperty->storeXml( cout );
#endif //DEBUG
			mapPropertyAreaNodes[ *pMostCommonProperty ].push_back( *itrArea );
		}//create area or single points
	}//end for setAreasWithoutNeighbourhood
	
	for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
			itrRemovedArea = removedAreaNodes.begin();
			itrRemovedArea != removedAreaNodes.end(); itrRemovedArea++ ){
		
		nConvertReduced::cAreaNeighbourNode< typeValue > * pRemovedArea = *itrRemovedArea;
		setAreasWithoutNeighbourhood.erase( pRemovedArea );
		delete pRemovedArea;
	}
	setAreasWithoutNeighbourhood.insert( newAreaNodes.begin(), newAreaNodes.end() );
	
	
	if ( ( bCreatebackground ) && ( ! multimediaObject.hasFileBkColor() ) ){
		//set a background color, if non is given
		DEBUG_OUT_L1(<<endl<<"evalue a background color of "<<mapPropertyAreaNodes.size()<<" colors"<<endl );
		
		/*if a background property should be created, this map contains the
		area fib-objects for the different properties*/
		map< cVectorProperty, unsignedLongFib > mapAreasPerProperty;
		/*if a background property should be created, this map contains the
		single point fib-objects for the different properties*/
		map< cVectorProperty, unsignedLongFib > mapSinglePointsPerProperty;
		
		for ( map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >::const_reverse_iterator
				itrPropertAreas = mapPropertyAreaNodes.rbegin();
				itrPropertAreas != mapPropertyAreaNodes.rend(); itrPropertAreas++ ){
			
			if ( itrPropertAreas->second.empty() ){
				//no areas for property to consider -> skip property
				continue;
			}
#ifdef DEBUG
			cout<<"evaluing if property is good background color:"<<endl;
			itrPropertAreas->first.storeXml( cout );
#endif //DEBUG
			const cVectorProperty & actualProperty = itrPropertAreas->first;
			const list< nConvertReduced::cAreaNeighbourNode< typeValue > * > & liActualAreas =
				itrPropertAreas->second;
			
			//find max area difference properties and max single point difference properties for background
			set< const cVectorProperty * > setActualMaxAreaDiffProperties;
			set< const cVectorProperty * > setActualMaxPointDiffProperties;
			//evalue diff to all other properties
			for ( map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >::iterator
					itrPropertyCompare = mapPropertyAreaNodes.begin();
					itrPropertyCompare != mapPropertyAreaNodes.end(); itrPropertyCompare++ ){
				
				const cVectorProperty & toCompareWithProperty = itrPropertyCompare->first;
				
				const unsignedLongFib ulDistance = roundToLongFib( cVectorProperty::
					distanceOfProperty( actualProperty, toCompareWithProperty ) );
				
				if ( ulDistance <= ulMaxDiff ){
					//this property has to the actual property an difference lower ulMaxDiff
					setActualMaxPointDiffProperties.insert( &toCompareWithProperty );
				}
				if ( ulDistance <= ulMaxAreaDiff ){
					//this property has to the actual property an difference lower ulMaxAreaDiff
					setActualMaxAreaDiffProperties.insert( &toCompareWithProperty );
				}
			}
			
			for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::const_iterator
					itrArea = liActualAreas.begin();
					itrArea != liActualAreas.end(); itrArea++ ){
				
				const set< typeDataPoint > & setPointsOfArea = (*itrArea)->getPointsOfArea();
		
				//add counts for the background
				if ( setPointsOfArea.size() < uiMinPointsForArea ){
					//add single points count
					for ( set< const cVectorProperty * >::iterator
							itrSameSinglePointProperties = setActualMaxPointDiffProperties.begin();
							itrSameSinglePointProperties != setActualMaxPointDiffProperties.end();
							itrSameSinglePointProperties++ ){
					
						mapSinglePointsPerProperty[ **itrSameSinglePointProperties ] += setPointsOfArea.size();
					}
				}else{
					//add an area count
					for ( set< const cVectorProperty * >::iterator
							itrSameAreaProperties = setActualMaxAreaDiffProperties.begin();
							itrSameAreaProperties != setActualMaxAreaDiffProperties.end();
							itrSameAreaProperties++ ){
					
						mapAreasPerProperty[ **itrSameAreaProperties ]++;
					}
				}
			}//end for all areas
		}//end for all properties
		
		//search for the propertie which uses the most bits
		const cVectorProperty * pPropertyUsesMostSpace;
		unsignedLongFib ulMaxSize = 0;
		for ( map< cVectorProperty, unsignedLongFib >::iterator
				itrProperty = mapAreasPerProperty.begin();
				itrProperty != mapAreasPerProperty.end(); itrProperty++ ){
			
			const unsignedLongFib actualSize =
				itrProperty->second * MIN_POINTS_FOR_AREA +
				mapSinglePointsPerProperty[ itrProperty->first ];
			
			if ( ulMaxSize < actualSize ){
				//actual property uses most bits till now
				pPropertyUsesMostSpace = &(itrProperty->first);
				ulMaxSize = actualSize;
			}
		}
#ifdef DEBUG
		cout<<"the founded background color with the biggest size (="<<ulMaxSize<<
			") is:"<<endl;
		pPropertyUsesMostSpace->storeXml( cout );
#endif //DEBUG
		
		//add new background property
		DEBUG_OUT_L2(<<"adding background property"<<endl );
		cVectorPosition vecPositionBackground( 0 );
		cPoint * pBackgroundPoint = new cPoint( &vecPositionBackground );
		pBackgroundProperty = new cProperty( *pPropertyUsesMostSpace, pBackgroundPoint );
		liUnderobjects.push_back( pBackgroundProperty );
	}//add background
	
	//points with this color dosn't needs to be included, because ther are background
	//TODO don't add points with this property
	set< cVectorProperty > setBackgroundPointProperties;
	if ( pBackgroundProperty ){
		//removing areas for the background property
		const cVectorProperty * pVecBackgroundProperty =
			pBackgroundProperty->getProperty();
		//remove areas for property, for the background
		mapPropertyAreaNodes.erase( * pVecBackgroundProperty );
		
		//find max area difference properties and max single point difference properties for background
		set< cVectorProperty > setPropertiesToDelete;
		//remove all areas which can be subsumed by the background
		for ( map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >::iterator
				itrPropertyCompare = mapPropertyAreaNodes.begin();
				itrPropertyCompare != mapPropertyAreaNodes.end(); itrPropertyCompare++ ){
			
			const cVectorProperty & toCompareWithProperty = itrPropertyCompare->first;
			
			const unsignedLongFib ulDistance = roundToLongFib( cVectorProperty::
				distanceOfProperty( *pVecBackgroundProperty, toCompareWithProperty ) );
			
			if ( ulDistance <= ulMaxAreaDiff ){
				//this property has to the actual property an difference lower ulMaxAreaDiff
#ifdef DEBUG
				cout<<"mark to erase all "<<mapPropertyAreaNodes[ toCompareWithProperty ].size()<<" areas with property:"<<endl;
				toCompareWithProperty.storeXml( cout );
#endif //DEBUG
				setPropertiesToDelete.insert( toCompareWithProperty );
				
			}else if ( ulDistance <= ulMaxDiff ){
				//this property has to the actual property an difference lower ulMaxDiff
				setBackgroundPointProperties.insert( toCompareWithProperty );
				
				list< nConvertReduced::cAreaNeighbourNode< typeValue > * > & liActualAreas =
					itrPropertyCompare->second;
				
				for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::iterator
						itrActualArea = liActualAreas.begin();
						itrActualArea != liActualAreas.end(); ){
					
					if ( (*itrActualArea)->getNumberOfAreaPoints() <= ulMinPoints ){
						DEBUG_OUT_L4(<<"erasing area "<<(*itrActualArea)<<endl);
						itrActualArea = liActualAreas.erase( itrActualArea );
					}else{
						itrActualArea++;
					}
				}
				if ( liActualAreas.empty() ){
					//no areas left -> erase property
					setPropertiesToDelete.insert( toCompareWithProperty );
				}
			}
		}
		//erasing areas near the background property
		for ( set< cVectorProperty >::iterator
				itrToDeleteProperty = setPropertiesToDelete.begin();
				itrToDeleteProperty != setPropertiesToDelete.end();
				itrToDeleteProperty++ ){
		
#ifdef DEBUG
			cout<<"erasing all "<<mapPropertyAreaNodes[ *itrToDeleteProperty ].size()<<" areas with property:"<<endl;
			itrToDeleteProperty->storeXml( cout );
#endif //DEBUG
			mapPropertyAreaNodes.erase( *itrToDeleteProperty );
		}
	}
	
	//create dimension domain
	cDomainNaturalNumber domainWidth( ulWidth );
	cDomainNaturalNumber domainHeight( ulHeight );
	cTypeDimension typeDimension( 2 );
	vector<cDomainSingle*> vecDomainsDimension;
	vecDomainsDimension.push_back( &domainWidth );
	vecDomainsDimension.push_back( &domainHeight );
	cDomainVector vectorDomainDimension( vecDomainsDimension );
	
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
	//sort area nodes into ther size classes
	map< int, map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > > >
		mapSizeClassPropertyAreaNodes;
	for ( map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >::const_reverse_iterator
			itrPropertAreas = mapPropertyAreaNodes.rbegin();
			itrPropertAreas != mapPropertyAreaNodes.rend(); itrPropertAreas++ ){
		
		const cVectorProperty & actualProperty = itrPropertAreas->first;
		const list< nConvertReduced::cAreaNeighbourNode< typeValue > * > &
			liActualAreas = itrPropertAreas->second;
		
		for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::const_iterator
				itrArea = liActualAreas.begin();
				itrArea != liActualAreas.end(); itrArea++ ){
			//add area node to its class and property
			unsigned long ulPointsInArea = (*itrArea)->getNumberOfAreaPoints();
			
			if ( (ulPointsInArea < uiMinPointsForArea) ||
					(ulPointsInArea <= 1 ) ){
				//they will be added as single points
				mapSizeClassPropertyAreaNodes[ -1 ][ actualProperty ].push_back( *itrArea );
				
			}else{//an area object will be created for the area node
				const int iClass = log( ulPointsInArea ) / FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP;
				
				mapSizeClassPropertyAreaNodes[ iClass ][ actualProperty ].push_back( *itrArea );
			}
		}//end for every area node for the property
	}//end for every property
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
	
	
	//create fib-objects for the areas
	DEBUG_OUT_L2(<<"create fib-objects for the remaining "<<setAreasWithoutNeighbourhood.size()<<" areas"<<endl );
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
	//the map with the fib-objects for the different properties
	map< int, map< cVectorProperty, list< cFibElement * > > > mapSizeClassPropertyFibObjects;
	//maximal area which an new area can occupy
	set< typeDataPoint > setOverlapedPoints;
	//points which are in the areas to create but not in the created area object
	set< typeDataPoint > setMissingPoints;
	
	const double MAX_VALUE_FOR_CREATE_AREA = ((double)(std::max( ulWidth, ulHeight ))) *
		((double)(128));
	
	for ( map< int, map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > > >::const_iterator
			itrPropertAreas = mapSizeClassPropertyAreaNodes.begin();
			itrPropertAreas != mapSizeClassPropertyAreaNodes.end(); itrPropertAreas++ ){
		
		const map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > > &
			mapLayerPropertyAreaNodes = itrPropertAreas->second;
		const int & iActualLayer = itrPropertAreas->first;
		
		for ( map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >::const_reverse_iterator
				itrPropertAreas = mapLayerPropertyAreaNodes.rbegin();
				itrPropertAreas != mapLayerPropertyAreaNodes.rend(); itrPropertAreas++ ){
			
			const cVectorProperty & actualProperty = itrPropertAreas->first;
			const list< nConvertReduced::cAreaNeighbourNode< typeValue > * > & liActualAreas =
				itrPropertAreas->second;
#ifdef DEBUG
			cout<<endl<<"creating size layer "<<iActualLayer<<" fib-object(s) for the property:"<<endl;
			actualProperty.storeXml( cout );
#endif //DEBUG
			
			for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::const_iterator
					itrArea = liActualAreas.begin();
					itrArea != liActualAreas.end(); itrArea++ ){
				
				const set< typeDataPoint > & setPointsOfArea = (*itrArea)->getPointsOfArea();
				
				setOverlapedPoints.insert( setPointsOfArea.begin(), setPointsOfArea.end() );
#ifdef DEBUG
				cout<<endl<<"creating fib-object(s) for an area:"<<endl;
				(*itrArea)->print( cout );
#endif //DEBUG
				bool bStorePoints = false;
				if ( setPointsOfArea.size() < uiMinPointsForArea ){
					/*if area has less than tree points
					-> don't create an area object and add the points directly*/
					DEBUG_OUT_L2(<<"less than "<<uiMinPointsForArea<<" ("<<setPointsOfArea.size()<< ") points in area -> store points directly"<<endl<<flush);
					bStorePoints = true;
					
				}else{//create area object for point area
#ifndef N_CONVERT_TO_FIB_NO_AREAS
					cFibVariable * pVariableX = new cFibVariable( NULL );
					cFibVariable * pVariableY = new cFibVariable( NULL );
					cVectorPosition vecPositionVariable( 2 );
					vecPositionVariable.setVariable( 1, pVariableX );
					vecPositionVariable.setVariable( 2, pVariableY );
					
					cPoint * pNewPoint = new cPoint( & vecPositionVariable );
					
					set< typeDataPoint > setActualMissingPoints;
					
#ifdef FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
					DEBUG_OUT_L2(<<"createNSplineBorderAreasForPoints( #setPointsOfArea="<<setPointsOfArea.size()<<", #setOverlapedPoints="<<setOverlapedPoints.size()<<" )"<<endl<<flush);
					cFibElement * pAreaFibObject = nD2::createNSplineBorderAreasForPoints< typeValue >(
						setPointsOfArea, setOverlapedPoints, pNewPoint, pVariableX, pVariableY, 4,
						& setActualMissingPoints, 1, MAX_VALUE_FOR_CREATE_AREA, maxError );
#else //FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
					DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints( #setPointsOfArea="<<setPointsOfArea.size()<<", #setOverlapedPoints="<<setOverlapedPoints.size()<<" )"<<endl<<flush);
					cFibElement * pAreaFibObject = nD2::createSplineItrFastBorderAreasForPoints< typeValue >(
						setPointsOfArea, setOverlapedPoints, pNewPoint, pVariableX, pVariableY, 4,
						& setActualMissingPoints, 1, MAX_VALUE_FOR_CREATE_AREA, maxError );
#endif //FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
					
					DEBUG_OUT_L3(<<"points missing in area: "<<setActualMissingPoints.size()<<endl<<flush);
					
					if ( bCorrectMissingPoints ){
						
						setMissingPoints.insert( setActualMissingPoints.begin(), setActualMissingPoints.end() );
						/*don't need to correct overlaped points, becaus the
						missing points will be added overlapping all later*/
					}else{//correct overlaped points
						for ( set< typeDataPoint >::const_iterator
								itrMissingPoint = setActualMissingPoints.begin();
								itrMissingPoint != setActualMissingPoints.end(); itrMissingPoint++ ){
							
							setOverlapedPoints.erase( *itrMissingPoint );
						}
					}
					
					delete pVariableX;
					delete pVariableY;
					if ( pAreaFibObject ){
						//add fib-object
						mapSizeClassPropertyFibObjects[iActualLayer][ actualProperty ].push_front( pAreaFibObject );
						
					}else{
						DEBUG_OUT_EL2(<<"Error: Area creation function returned NULL ."<<endl<<flush);
						pNewPoint->deleteObject();
						//add points
						bStorePoints = true;
					}
#endif //N_CONVERT_TO_FIB_NO_AREAS
				}//end create area object for point area
#ifndef N_CONVERT_TO_FIB_NO_POINTS
				if ( bStorePoints ){
					//store points seperatly
					DEBUG_OUT_L2(<<"Store "<<setPointsOfArea.size()<<" single points seperatly"<<endl<<flush);
					cVectorPosition vecPosition( 2 );
						
					for ( typeSetPoints::iterator itrPoint = setPointsOfArea.begin();
							itrPoint != setPointsOfArea.end(); itrPoint++ ){
						
						vecPosition.setValue( 1, itrPoint->x );
						vecPosition.setValue( 2, itrPoint->y );
						cPoint * pPoint = new cPoint( &vecPosition );
						//add points to size layer -1 (they overlap all)
						mapSizeClassPropertyFibObjects[ -1 ][ actualProperty ].push_front( pPoint );
					}
				}//end if bStorePoints
#endif //N_CONVERT_TO_FIB_NO_POINTS
			}//end for all area nodes for the property
		}//end for all properties
	}//end for all size layers
	
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP

	//the map with the fib-objects for the different properties
	map< cVectorProperty, list< cFibElement * > > mapPropertyFibObjects;
	//maximal area which an new area can occupy
	set< typeDataPoint > setOverlapedPoints;
	//points which are in the areas to create but not in the created area object
	set< typeDataPoint > setMissingPoints;
	
	const double MAX_VALUE_FOR_CREATE_AREA = ((double)(std::max( ulWidth, ulHeight ))) *
		((double)(128));

	for ( map< cVectorProperty, list< nConvertReduced::cAreaNeighbourNode< typeValue > * > >::const_reverse_iterator
			itrPropertAreas = mapPropertyAreaNodes.rbegin();
			itrPropertAreas != mapPropertyAreaNodes.rend(); itrPropertAreas++ ){
		
		const cVectorProperty & actualProperty = itrPropertAreas->first;
		const list< nConvertReduced::cAreaNeighbourNode< typeValue > * > & liActualAreas =
			itrPropertAreas->second;
#ifdef DEBUG
		cout<<endl<<"creating fib-object(s) for the property:"<<endl;
		actualProperty.storeXml( cout );
#endif //DEBUG
		
		for ( list< nConvertReduced::cAreaNeighbourNode< typeValue > * >::const_iterator
				itrArea = liActualAreas.begin();
				itrArea != liActualAreas.end(); itrArea++ ){
			
			const set< typeDataPoint > & setPointsOfArea = (*itrArea)->getPointsOfArea();
			
			setOverlapedPoints.insert( setPointsOfArea.begin(), setPointsOfArea.end() );
#ifdef DEBUG
			cout<<endl<<"creating fib-object(s) for an area:"<<endl;
			(*itrArea)->print( cout );
#endif //DEBUG
		
			bool bStorePoints = false;
			if ( setPointsOfArea.size() < uiMinPointsForArea ){
				/*if area has less than tree points
				-> don't create an area object and add the points directly*/
				DEBUG_OUT_L2(<<"less than "<<uiMinPointsForArea<<" ("<<setPointsOfArea.size()<< ") points in area -> store points directly"<<endl<<flush);
				bStorePoints = true;
				
			}else{//create area object for point area
#ifndef N_CONVERT_TO_FIB_NO_AREAS
				cFibVariable * pVariableX = new cFibVariable( NULL );
				cFibVariable * pVariableY = new cFibVariable( NULL );
				cVectorPosition vecPositionVariable( 2 );
				vecPositionVariable.setVariable( 1, pVariableX );
				vecPositionVariable.setVariable( 2, pVariableY );
				
				cPoint * pNewPoint = new cPoint( & vecPositionVariable );
				
				set< typeDataPoint > setActualMissingPoints;
				
#ifdef FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
				DEBUG_OUT_L2(<<"createNSplineBorderAreasForPoints( #setPointsOfArea="<<setPointsOfArea.size()<<", #setOverlapedPoints="<<setOverlapedPoints.size()<<" )"<<endl<<flush);
				cFibElement * pAreaFibObject = nD2::createNSplineBorderAreasForPoints< typeValue >(
					setPointsOfArea, setOverlapedPoints, pNewPoint, pVariableX, pVariableY, 4,
					& setActualMissingPoints, 1, MAX_VALUE_FOR_CREATE_AREA, maxError );
#else //FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
				DEBUG_OUT_L2(<<"createSplineItrFastBorderAreasForPoints( #setPointsOfArea="<<setPointsOfArea.size()<<", #setOverlapedPoints="<<setOverlapedPoints.size()<<" )"<<endl<<flush);
				cFibElement * pAreaFibObject = nD2::createSplineItrFastBorderAreasForPoints< typeValue >(
					setPointsOfArea, setOverlapedPoints, pNewPoint, pVariableX, pVariableY, 4,
					& setActualMissingPoints, 1, MAX_VALUE_FOR_CREATE_AREA, maxError );
#endif //FEATURE_CONVERT_TO_FIB_AREA_GENERATOR
				
				DEBUG_OUT_L3(<<"points missing in area: "<<setActualMissingPoints.size()<<endl<<flush);
				//correct overlaped points
				for ( set< typeDataPoint >::const_iterator
						itrMissingPoint = setActualMissingPoints.begin();
						itrMissingPoint != setActualMissingPoints.end(); itrMissingPoint++ ){
					
					setOverlapedPoints.erase( *itrMissingPoint );
				}
				
				if ( bCorrectMissingPoints ){
					setMissingPoints.insert( setActualMissingPoints.begin(), setActualMissingPoints.end() );
				}
				
				delete pVariableX;
				delete pVariableY;
				if ( pAreaFibObject ){
					//add fib-object
					mapPropertyFibObjects[ actualProperty ].push_front( pAreaFibObject );
					
				}else{
					DEBUG_OUT_EL2(<<"Error: Area creation function returned NULL."<<endl<<flush);
					pNewPoint->deleteObject();
					//add points
					bStorePoints = true;
				}
#endif //N_CONVERT_TO_FIB_NO_AREAS
			}//end create area object for point area
#ifndef N_CONVERT_TO_FIB_NO_POINTS
			if ( bStorePoints ){
				//store points seperatly
				DEBUG_OUT_L2(<<"Store "<<setPointsOfArea.size()<<" single points seperatly"<<endl<<flush);
				cVectorPosition vecPosition( 2 );
					
				for ( typeSetPoints::iterator itrPoint = setPointsOfArea.begin();
						itrPoint != setPointsOfArea.end(); itrPoint++ ){
					
					vecPosition.setValue( 1, itrPoint->x );
					vecPosition.setValue( 2, itrPoint->y );
					cPoint * pPoint = new cPoint( &vecPosition );
					
					mapPropertyFibObjects[ actualProperty ].push_front( pPoint );
				}
			}//end if bStorePoints
#endif //N_CONVERT_TO_FIB_NO_POINTS
		}//end for all area nodes for the property
	}//end for all properties
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
	
	//delete setAreas
	DEBUG_OUT_L2(<<"delete area nodes"<<endl );
	for ( typeSetAreas::iterator itrArea = setAreasWithoutNeighbourhood.begin();
			itrArea != setAreasWithoutNeighbourhood.end(); itrArea++ ){
	
		delete (*itrArea);
	}
	setAreasWithoutNeighbourhood.clear();
	
	if ( bCorrectMissingPoints ){
		DEBUG_OUT_L2(<<"correct "<<setMissingPoints.size()<<" points, wich are missing in the created area fib-objects"<<endl );
		cVectorPosition vecPosition( 2 );
		for ( typeSetPoints::iterator itrPoint = setMissingPoints.begin();
				itrPoint != setMissingPoints.end(); itrPoint++ ){
			
			const unsigned long ulX = itrPoint->x;
			const unsigned long ulY = itrPoint->y;
			//load property
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue = colorPalette[ *indexValue ];
			}else{
				//from 16 bit upwards
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
			}
			
			if ( bColor ){
				//set the property values
				if ( bSWColor ){
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
				}else{
					vecProperty.setValue( 1, colorRGBValue->rgbRed );
					vecProperty.setValue( 2, colorRGBValue->rgbGreen );
					vecProperty.setValue( 3, colorRGBValue->rgbBlue );
				}
				
				set< typeDataPoint > setPointOfNewArea;
				setPointOfNewArea.insert( *itrPoint );
				
				vecPosition.setValue( 1, ulX );
				vecPosition.setValue( 2, ulY );
				cPoint * pPoint = new cPoint( &vecPosition );
#ifdef DEBUG
				cout<<"add point ("<<ulX<<", "<<ulY<<") missing in created area object"<<endl;
				vecProperty.storeXml( cout );
#endif //DEBUG

#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
				//add points to size layer -1
				mapSizeClassPropertyFibObjects[ -1 ][ vecProperty ].push_back( pPoint );
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
				mapPropertyFibObjects[ vecProperty ].push_back( pPoint );
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
			}
		}//end for missing points
	}
	
	//correct wrong points
	if ( bCorrectPoints ){
		DEBUG_OUT_L2(<<endl<<"correcting wrong points"<<endl );
		//compare with background color
		bool matrixCorrectPoints[ ulWidth ][ ulHeight ];
		
		if ( pBackgroundProperty ){
			DEBUG_OUT_L2(<<"evaluing if background is correct "<<endl );
			
			const cVectorProperty & vecBgProperty =
				*(pBackgroundProperty->getProperty());
			for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
				for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
					//evalue the color of the point
					
					if ( colorPalette != NULL ){
						//till 8 bit
						bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
						
						if ( ulPaletteSize <= *indexValue ){
							continue;//skip pixel
						}
						*colorRGBValue = colorPalette[ *indexValue ];
					}else{
						//from 16 bit upwards
						bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
					}
					
					if ( bColor ){
						//set the property values
						if ( bSWColor ){
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
						}else{
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
							vecProperty.setValue( 2, colorRGBValue->rgbGreen );
							vecProperty.setValue( 3, colorRGBValue->rgbBlue );
						}
					}
					//compare with background color
					const unsignedLongFib ulDistance = roundToLongFib( cVectorProperty::
						distanceOfProperty( vecBgProperty, vecProperty ) );
					if ( ulDistance <= ulMaxDiff ){
						//correct point
						matrixCorrectPoints[ ulX ][ ulY ] = true;
					}else{//not correct point
						matrixCorrectPoints[ ulX ][ ulY ] = false;
					}
				}
			}
		}else{//no background property
			DEBUG_OUT_L2(<<"set all points to wrong "<<endl );
			for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
				for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
					//evalue the color of the point
					matrixCorrectPoints[ ulX ][ ulY ] = false;
				}
			}
		}
		//compare with points
		const unsignedLongFib ulNumberOfPoints = ulWidth * ulHeight;
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		for ( map< int, map< cVectorProperty, list< cFibElement * > > >::reverse_iterator
				itrPropertAreas = mapSizeClassPropertyFibObjects.rbegin();
				itrPropertAreas != mapSizeClassPropertyFibObjects.rend(); itrPropertAreas++ ){
			
		map< cVectorProperty, list< cFibElement * > > &
			mapLayerPropertyFibObjects = itrPropertAreas->second;
				
		for ( map< cVectorProperty, list< cFibElement * > >::iterator
				itrPropertyObjects = mapLayerPropertyFibObjects.begin();
				itrPropertyObjects != mapLayerPropertyFibObjects.end(); itrPropertyObjects++ ){
		
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		for ( map< cVectorProperty, list< cFibElement * > >::iterator
				itrPropertyObjects = mapPropertyFibObjects.begin();
				itrPropertyObjects != mapPropertyFibObjects.end(); itrPropertyObjects++ ){
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
			
			const cVectorProperty & vecActualProperty = itrPropertyObjects->first;
			list< cFibElement * > & liPropertyFibObjects = itrPropertyObjects->second;
#ifdef DEBUG
			cout<<"evaluing error points for property:"<<endl;
			vecActualProperty.storeXml( cout );
#endif //DEBUG
			
			for ( list< cFibElement* >::iterator itrUnderobject = liPropertyFibObjects.begin();
					itrUnderobject != liPropertyFibObjects.end(); itrUnderobject++ ){
				
				//evalue the underobject
				cEvaluePositionListLimit evaluedPositionData( ulNumberOfPoints * 2,
					& vectorDomainDimension, true, 0, ulNumberOfPoints * 64 );
				
				//discard the property element
				const cFibElement * pFibObjectToEvalue = (*itrUnderobject);
				
				const bool bObjectEvalued = pFibObjectToEvalue->evalueObjectSimple(
					evaluedPositionData );
				if ( ! bObjectEvalued ){
					DEBUG_OUT_EL1( <<"Error: The fib -object couldn't be evalued."<<endl );
					continue;
				}
				
				const list< pair< cVectorPosition, list< cVectorProperty > > > &
					liPoints = evaluedPositionData.liEvaluedPositionData;
				//compare evalued points with the picture
				for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
						itrActualPoint = liPoints.begin();
						itrActualPoint != liPoints.end(); itrActualPoint++ ){
					
					const cVectorPosition & position = itrActualPoint->first;
					const unsigned long ulX = roundToLongFib( position.getValue( 1 ) );
					const unsigned long ulY = roundToLongFib( position.getValue( 2 ) );
						
					if ( colorPalette != NULL ){
						//till 8 bit
						bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
						
						if ( ulPaletteSize <= *indexValue ){
							continue;//skip pixel
						}
						*colorRGBValue = colorPalette[ *indexValue ];
					}else{
						//from 16 bit upwards
						bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
					}
					
					if ( bColor ){
						//set the property values
						if ( bSWColor ){
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
						}else{
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
							vecProperty.setValue( 2, colorRGBValue->rgbGreen );
							vecProperty.setValue( 3, colorRGBValue->rgbBlue );
						}
					}
					//compare with background color
					const unsignedLongFib ulDistance = roundToLongFib( cVectorProperty::
						distanceOfProperty( vecActualProperty, vecProperty ) );
					if ( ulDistance <= ulMaxDiff ){
						//correct point
						matrixCorrectPoints[ ulX ][ ulY ] = true;
					}else{//not correct point
#ifdef DEBUG
						//cout<<"founded wrong point ("<<ulX<<", "<<ulY<<") with error "<<ulDistance<<", but should be maximal "<<ulMaxDiff<<endl;
#endif //DEBUG
						matrixCorrectPoints[ ulX ][ ulY ] = false;
					}
				}
			}
			
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		}}//end for mapSizeClassPropertyFibObjects
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		}//end for mapPropertyFibObjects
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP

#ifdef DEBUG_N_CONVERT_TO_FIB__JUST_CORRECTED_WRONG_POINTS
		//just output the corrected points
		mapPropertyFibObjects.clear();
		liUnderobjects.clear();
#endif //DEBUG_N_CONVERT_TO_FIB__JUST_CORRECTED_WRONG_POINTS
		//add wrong points
		map< cVectorProperty, list< cFibElement * > > mapWrongPoints;
		cVectorPosition vecPosition( 2 );
		for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
			for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
				//evalue the color of the point
				if ( ! matrixCorrectPoints[ ulX ][ ulY ] ){
					//wrong point -> correct point
					
					if ( colorPalette != NULL ){
						//till 8 bit
						bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
						
						if ( ulPaletteSize <= *indexValue ){
							continue;//skip pixel
						}
						*colorRGBValue = colorPalette[ *indexValue ];
					}else{
						//from 16 bit upwards
						bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
					}
					
					if ( bColor ){
						//set the property values
						if ( bSWColor ){
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
						}else{
							vecProperty.setValue( 1, colorRGBValue->rgbRed );
							vecProperty.setValue( 2, colorRGBValue->rgbGreen );
							vecProperty.setValue( 3, colorRGBValue->rgbBlue );
						}
#ifdef DEBUG_N_CONVERT_TO_FIB__JUST_CORRECTED_WRONG_POINTS
						//make all corrected point visibel
						vecProperty.setValue( 1, 255 );
#endif //DEBUG_N_CONVERT_TO_FIB__JUST_CORRECTED_WRONG_POINTS
					}
					vecPosition.setValue( 1, ulX );
					vecPosition.setValue( 2, ulY );
					cPoint * pPoint = new cPoint( &vecPosition );
#ifdef DEBUG
					cout<<"founded wrong point ("<<ulX<<", "<<ulY<<") for property:"<<endl;
					vecProperty.storeXml( cout );
#endif //DEBUG

#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
					//add points to size layer -1
					mapSizeClassPropertyFibObjects[ -1 ][ vecProperty ].push_back( pPoint );
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
					mapPropertyFibObjects[ vecProperty ].push_back( pPoint );
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
				}
			}
		}
	}//end correct wrong points
	
	//if needed the points for the different area fib-objects
	map< cFibElement *, list< cVectorPosition > > mapAreaObjectPoints;
	if ( bReduceFunctionDomains || bReplaceAreasWithPoints ){
		DEBUG_OUT_L2(<<"the points for the atomar areas (by filling mapAreaObjectPoints) "<<endl );
		//evalue the area underobjects
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		for ( map< int, map< cVectorProperty, list< cFibElement * > > >::iterator
				itrPropertAreas = mapSizeClassPropertyFibObjects.begin();
				itrPropertAreas != mapSizeClassPropertyFibObjects.end(); itrPropertAreas++ ){
			
			map< cVectorProperty,list< cFibElement * > > &
				mapLayerPropertyFibObjects = itrPropertAreas->second;
			
		for ( map< cVectorProperty, list< cFibElement * > >::iterator
				itrPropertyObjects = mapLayerPropertyFibObjects.begin();
				itrPropertyObjects != mapLayerPropertyFibObjects.end(); itrPropertyObjects++ ){
		
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		for ( map< cVectorProperty, list< cFibElement * > >::iterator
				itrPropertyObjects = mapPropertyFibObjects.begin();
				itrPropertyObjects != mapPropertyFibObjects.end(); itrPropertyObjects++ ){
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
			
			list< cFibElement * > & liUnderobjectsForProperty =
				itrPropertyObjects->second;
			
			for ( list< cFibElement * >::iterator
					itrUnderobject = liUnderobjectsForProperty.begin();
					itrUnderobject != liUnderobjectsForProperty.end();
					itrUnderobject++ ){
				
				const char cType = (*itrUnderobject)->getType();
				if ( cType == 'a' ){
					//is an area underobject -> add it
					mapAreaObjectPoints.insert( make_pair(
						(*itrUnderobject), list< cVectorPosition >() ) );
					
				}else if ( cType == 'l' ){
					//is an listelement -> add its underobject, which should be areas
					list< cFibElement * > liUnderobjects =
						((cList*)(*itrUnderobject))->getUnderobjects();
					
					for ( list< cFibElement * >::iterator
							itrListUnderobject = liUnderobjects.begin();
							itrListUnderobject != liUnderobjects.end();
							itrListUnderobject++ ){
						
						if ( (*itrListUnderobject)->getType() == 'a' ){
							//is an area underobject -> add it
							mapAreaObjectPoints.insert( make_pair(
								(*itrListUnderobject), list< cVectorPosition >() ) );
						}
					}
				}//else nothing to add
			}
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		}}
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		}
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
		//evalue the points of the area underobjects
		const unsignedLongFib ulNumberOfPoints = ulWidth * ulHeight;
		for ( map< cFibElement *, list< cVectorPosition > >::iterator
				itrUnderobject = mapAreaObjectPoints.begin();
				itrUnderobject != mapAreaObjectPoints.end(); itrUnderobject++ ){
			
			//evale points for the areas
			cFibElement * pAreaFibObject = itrUnderobject->first;
			
			cEvaluePositionListLimit evaluedPositionData( ulNumberOfPoints * 2,
				& vectorDomainDimension, true, 0, ulNumberOfPoints * 64 );
			
			const bool bObjectEvalued = pAreaFibObject->evalueObjectSimple(
				evaluedPositionData );
			if ( bObjectEvalued ){
			
				const list< pair< cVectorPosition, list< cVectorProperty > > > &
					liPoints = evaluedPositionData.liEvaluedPositionData;
				//convert positions vector list to data point set
				list< cVectorPosition > & liPositions = itrUnderobject->second;
				for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
						itrPoint = liPoints.begin();
						itrPoint != liPoints.end(); itrPoint++ ){
					
					liPositions.push_back( itrPoint->first );
				}
			}
		}//end for all area underobjects
	}//end evalue mapAreaObjectPoints
	
#ifdef FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
	//create ordering for properties
	DEBUG_OUT_L2(<<"create ordering for properties"<<endl );
	/*TODO??
	This list contains the fib-objects in the order they should be included.
	Fib-objects with higher size layer (more points) will be at the front
	of the list, so they can be overlaped.
		contained pairs:
			first: the property of the fib-object
			second: a list of the fib-objects to insert in the property
	list< pair< cVectorProperty, list< cFibElement * > > >
		liOrderedFiObjects;
	*/
	
	//create fib-objects for the properties, fib-elements with higher size layer first
	DEBUG_OUT_L2(<<"create fib-objects for the properties"<<endl );
	
	for ( map< int, map< cVectorProperty, list< cFibElement * > > >::reverse_iterator
			itrPropertAreas = mapSizeClassPropertyFibObjects.rbegin();
			itrPropertAreas != mapSizeClassPropertyFibObjects.rend(); itrPropertAreas++ ){
		
		map< cVectorProperty, list< cFibElement * > > &
			mapLayerPropertyFibObjects = itrPropertAreas->second;
		
		for ( map< cVectorProperty, list< cFibElement * > >::iterator
				itrPropertyObjects = mapLayerPropertyFibObjects.begin();
				itrPropertyObjects != mapLayerPropertyFibObjects.end(); itrPropertyObjects++ ){
			
			list< cFibElement * > & liUnderobjectsForProperty =
				itrPropertyObjects->second;
			
			if ( 2 <= liUnderobjectsForProperty.size() ){
#ifdef FEATURE_BALANCED_LOAD
				cList * pUnderListProperty = createBalancedList(
					liUnderobjectsForProperty, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
				cList * pUnderListProperty = new cList( liUnderobjectsForProperty );
#endif //FEATURE_BALANCED_LOAD
				cProperty * pProperty = new cProperty( itrPropertyObjects->first, pUnderListProperty );
				
				liUnderobjects.push_back( pProperty );
			}else if ( ! liUnderobjectsForProperty.empty() ){
				
				cProperty * pProperty = new cProperty( itrPropertyObjects->first,
					liUnderobjectsForProperty.front() );
				liUnderobjects.push_back( pProperty );
			}//else error no underobject -> nothing to insert
		}
	}
#else //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP

	//create fib-objects for the properties
	DEBUG_OUT_L2(<<"create fib-objects for the properties"<<endl );
	for ( map< cVectorProperty, list< cFibElement * > >::iterator
			itrPropertyObjects = mapPropertyFibObjects.begin();
			itrPropertyObjects != mapPropertyFibObjects.end(); itrPropertyObjects++ ){
		
		list< cFibElement * > & liUnderobjectsForProperty =
			itrPropertyObjects->second;
		
		if ( 2 <= liUnderobjectsForProperty.size() ){
#ifdef FEATURE_BALANCED_LOAD
			cList * pUnderListProperty = createBalancedList(
				liUnderobjectsForProperty, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
			cList * pUnderListProperty = new cList( liUnderobjectsForProperty );
#endif //FEATURE_BALANCED_LOAD
			cProperty * pProperty = new cProperty( itrPropertyObjects->first, pUnderListProperty );
			
			liUnderobjects.push_back( pProperty );
		}else if ( ! liUnderobjectsForProperty.empty() ){
			
			cProperty * pProperty = new cProperty( itrPropertyObjects->first,
				liUnderobjectsForProperty.front() );
			liUnderobjects.push_back( pProperty );
		}//else error no underobject -> nothing to insert
	}
	
#endif //FEATURE_CONVERT_TO_FIB_SMALL_AREAS_OVERLAP
	cFibElement * pMainFibObject = NULL;
	if ( 2 <= liUnderobjects.size() ){
#ifdef FEATURE_BALANCED_LOAD
		pMainFibObject = createBalancedList(
			liUnderobjects, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
		pMainFibObject = new cList( liUnderobjects );
#endif //FEATURE_BALANCED_LOAD
	}else if ( ! liUnderobjects.empty() ){
		
		pMainFibObject = liUnderobjects.front();
	}else{
		DEBUG_OUT_EL2(<<"Error: no underobjects to create the fib object"<<endl<<flush);
		DEBUG_OUT_EL2( <<"fib::nConvertToFib::convertOptimized() done"<<endl );
		return NULL;
	}
	cRoot * pMasterRoot = new cRoot( pMainFibObject );
	
	/*evalue the size of the image and include a corresponding dimension
	domain in the root -element*/
	
	//set domains of master root -object
	pMasterRoot->getDomains()->addDomain( typeDimension, vectorDomainDimension );

	/*evalue which properties are needed and include ther domains in the
	root -element*/
	//TODO include palletized domains
	
	unsigned int uiBitsPerColor = 0;
	if ( colorPalette == NULL ){
		uiBitsPerColor = multimediaObject.getBitsPerPixel();
	}else{
		if ( bSWColor ){
			uiBitsPerColor = 8;
		}else{
			uiBitsPerColor = 24;
		}
	}
	
	vector<cDomainSingle*> * pVecDomainColor = NULL;
	if ( bSWColor ){
		pVecDomainColor = new vector<cDomainSingle*>( 1, ((cDomainSingle*)NULL) );
		(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor );
	}else{
		pVecDomainColor = new vector<cDomainSingle*>( 3, ((cDomainSingle*)NULL) );
		if ( multimediaObject.getColorType() == FIC_RGB ){
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 3 );
		}else{//TODO include other color typs
			//for FIC_RGBALPHA
			(*pVecDomainColor)[ 0 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 1 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
			(*pVecDomainColor)[ 2 ] = new cDomainNaturalNumberBit( uiBitsPerColor / 4 );
		}
	}
	cDomainVector vectorDomainProperty( *pVecDomainColor );
	
	for ( unsigned int uiVectorElement = 0;
			uiVectorElement < pVecDomainColor->size(); uiVectorElement++ ){
		
		delete ((*pVecDomainColor)[ uiVectorElement ]);
	}
	delete pVecDomainColor;
	
	pMasterRoot->getDomains()->addDomain( typeProperty, vectorDomainProperty );
	
	const unsigned long ulBitsToStorePoint = 4 + 2 +
		domainWidth.getCompressedSizeForValue() +
		domainHeight.getCompressedSizeForValue();
	
	unsigned char ucModulesWithChanges = 2;
	while ( 2 <= ucModulesWithChanges ){
		ucModulesWithChanges = 0;
		
		if ( bReduceFunctionDomains ){
			//reduce area domains
			DEBUG_OUT_L2(<<endl<<"reduce area function value domains"<<endl );
			/*map with the bits for the mantissas of the function falues of the areas
				key: the maximal bits needed to store the function value mantissas
				value:
					first element: sum of the number of points in all areas for
						the bit number
					second element: a list with the given fib-objects wich need as
						minimum this number of bits*/
			map< unsigned int, nConvertReduced::cAreasBitInfo >
				mapBitsFunctionMantissaValues;
			//the number of all values in all area objects
			unsigned long ulNumberOfAllValues = 0;
			for ( map< cFibElement *, list< cVectorPosition > >::iterator
					itrArea = mapAreaObjectPoints.begin();
					itrArea != mapAreaObjectPoints.end(); itrArea++ ){
				
				cFibElement * pAreaFibObject = itrArea->first;
				
				const pair< unsigned int, unsigned long > paBitsForMantissa =
					evalueMaxFunctionValuesMantissaBits( pAreaFibObject );
				ulNumberOfAllValues += paBitsForMantissa.second;
				
				map< unsigned int, nConvertReduced::cAreasBitInfo >::iterator
					itrBitEntry = mapBitsFunctionMantissaValues.find( paBitsForMantissa.first );
				if ( itrBitEntry != mapBitsFunctionMantissaValues.end() ){
					//entry exists allready
					itrBitEntry->second.liAreas.push_back( pAreaFibObject );
					itrBitEntry->second.ulNumberOfValues += paBitsForMantissa.second;
					itrBitEntry->second.ulNumberOfPoints += itrArea->second.size();
					
				}else{//add new entry
					list< cFibElement * > liAreaForBits;
					liAreaForBits.push_back( pAreaFibObject );
					
					mapBitsFunctionMantissaValues.insert( make_pair(
						paBitsForMantissa.first,
						nConvertReduced::cAreasBitInfo( paBitsForMantissa.second,
							itrArea->second.size(), pAreaFibObject ) ) );
				}
			}//end for all atomar areas
#ifdef DEBUG
			cout<<"Number of atomar areas is "<<mapAreaObjectPoints.size()<<" with "<<
				mapBitsFunctionMantissaValues.size()<<" bits levels and "<<
				ulNumberOfAllValues<<" values."<<endl;
			for ( map< unsigned int, nConvertReduced::cAreasBitInfo >::iterator
					itrBitAreas = mapBitsFunctionMantissaValues.begin();
					itrBitAreas != mapBitsFunctionMantissaValues.end(); itrBitAreas++ ){
				
				cout<<"   for bits "<<itrBitAreas->first<<" ther are "<<
					itrBitAreas->second.liAreas.size()<<" areas with "<<
					itrBitAreas->second.ulNumberOfValues<<" values for "<<
					itrBitAreas->second.ulNumberOfPoints<<" points (that is at average "<<
					(itrBitAreas->second.ulNumberOfPoints / itrBitAreas->second.liAreas.size())<<
					" points per area)"<<endl;
			}
#endif //DEBUG
			if ( 1 < mapBitsFunctionMantissaValues.size() ){
				//if more than one bit value for the mantissas ->
				//find till wich number of bits to remove the areas
				map< unsigned int, nConvertReduced::cAreasBitInfo >::reverse_iterator
					itrBitAreas = mapBitsFunctionMantissaValues.rbegin();
				map< unsigned int, nConvertReduced::cAreasBitInfo >::reverse_iterator
					itrFirstBitAreasNotToRemove = mapBitsFunctionMantissaValues.rbegin();
				const unsigned int uiMaxBits = itrBitAreas->first;
				unsigned long ulPointsToInsert = 0;
				
				for ( ; itrBitAreas != mapBitsFunctionMantissaValues.rend(); itrBitAreas++ ){
					
					const unsigned long ulBitsToStorePointsForAreas =
						ulBitsToStorePoint * ulPointsToInsert;
					//bits saved for values, if the actaul areas wher removed
					const unsigned long ulBitsSavedForValues =
						(uiMaxBits - itrBitAreas->first) * ulNumberOfAllValues;
					
					DEBUG_OUT_L2(<<"check if areas till "<<itrBitAreas->first<<" bits function value mantissa should be removed (max bits="<<uiMaxBits<<", saved bits="<<ulBitsSavedForValues<<", number of areas for bits="<<itrBitAreas->second.liAreas.size()<<", wich can be replaced by "<<ulPointsToInsert<<" points with "<<ulBitsToStorePointsForAreas<<" bits, number of values in all remaining area objects "<<ulNumberOfAllValues<<" and for actual bits="<<itrBitAreas->second.ulNumberOfValues<<endl );
					
					if ( ulBitsToStorePointsForAreas < ( (ulBitsSavedForValues * 9) / 10) ){
						//remove all areas for more than this mantissa bits
						DEBUG_OUT_L2(<<"remove areas for bits"<<endl );
						itrFirstBitAreasNotToRemove = itrBitAreas;
					}
					ulPointsToInsert    += itrBitAreas->second.ulNumberOfPoints;
					ulNumberOfAllValues -= itrBitAreas->second.ulNumberOfValues;
				}
				//add areas to remove
				DEBUG_OUT_L2(<<"add areas to remove from "<<uiMaxBits<<" till "<<itrFirstBitAreasNotToRemove->first<<" bits (without it)"<<endl );
				set< cFibElement * > setAreasToReplaceByTherPoints;
				for ( itrBitAreas = mapBitsFunctionMantissaValues.rbegin();
						itrBitAreas != itrFirstBitAreasNotToRemove; itrBitAreas++ ){
				
					DEBUG_OUT_L2(<<"remove "<<itrBitAreas->second.liAreas.size()<<" areas for "<<itrBitAreas->first<<" bits"<<endl );
					list< cFibElement * > & liAreasForBits = itrBitAreas->second.liAreas;
					setAreasToReplaceByTherPoints.insert( liAreasForBits.begin(),
						liAreasForBits.end() );
				
				}
				//replace areas with ther points
				DEBUG_OUT_L2(<<"replace "<<setAreasToReplaceByTherPoints.size()<<" areas with ther points"<<endl );
				for ( set< cFibElement * >::iterator
						itrArea = setAreasToReplaceByTherPoints.begin();
						itrArea != setAreasToReplaceByTherPoints.end();
						itrArea++ ){
					
					list< cVectorPosition > & liPointsForArea =
						mapAreaObjectPoints[ *itrArea ];
					
					DEBUG_OUT_L2(<<"the area "<<(*itrArea)<<" has "<<liPointsForArea.size()<<" points to insert"<<endl );
					list< cFibElement * > liToInsertPoints;
					for ( list< cVectorPosition >::iterator itrPoint = liPointsForArea.begin();
							itrPoint != liPointsForArea.end();itrPoint++ ){
						
						liToInsertPoints.push_back( new cPoint( &(*itrPoint) ) );
					}
					cFibElement * pFibObjectToInsert = NULL;
					if ( 2 <= liToInsertPoints.size() ){
#ifdef FEATURE_BALANCED_LOAD
						pFibObjectToInsert = createBalancedList(
							liToInsertPoints, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
						pFibObjectToInsert = new cList( liToInsertPoints );
#endif //FEATURE_BALANCED_LOAD
					}else if ( ! liToInsertPoints.empty() ){
						
						pFibObjectToInsert = liToInsertPoints.front();
					}//else error no underobject -> nothing to insert
					if ( pFibObjectToInsert ){
						//replace area with its points
						DEBUG_OUT_L2(<<"pMasterRoot->overwriteObjectWithObject( pFibObjectToInsert="<<pFibObjectToInsert<<", 'u', (*itrArea)->getNumberOfElement()="<<((*itrArea)->getNumberOfElement())<<", true, true )"<<endl );
						const bool bAreaReplaced = pMasterRoot->overwriteObjectWithObject(
							pFibObjectToInsert, 'u', (*itrArea)->getNumberOfElement(), true, true );
						if ( bAreaReplaced ){
							//update mapping to points (maybe its needed later)
							mapAreaObjectPoints.erase( *itrArea );
						}else{//delete created points object
							DEBUG_OUT_EL2(<<"Couldn't replace area object ("<<(*itrArea)<<" with its points"<<endl );
							pFibObjectToInsert->deleteObject();
						}
					}
				}//end for replace areas
				if ( ! setAreasToReplaceByTherPoints.empty() ){
					//this modul has changed the fib-object
					ucModulesWithChanges++;
				}
			}//end if ( 1 < mapBitsFunctionMantissaValues.size() )
		}//end if bReduceFunctionDomains
		
		
		//generate domains for the function and area elements
		pMasterRoot->generateNeededDomains();
		
		if ( bReplaceAreasWithPoints ){
			//replace areas, which need more bits to store than ther points, with ther points
			DEBUG_OUT_L2(<<endl<<"replace areas, which need more bits to store than ther points, with ther points (wool fib-object bits now "<<pMasterRoot->getCompressedSize()<<")"<<endl );
			
			set< cFibElement * > setAreasToReplaceByTherPoints;
			for ( map< cFibElement *, list< cVectorPosition > >::iterator
					itrArea = mapAreaObjectPoints.begin();
					itrArea != mapAreaObjectPoints.end(); itrArea++ ){
				
				cFibElement * pAreaFibObject = itrArea->first;
				
				const unsigned long ulBitsNeededForArea =
					pAreaFibObject->getCompressedSize();
				
				const unsigned long ulBitsToStorePointsForAreas =
					ulBitsToStorePoint * itrArea->second.size();
				
				//DEBUG_OUT_L4(<<"check if "<<pAreaFibObject<<" area should be replace by its points (bits area ="<<ulBitsNeededForArea<<", bits needed for "<<itrArea->second.size()<<" points  "<<ulBitsToStorePointsForAreas<<")"<<endl );
				
				if ( ulBitsToStorePointsForAreas < ( (ulBitsNeededForArea * 9) / 10) ){
					//remove areas for bits
					DEBUG_OUT_L2(<<"mark "<<pAreaFibObject<<" area to replace by its points (bits area ="<<ulBitsNeededForArea<<", bits needed for "<<itrArea->second.size()<<" points "<<ulBitsToStorePointsForAreas<<")"<<endl );
					setAreasToReplaceByTherPoints.insert( pAreaFibObject );
				}
			}//end for all atomar areas
			//replace areas with ther points
			DEBUG_OUT_L2(<<"replace "<<setAreasToReplaceByTherPoints.size()<<" areas with ther points"<<endl );
			for ( set< cFibElement * >::iterator
					itrArea = setAreasToReplaceByTherPoints.begin();
					itrArea != setAreasToReplaceByTherPoints.end();
					itrArea++ ){
				
				list< cVectorPosition > & liPointsForArea =
					mapAreaObjectPoints[ *itrArea ];
				
				//DEBUG_OUT_L4(<<"the area "<<(*itrArea)<<" has "<<liPointsForArea.size()<<" points to insert"<<endl );
				list< cFibElement * > liToInsertPoints;
				for ( list< cVectorPosition >::iterator itrPoint = liPointsForArea.begin();
						itrPoint != liPointsForArea.end();itrPoint++ ){
					
					liToInsertPoints.push_back( new cPoint( &(*itrPoint) ) );
				}
				cFibElement * pFibObjectToInsert = NULL;
				if ( 2 <= liToInsertPoints.size() ){
#ifdef FEATURE_BALANCED_LOAD
					pFibObjectToInsert = createBalancedList(
						liToInsertPoints, FEATURE_BALANCED_LOAD );
#else //FEATURE_BALANCED_LOAD
					pFibObjectToInsert = new cList( liToInsertPoints );
#endif //FEATURE_BALANCED_LOAD
				}else if ( ! liToInsertPoints.empty() ){
					
					pFibObjectToInsert = liToInsertPoints.front();
				}//else error no underobject -> nothing to insert
				if ( pFibObjectToInsert ){
					//replace area with its points
					DEBUG_OUT_L3(<<"pMasterRoot->overwriteObjectWithObject( pFibObjectToInsert="<<pFibObjectToInsert<<", 'u', (*itrArea)->getNumberOfElement()="<<((*itrArea)->getNumberOfElement())<<", true, true )"<<endl );
					const bool bAreaReplaced = pMasterRoot->overwriteObjectWithObject(
						pFibObjectToInsert, 'u', (*itrArea)->getNumberOfElement(), true, true );
					if ( bAreaReplaced ){
						//update mapping to points (maybe its needed later)
						mapAreaObjectPoints.erase( *itrArea );
					}else{//delete created points object
						DEBUG_OUT_EL2(<<"Couldn't replace area object ("<<(*itrArea)<<" with its points"<<endl );
						pFibObjectToInsert->deleteObject();
					}
				}else{//no pints in area -> remove area
					const unsignedIntFib uiObjectToRemove =
						pMasterRoot->getObjectPointsForElement( (*itrArea), true ).back();
					DEBUG_OUT_L2(<<"no points in area -> remove area with object point "<<uiObjectToRemove<<endl );
					const bool bAreaRemoved = pMasterRoot->removeObject(
						uiObjectToRemove, true, true );
					if ( bAreaRemoved ){
						//update mapping to points (maybe its needed later)
						DEBUG_OUT_L2(<<"   area object removed"<<endl );
						mapAreaObjectPoints.erase( *itrArea );
					}
				}
			}//end for replace areas
			if ( ! setAreasToReplaceByTherPoints.empty() ){
				//this modul has changed the fib-object
				ucModulesWithChanges++;
				//generate again domains for the function and area elements
				pMasterRoot->generateNeededDomains();
				DEBUG_OUT_L2( <<"wool fib-object bits now "<<pMasterRoot->getCompressedSize()<<" after replacing areas"<<endl );
			}
		}
	
	}//end while minimum two modules changed

	
	
	/*include image description data into the optionalpart of the
	root -element*/
	//TODO
	
	
	//clean
	delete colorRGBValue;
	delete indexValue;

	DEBUG_OUT_L1( <<"fib::nConvertToFib::convertReduced() ended correctly"<<endl );
	
	return pMasterRoot;
}




/**
 * This function conts how oftern the different colors occure in the
 * given pictur.
 *
 * @param multimediaObject the multimedaobject wher to count the colors
 * @return a map with the color values and ther counts
 */
map< vector< unsigned int >, unsigned long > fib::nConvertToFib::countColors(
		const fipImage & multimediaObject ){
	
	//count colors
	const unsigned long ulWidth  = multimediaObject.getWidth();
	const unsigned long ulHeight = multimediaObject.getHeight();
	RGBQUAD * colorRGBValue = new RGBQUAD();
	BYTE * indexValue = new BYTE();
	RGBQUAD * colorPalette = multimediaObject.getPalette();
	const unsigned long ulPaletteSize = (colorPalette == NULL) ?
		0 : multimediaObject.getPaletteSize();
	bool bSWColor = false;
	if ( multimediaObject.isGrayscale() ){
		bSWColor = true;
	}
	bool bColor;
	map< vector< unsigned int >, unsigned long > mapColorCounts;
	vector< unsigned int > vecColor;
	if ( bSWColor ){
		//grayscale color
		vecColor = vector< unsigned int >( 1, 0 );
	}else{//RGB-Color
		vecColor = vector< unsigned int >( 3, 0 );
	}
	
	for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
		
		for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
			//evalue the color of the point
			
//			DEBUG_OUT_L4( <<"evalue point X="<< ulX <<" Y="<< ulY <<endl );
			
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue = colorPalette[ *indexValue ];
			}else{
				//from 16 bit upwards
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
			}
			
			if ( bColor ){
				//set the property values
				if ( bSWColor ){
					vecColor[ 0 ] = colorRGBValue->rgbRed;
				}else{
					vecColor[ 0 ] = colorRGBValue->rgbRed;
					vecColor[ 1 ] = colorRGBValue->rgbGreen;
					vecColor[ 2 ] = colorRGBValue->rgbBlue;
				}
				
				map< vector< unsigned int >, unsigned long >::iterator
					itrColor = mapColorCounts.find( vecColor );
				
				if ( itrColor == mapColorCounts.end() ){
					//color not found -> new color
					mapColorCounts.insert( make_pair( vecColor, 1 ) );
				}else{//color found -> add 1
					itrColor->second++;
				}
			}
		}
	}
	delete colorRGBValue;
	delete indexValue;
	
	return mapColorCounts;
}


/**
 * This function maps the colors of the given pictur accordingly to the
 * given mapping.
 * Colors not in the map won't be changed.
 *
 * @param multimediaObject the multimedaobject wher to change the colors
 * @param mapColorMapping the mapping for the colors:
 * 	key: the source color
 * 	value: to which color the color should be mapped
 * 	(BEWARE: all color vectors of the map should have the correct size.)
 */
void fib::nConvertToFib::mapColors( fipImage & multimediaObject,
		const map< vector< unsigned int >, vector< unsigned int > > & mapColorMapping ){
	
	//count colors
	const unsigned long ulWidth  = multimediaObject.getWidth();
	const unsigned long ulHeight = multimediaObject.getHeight();
	RGBQUAD * colorRGBValue = new RGBQUAD();
	RGBQUAD * colorValue = new RGBQUAD();
	BYTE * indexValue = new BYTE();
	RGBQUAD * colorPalette = multimediaObject.getPalette();
	const unsigned long ulPaletteSize = (colorPalette == NULL) ?
		0 : multimediaObject.getPaletteSize();
	bool bSWColor = false;
	if ( multimediaObject.isGrayscale() ){
		bSWColor = true;
	}
	bool bColor;
	vector< unsigned int > vecColor;
	if ( bSWColor ){
		//grayscale color
		vecColor = vector< unsigned int >( 1, 0 );
	}else{//RGB-Color
		vecColor = vector< unsigned int >( 3, 0 );
	}
	
	for ( unsigned long ulX = 0; ulX < ulWidth; ulX++ ){
		
		for ( unsigned long ulY = 0; ulY < ulHeight; ulY++ ){
			//evalue the color of the point
			
//			DEBUG_OUT_L4( <<"evalue point X="<< ulX <<" Y="<< ulY <<endl );
			
			if ( colorPalette != NULL ){
				//till 8 bit
				bColor = multimediaObject.getPixelIndex( ulX, ulY, indexValue );
				
				if ( ulPaletteSize <= *indexValue ){
					continue;//skip pixel
				}
				*colorRGBValue = colorPalette[ *indexValue ];
			}else{
				//from 16 bit upwards
				bColor = multimediaObject.getPixelColor( ulX, ulY, colorRGBValue );
			}
			
			if ( bColor ){
				//set the property values
				if ( bSWColor ){
					vecColor[ 0 ] = colorRGBValue->rgbRed;
				}else{
					vecColor[ 0 ] = colorRGBValue->rgbRed;
					vecColor[ 1 ] = colorRGBValue->rgbGreen;
					vecColor[ 2 ] = colorRGBValue->rgbBlue;
				}
				const map< vector< unsigned int >, vector< unsigned int > >::const_iterator
					itrColor = mapColorMapping.find( vecColor );
				
				if ( itrColor != mapColorMapping.end() ){
					//color found -> map color
					if ( vecColor == itrColor->second ){
						//don't change color
						continue;
					}
					vecColor = itrColor->second;
				}else{//color not found -> don't change color
					continue;
				}
				
				if ( colorPalette != NULL ){
					//if color palette -> find and add index of color
					for ( BYTE actualIndexValue = 0;
							actualIndexValue < ulPaletteSize; actualIndexValue++ ) {
						if ( (  colorPalette[ actualIndexValue ].rgbRed   == vecColor[ 0 ] ) &&
								( colorPalette[ actualIndexValue ].rgbGreen == vecColor[ 1 ] ) &&
								( colorPalette[ actualIndexValue ].rgbBlue  == vecColor[ 2 ] ) ){
							//correct color index found
							multimediaObject.setPixelIndex( ulX, ulY, &actualIndexValue );
							break;
						}
					}//end search for index for color
				}else{//no color palette given
					if ( bSWColor ){
						//set grayscale color values
						colorValue->rgbRed   = vecColor[ 0 ];
						colorValue->rgbGreen = vecColor[ 0 ];
						colorValue->rgbBlue  = vecColor[ 0 ];
					}else{
						//set rgb-color values
						colorValue->rgbRed   = vecColor[ 0 ];
						colorValue->rgbGreen = vecColor[ 1 ];
						colorValue->rgbBlue  = vecColor[ 2 ];
					}
					multimediaObject.setPixelColor( ulX, ulY, colorValue );
				}//end if color palette
			}//end if color loaded
		}//end for al y
	}//end for all x
	delete colorRGBValue;
	delete colorValue;
	delete indexValue;
}









