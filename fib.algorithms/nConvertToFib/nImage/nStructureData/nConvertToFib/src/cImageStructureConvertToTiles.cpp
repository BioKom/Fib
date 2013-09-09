/**
 * @file cImageStructureConvertToTiles
 * file name: cImageStructureConvertToTiles.h
 * @author Betti Oesterholz
 * @date 29.11.2012
 * @mail Oesterholz@Fib-development.org
 *
 * System: C++
 *
 * This header specifies a class to convert the data of a area of points
 * in an image to tiles.
 *
 * Copyright (C) @c GPL3 2012 Betti Oesterholz
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License (GPL) as
 * published by the Free Software Foundation, either version 3 of the
 * License, or any later version.
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
 * This header specifies a class to convert the data of a area of points
 * in an image to tiles.
 *
 * @patter strategy
 */
/*
History:
29.11.2012  Oesterholz  created
*/

//switches for debugging proposes
//#define DEBUG
//#define DEBUG_ADDING_POINTS
//#define DEBUG_REMOVE_POINT_METHOD
//#define DEBUG_DELETING_POINTS
//#define DEBUG_OUTPUT_GENERATED_AREA_DATA


#ifdef DEBUG
	#include <iomanip>
#endif //DEBUG

#include "cImageStructureConvertToTiles.h"

#include "cDataPointRange.h"

#include "fibDatatyps.h"
#include "cVectorPosition.h"
#include "cProperty.h"
#include "cVectorProperty.h"
#include "cTypeProperty.h"
#include "cPoint.h"
#include "cEvaluePositionList.h"
#include "cEvaluePositionListLimit.h"
#include "cPolynom.h"
#include "cDomainNaturalNumber.h"
#include "cDomainVector.h"


#if defined(DEBUG_OUTPUT_GENERATED_AREA_DATA) //|| defined(DEBUG)
	#include <iostream>
	#include <fstream>
	
	#include "cImageAreaSameColor.h"
	
	#ifndef DEBUG_OUTPUT_GENERATED_AREA_DATA_FILE
		#define DEBUG_OUTPUT_GENERATED_AREA_DATA_FILE "genAreaData.xml"
	#endif //DEBUG_OUTPUT_STRUCTURE_DATA_FILE
#endif //defined(DEBUG_OUTPUT_GENERATED_AREA_DATA) || defined(DEBUG)


/**
 * With this feature the size of the straight lines will be the number of
 * points in the area to the straight line.
 *
 * created: 29.04.2013  Betti Oesterholz
 * status:  running and tested(04.2013)
 * (deprecated: not FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE)
 *//*
History:
*/
#define FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE


/**
 * With this feature the rectangle external object with identifer -40 will
 * be used for areas, for which it is possible.
 *
 * created: 13.05.2013  Betti Oesterholz
 * status:  running and tested(05.2013)
 * (deprecated: not FEATURE_USE_RECTANGLE_EXT_OBJECT)
 *//*
History:
*/
#define FEATURE_USE_RECTANGLE_EXT_OBJECT

/**
 * With this feature the cImageStructureConvertToTiles::convertToTiles()
 * method will use extra range points for area border line to match.
 * These extra points will have a lower whight than the possible range points.
 *
 * @see fib::algorithms::nConvertToFib::nImage::nStructureData::nConvertToFib::cImageStructureConvertToTiles::convertToTiles()
 *
 * created: 30.04.2013  Betti Oesterholz
 * Status:  implemened and tested(30.04.2013 not a good parameter)
 * Needed: FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
 *//*
History:
*/
#ifdef FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING
	//#define FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
#endif //FEATURE_C_SPLINE_USE_GLP_LIB_LINAR_PROBLEM_SOLVING



#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
	/**
	 * The weight for a point to match the area border line.
	 */
	#define D_WEIGHT_INNER_POINT 0.00000001
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE



using namespace fib::algorithms::nConvertToFib::nImage::nStructureData::nConvertToFib;
using namespace fib::algorithms::nD1;
using namespace fib;


namespace fib{
namespace algorithms{
namespace nConvertToFib{
namespace nImage{
namespace nStructureData{
namespace nConvertToFib{
namespace nImageStructureConvertToTiles{

/**
 * The area line for one fix coordinat value.
 * This is a helper class for:
 * 	@see cImageStructureConvertToTiles::convertToExtObjects()
 */
class cLine{
public:
	
	/**
	 * The part of the line, with its start and end point.
	 */
	typedef pair<
		fib::algorithms::nD1::cDataPointRange< long, double >,
		fib::algorithms::nD1::cDataPointRange< long, double > >
			tLinePart;
	
	/**
	 * The type for the container with the parts of the line.
	 */
	typedef list< tLinePart > tLineParts;
	
	/**
	 * The container with the parts of the line.
	 */
	tLineParts lineParts;
	
	/**
	 * The coordinate value of all line points.
	 */
	long lLineDirectionCoordinateValue;
	
	/**
	 * Constructor
	 *
	 * @param lInLineDirectionCoordinateValue the coordinate value of all
	 * 	line points
	 */
	cLine( const long lInLineDirectionCoordinateValue ):
			lLineDirectionCoordinateValue( lInLineDirectionCoordinateValue ){
		//nothing to do
	}
	
	
	/**
	 * This method adds the given point to the line.
	 *
	 * @param lPointsOtherCoordinate the other point coordinate value
	 * 	(should be an integer value and not added befor)
	 */
	void addPoint( const long lPointsOtherCoordinate ){
		
		const double dPointsOtherCoordinate = lPointsOtherCoordinate;
		
		//find the line part nearest to the coordinat value
		tLineParts::iterator itrNearestLinePart = lineParts.begin();
		
		/*begin with the search at back of list (normaly the coordinate will
		 *increase with each call)*/
		for ( tLineParts::reverse_iterator revItrNearestLinePart = lineParts.rbegin();
				revItrNearestLinePart != lineParts.rend(); revItrNearestLinePart++ ){
			
			if ( revItrNearestLinePart->first.minY < dPointsOtherCoordinate ){
				//nearest line part found (itrNearestLinePart has the next bigger values)
				itrNearestLinePart = revItrNearestLinePart.base();
				break;
			}
		}
		if ( itrNearestLinePart != lineParts.end() ){
			//bigger line part found
			if ( itrNearestLinePart != lineParts.begin() ){
				//if two near line parts
				tLineParts::iterator itrNearestLinePart2 = itrNearestLinePart;
				itrNearestLinePart2--;
				//check if the point was already added
				if ( dPointsOtherCoordinate < itrNearestLinePart2->second.minY ){
					return;//point was already added
				}
				//check if the two line parts concatinate with the point
				if ( ( dPointsOtherCoordinate <
						( itrNearestLinePart2->second.minY + 2.0 ) ) &&
					( ( itrNearestLinePart->first.minY - 2.0 ) <
						dPointsOtherCoordinate ) ){
					//concatinate line parts
					itrNearestLinePart2->second.minY =
						itrNearestLinePart->second.minY;
					lineParts.erase( itrNearestLinePart );
					
					return;//point was added
				}//else if point not added
				//check if the point should be added to the first line part
				if ( dPointsOtherCoordinate <
						( itrNearestLinePart2->second.minY + 2.0 )  ){
					//add point to first line part
					itrNearestLinePart2->second.minY += 1.0;
					return;//point was added
				}
				//check if the point should be added to the second line part
				if ( ( itrNearestLinePart->first.minY - 2.0 ) <
						dPointsOtherCoordinate ){
					//add point to secound line part
					itrNearestLinePart->first.minY -= 1.0;
					return;//point was added
				}
				
			}else{//if one near line part
				//check if the point should be added to the line part
				if ( ( itrNearestLinePart->first.minY - 2.0 ) < dPointsOtherCoordinate ){
					//add point to line part
					itrNearestLinePart->first.minY -= 1.0;
					return;//point was added
				}
			}
		}else{//if ( itrNearestLinePart == lineParts.end() )
			if ( ! lineParts.empty() ){
				tLineParts::iterator itrNearestLinePart2 = itrNearestLinePart;
				itrNearestLinePart2--;
				//check if the point should be added to the line part
				if ( dPointsOtherCoordinate <
						( itrNearestLinePart2->second.minY + 2.0 )  ){
					//add point to line part
					itrNearestLinePart2->second.minY += 1.0;
					return;//point was added
				}
			}
		}
		//if point was not added
		//add new line part for the point
		fib::algorithms::nD1::cDataPointRange< long, double >
			lowerBorder( lLineDirectionCoordinateValue );
		lowerBorder.minY = dPointsOtherCoordinate + 0.49;
			
		fib::algorithms::nD1::cDataPointRange< long, double >
			upperBorder( lLineDirectionCoordinateValue );
		upperBorder.minY = dPointsOtherCoordinate - 0.49;
		
		//insert befor nearest line part
		lineParts.insert( itrNearestLinePart,
			make_pair( lowerBorder, upperBorder ) );
	}
	
	
	/**
	 * This method removes the given point from the line.
	 *
	 * @param lPointsOtherCoordinate the other point coordinate value
	 * 	(should be an integer value)
	 * @return true if the point could be removed, else false
	 */
	bool removePoint( const long lPointsOtherCoordinate ){
		
#ifdef DEBUG_REMOVE_POINT_METHOD
		cout<<"removePoint( lPointsOtherCoordinate="<<
			lPointsOtherCoordinate<<" ) started (line="<<
			lLineDirectionCoordinateValue<<")"<<endl;
#endif //DEBUG_REMOVE_POINT_METHOD
		const double dPointsOtherCoordinate = lPointsOtherCoordinate;
		//the upper border has x.51 so (x + 1) is the border
		const double dPointsOtherCoordinateDec1 = dPointsOtherCoordinate - 1;
	
		//find the line part nearest to the coordinat value
		tLineParts::iterator itrNearestLinePart;
		for ( itrNearestLinePart = lineParts.begin();
				itrNearestLinePart != lineParts.end(); itrNearestLinePart++ ){
			/*itrNearestLinePart->second.minY = x.51 -> border is (x + 1)
			 -> check if dPointsOtherCoordinate < (x + 1)
			 -> dPointsOtherCoordinateDec1 < x.51 */
			if ( dPointsOtherCoordinateDec1 < itrNearestLinePart->second.minY ){
				//line part for point found
				break;
			}
		}//end find line part nearest to the coordinat value
#ifdef DEBUG_REMOVE_POINT_METHOD
		if ( itrNearestLinePart != lineParts.end() ){
			cout<<"   nearest line part from max "<<std::fixed<<
				itrNearestLinePart->first.maxY<<" min "<<
				itrNearestLinePart->first.minY<<" till min "<<
				itrNearestLinePart->second.minY<<" max "<<
				itrNearestLinePart->second.maxY<<""<<endl;
		}else{
			cout<<"   no nearest line part found (in "<<lineParts.size()<<" line parts)"<<endl;
		}
#endif //DEBUG_REMOVE_POINT_METHOD
		
		if ( ( itrNearestLinePart != lineParts.end() ) &&
				( itrNearestLinePart->first.minY - 1 < dPointsOtherCoordinate ) &&
				( dPointsOtherCoordinate < itrNearestLinePart->second.minY + 1 ) ){
			//if inside first.minY second.minY -> erase point
			if (  dPointsOtherCoordinate < itrNearestLinePart->first.minY ){
				/* if at beginning of the part line -> move min border one to the
				* left (add 1 to first.minY)*/
				itrNearestLinePart->first.minY += 1.0;
				//if part line don't contain any points anymore (betwean minY's) -> remove it
				/*erase point if ( round( second.minY ) < round( first.minY ) );
					first.minY has 0.49 after point and second.minY 0.51 */
				if ( ( itrNearestLinePart->second.minY + 1.0 ) < itrNearestLinePart->first.minY ){
					lineParts.erase( itrNearestLinePart );
#ifdef DEBUG_REMOVE_POINT_METHOD
					cout<<"   line part erased"<<endl;
					itrNearestLinePart == lineParts.end();
#endif //DEBUG_REMOVE_POINT_METHOD
				}
			}else if ( itrNearestLinePart->second.minY < dPointsOtherCoordinate ){
				/* else if at end of the part line -> move min border one to the
				* right (decrase second.minY with 1)*/
				itrNearestLinePart->second.minY -= 1.0;
				//if part line don't contain any points anymore (betwean minY's) -> remove it
				//erase point if ( round( second.minY ) < round( first.minY ) )
				if ( ( itrNearestLinePart->second.minY + 1.0 ) < itrNearestLinePart->first.minY ){
					lineParts.erase( itrNearestLinePart );
				}
			}else{/* else if inside the part line -> split part lines into two parts
				* left and right of point;
				* the maxY of both part lines will be the values of the original part line*/
				//the new part line is befor the old part line
				tLinePart newPartLine( *itrNearestLinePart );
				//remove point from part line
				newPartLine.second.minY = dPointsOtherCoordinate - 1.49;
				itrNearestLinePart->first.minY = dPointsOtherCoordinate + 1.49;
				
				lineParts.insert( itrNearestLinePart, newPartLine );
#ifdef DEBUG_REMOVE_POINT_METHOD
			cout<<"   adding new line part from max "<<std::fixed<<
				newPartLine.first.maxY<<" min "<<
				newPartLine.first.minY<<" till min "<<
				newPartLine.second.minY<<" max "<<
				newPartLine.second.maxY<<""<<endl;
#endif //DEBUG_REMOVE_POINT_METHOD
			}//end remove point
			
#ifdef DEBUG_REMOVE_POINT_METHOD
			if ( itrNearestLinePart != lineParts.end() ){
				cout<<"   changed line part from max "<<std::fixed<<
					itrNearestLinePart->first.maxY<<" min "<<
					itrNearestLinePart->first.minY<<" till min "<<
					itrNearestLinePart->second.minY<<" max "<<
					itrNearestLinePart->second.maxY<<""<<endl;
				cout<<"removePoint( lPointsOtherCoordinate="<<
					lPointsOtherCoordinate<<" ) done point removed"<<endl;
			}
#endif //DEBUG_REMOVE_POINT_METHOD
			return true;
		}//else if point was not removed
#ifdef DEBUG_REMOVE_POINT_METHOD
		cout<<"removePoint( lPointsOtherCoordinate="<<
			lPointsOtherCoordinate<<" ) done point was not removed"<<endl;
		
		//check if point is in one line part
		for ( itrNearestLinePart = lineParts.begin();
				itrNearestLinePart != lineParts.end(); itrNearestLinePart++ ){
			if ( ( itrNearestLinePart->first.maxY <= dPointsOtherCoordinate ) &&
					( dPointsOtherCoordinate <= itrNearestLinePart->second.maxY ) ){
				//line part for point found
				break;
			}
		}//end find line part nearest to the coordinat value
		if ( itrNearestLinePart == lineParts.end() ){
			//line part for point not found
			cout<<"Point "<<lPointsOtherCoordinate<<" for line "<<
				lLineDirectionCoordinateValue<<" in no line part (betwean max max)"<<endl;
		}
		//check if point is in one line part
		for ( itrNearestLinePart = lineParts.begin();
				itrNearestLinePart != lineParts.end(); itrNearestLinePart++ ){
			if ( ( (itrNearestLinePart->first.minY - 1.0) <= dPointsOtherCoordinate ) &&
					( dPointsOtherCoordinate <= (itrNearestLinePart->second.minY + 1.0 ) ) ){
				//line part for point found
				break;
			}
		}//end find line part nearest to the coordinat value
		if ( itrNearestLinePart != lineParts.end() ){
			//line part for point not found
			cerr<<"Error: Point "<<lPointsOtherCoordinate<<" for line "<<
				lLineDirectionCoordinateValue<<" in removebel line part (betwean min min)"<<endl;
		}
#endif //DEBUG_REMOVE_POINT_METHOD
		return false;
	}
	
	
	/**
	 * This method adapts the maximal border to the value of the minimal
	 * border value.
	 * The maximum border value is then the minimum border value minus 0.98
	 * if it is the left / lower border and plus 0.98 if it is the right /
	 * higher border.
	 */
	void adaptAllMaxToMinValue(){
		
		for ( tLineParts::iterator itrNearestLinePart = lineParts.begin();
				itrNearestLinePart != lineParts.end(); itrNearestLinePart++ ){
			//for all line parts
			itrNearestLinePart->first.maxY  = itrNearestLinePart->first.minY - 0.98;
			itrNearestLinePart->second.maxY = itrNearestLinePart->second.minY + 0.98;
		}
	}
	
	
	/**
	 * Add to the line maximum area all points, which are already overlapped
	 * in the search data.
	 * Also adds dLeftBorder to the maximum area of lines which begin befor 0.
	 *
	 * @param uiDimension for which dimension this line is
	 * @param pImageSearchData the search data, wher the overlapped areas
	 * 	are stored
	 * @param dLeftBorder the value to which to set the left border, if max
	 * 	is below 0
	 */
	void enlargeMaxForSearchData( const unsigned int uiDimension,
			const cImageSearchData * pImageSearchData,
			double dLeftBorder = -32.0 ){
		
		if ( pImageSearchData == NULL ){
			//no search data nothing overlapped
			return;
		}
		
		if ( uiDimension == 1 ){
			const long lPositionDim1 = lLineDirectionCoordinateValue;
			long lPositionDim2 = 0;
			//for every part line
			for ( tLineParts::iterator itrActualLinePart = lineParts.begin();
					itrActualLinePart != lineParts.end(); itrActualLinePart++ ){
				
				//for lower border decrease till not overlapt point is reached or lower 0
				lPositionDim2 = roundToLongFib( itrActualLinePart->first.maxY );
				if ( 0 < lPositionDim2 ){
					lPositionDim2--;
					for ( ; 0 < lPositionDim2; lPositionDim2-- ){
						
						if ( ! pImageSearchData->isOverlapped(
									lPositionDim1, lPositionDim2 ) ){
							//point not overlapped
							break;
						}
					}
					//set max area to last overlapped point
					if ( 0 < lPositionDim2 ){
						itrActualLinePart->first.maxY = ((double)(lPositionDim2)) + 0.51;
					}else{//lPositionDim2 < 0 -> border point -> set dLeftBorder
						itrActualLinePart->first.maxY = dLeftBorder;
					}
				}else{//border point -> set dLeftBorder
					itrActualLinePart->first.maxY = dLeftBorder;
				}
				
				//second dimension width
				const long ulDim2Max = pImageSearchData->getHeight();
				
				//for upper border increase till not overlapt point is reached
				lPositionDim2 = roundToLongFib( itrActualLinePart->second.maxY );
				
				lPositionDim2++;
				for ( ; lPositionDim2 < ulDim2Max; lPositionDim2++ ){
					
					if ( ! pImageSearchData->isOverlapped(
								lPositionDim1, lPositionDim2 ) ){
						//point not overlapped
						break;
					}
				}
				//set max area to last overlapped point
				itrActualLinePart->second.maxY = ((double)(lPositionDim2)) - 0.51;
			}//end for all part lines
		}else{//line for dimension 2
			const long lPositionDim2 = lLineDirectionCoordinateValue;
			long lPositionDim1 = 0;
			//for every part line
			for ( tLineParts::iterator itrActualLinePart = lineParts.begin();
					itrActualLinePart != lineParts.end(); itrActualLinePart++ ){
				
				//for lower border decrease till not overlapt point is reached or lower 0
				lPositionDim1 = roundToLongFib( itrActualLinePart->first.maxY );
				if ( 0 < lPositionDim1 ){
					lPositionDim1--;
					for ( ; 0 < lPositionDim1; lPositionDim1-- ){
						
						if ( ! pImageSearchData->isOverlapped(
									lPositionDim1, lPositionDim2 ) ){
							//point not overlapped
							break;
						}
					}
					//set max area to last overlapped point
					if ( 0 < lPositionDim1 ){
						itrActualLinePart->first.maxY = ((double)(lPositionDim1)) + 0.51;
					}else{//lPositionDim1 < 0 -> border point -> set dLeftBorder
						itrActualLinePart->first.maxY = dLeftBorder;
					}
				}else{//border point -> set dLeftBorder
					itrActualLinePart->first.maxY = dLeftBorder;
				}
				
				//second dimension width
				const long ulDim1Max = pImageSearchData->getWidth();
				
				//for upper border increase till not overlapt point is reached
				lPositionDim1 = roundToLongFib( itrActualLinePart->second.maxY );
				
				lPositionDim1++;
				for ( ; lPositionDim1 < ulDim1Max; lPositionDim1++ ){
					
					if ( ! pImageSearchData->isOverlapped(
								lPositionDim1, lPositionDim2 ) ){
						//point not overlapped
						break;
					}
				}
				//set max area to last overlapped point
				itrActualLinePart->second.maxY = ((double)(lPositionDim1)) - 0.51;
			}//end for all part lines
		}//end if dimension switch
	}
	
	
	/**
	 * This function prints this line to the given stream.
	 *
	 * @param outputStream the stream, wher to print this line to
	 */
	void print( ostream & outputStream ) const{
		
		outputStream<<"line = "<<lLineDirectionCoordinateValue<<"; part lines: ";
		for ( tLineParts::const_iterator itrActualLinePart = lineParts.begin();
				itrActualLinePart != lineParts.end(); itrActualLinePart++ ){
			
			outputStream<<" max "<<itrActualLinePart->first.maxY<<
				" min "<<itrActualLinePart->first.minY<<" till"<<
				" min "<<itrActualLinePart->second.minY<<
				" max "<<itrActualLinePart->second.maxY<<" ;";
		}
		outputStream<<endl;
	}
	
	
};//end line cLine



/**
 * The straight border line for one fix coordinat area.
 * This is a helper class for:
 * 	@see cImageStructureConvertToTiles::convertToExtObjects()
 */
class cStraightBorderLine{
public:
	
	/**
	 * The coordinate wher the line starts.
	 * (smaaler than lLineEndPoint)
	 * @see lLineEndPoint
	 */
	long lLineStartPoint;
	
	/**
	 * The coordinate wher the line ends.
	 * (bigger than lLineStartPoint)
	 * @see lLineStartPoint
	 */
	long lLineEndPoint;
	
	/**
	 * The area, in which the line is.
	 * The values are for the other coordinate than lLineStartPoint and
	 * lLineEndPoint.
	 */
	pair< double, double > areaForLine;

#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
	/**
	 * The size of the area for the line.
	 * Number of points in the area to the line.
	 */
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
	/**
	 * The size of the line.
	 * lLineEndPoint - lLineStartPoint
	 */
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
	unsigned long size;
	
	/**
	 * parameter constructor
	 *
	 * @param lInLinePoint the start and end point for the line
	 * 	@see lLineStartPoint
	 * 	@see lLineEndPoint
	 * @param inAreaForLine the area, in which the line is
	 * 	@see areaForLine
	 */
	cStraightBorderLine( const longFib lInLinePoint,
			pair< double, double > inAreaForLine ):
			lLineStartPoint( lInLinePoint ), lLineEndPoint( lInLinePoint ),
			areaForLine( inAreaForLine ), size( 0 ){
		//nothing to do
	}
	
	
	/**
	 * @return true if this line is bigger than the the other line,
	 * 	else if the lines are the same size true if this line begins befor
	 * 	(lower) than the other line, else false
	 */
	bool operator<( const cStraightBorderLine & otherStraightBorderLine ){
		
		if ( otherStraightBorderLine.size < size ){
			return true;
		}
		if ( ( size == otherStraightBorderLine.size ) &&
				( lLineStartPoint < otherStraightBorderLine.lLineStartPoint ) ){
			return true;
		}
		return false;
	}
	
};//end class cStraightBorderLine


}}}}}}}//end namespaces





/**
 * standard constructor
 *
 * @param uiNumberOfSplineParameters the number of parameters for the
 * 	porder function
 * 	Beware: Just some values are valid
 * 	Valid values: 2, 3, 4
 * 	@see NUMBER_OF_SPLINE_PARAMETERS
 * @param dWeightFactor the factor of difference betwean the weigt factors
 * 	@see D_WEIGHT_FACTOR
 * @param bInReduceBitsForParameter if true, it will be tried to reduce
 * 	the number of bits for the parameter of the found splines
 * 	@see bReduceBitsForParameter
 */
cImageStructureConvertToTiles::cImageStructureConvertToTiles(
		unsigned int uiNumberOfSplineParameters,
		const double dWeightFactor,
			const bool bInReduceBitsForParameter ):
		D_WEIGHT_FACTOR( dWeightFactor ),
		bReduceBitsForParameter( bInReduceBitsForParameter ){
	//map uiNumberOfSplineParameters to valid value
	if ( uiNumberOfSplineParameters < 2 ){
		//value to smaal
		NUMBER_OF_SPLINE_PARAMETERS = 2;
	}else if ( 4 < uiNumberOfSplineParameters ){
		//value to great
		NUMBER_OF_SPLINE_PARAMETERS = 4;
	}else{//use given value
		NUMBER_OF_SPLINE_PARAMETERS = uiNumberOfSplineParameters;
	}
	//set the correct identifiers
	switch ( NUMBER_OF_SPLINE_PARAMETERS ){
		case 2:
			IDENTIFIER_SPLINE_OBJECT_XY = -702;
			IDENTIFIER_SPLINE_OBJECT_YX = -712;
			IDENTIFIER_SPLINE_OBJECT_AA_XY = -752;
			IDENTIFIER_SPLINE_OBJECT_AA_YX = -762;
		break;
		case 3:
			IDENTIFIER_SPLINE_OBJECT_XY = -70;
			IDENTIFIER_SPLINE_OBJECT_YX = -71;
			IDENTIFIER_SPLINE_OBJECT_AA_XY = -85;
			IDENTIFIER_SPLINE_OBJECT_AA_YX = -86;
		break;
		case 4:
			IDENTIFIER_SPLINE_OBJECT_XY = -72;
			IDENTIFIER_SPLINE_OBJECT_YX = -73;
			IDENTIFIER_SPLINE_OBJECT_AA_XY = -87;
			IDENTIFIER_SPLINE_OBJECT_AA_YX = -88;
		break;
		//TODO more cases
		
	}
}

/**
 * copy constructor
 *
 * @param imageStructureConvertToTiles the cImageStructureConvertToTiles
 * 	object to copy
 */
cImageStructureConvertToTiles::cImageStructureConvertToTiles(
		const cImageStructureConvertToTiles & imageStructureConvertToTiles ):
		NUMBER_OF_SPLINE_PARAMETERS( imageStructureConvertToTiles.NUMBER_OF_SPLINE_PARAMETERS ),
		IDENTIFIER_SPLINE_OBJECT_XY( imageStructureConvertToTiles.IDENTIFIER_SPLINE_OBJECT_XY ),
		IDENTIFIER_SPLINE_OBJECT_YX( imageStructureConvertToTiles.IDENTIFIER_SPLINE_OBJECT_YX ),
		IDENTIFIER_SPLINE_OBJECT_AA_XY( imageStructureConvertToTiles.IDENTIFIER_SPLINE_OBJECT_AA_XY ),
		IDENTIFIER_SPLINE_OBJECT_AA_YX( imageStructureConvertToTiles.IDENTIFIER_SPLINE_OBJECT_AA_YX ),
		D_WEIGHT_FACTOR( imageStructureConvertToTiles.D_WEIGHT_FACTOR ),
		bReduceBitsForParameter( imageStructureConvertToTiles.bReduceBitsForParameter ){
	//nothing to do
}


/**
 * destructor
 */
cImageStructureConvertToTiles::~cImageStructureConvertToTiles(){
	//nothing to do
}


/**
 * This method clones this strategy object.
 *
 * @return a clone of this strategie object
 */
cImageStructureConvertToTiles * cImageStructureConvertToTiles::clone() const{
	
	return new cImageStructureConvertToTiles( *this );
}


/**
 * This method converts this cImageStructure to tiles and return ther data.
 * The points of the area are (positiv) integer coordinates.
 * The generated external objects will have no subobjects and are from
 * the Fib database.
 * Beware: You have to check for antialising with isAntialised().
 * 	(If antialised add to tile external object identifer -10 .)
 *
 * @param structurePoints the set with the point of the area to convert
 * @param pImageSearchData a pointer to the image search data of found
 * 	image parts, which will overwrite tile parts
 * 	(the tiles can be bigger, because some parts of them won't be seen)
 * @param bIsAntialised if true the converted area should be antialised,
 * 	(the generated external objects should be for antialising), else
 * 	the area should not be antialised
 * @param maxValue the maximum possible value in all parameters,
 * 	the evalued spline/function values for the tile will allways have
 * 	value parameters with
 * 	-1 * maxValue <= vecFactors[i] <= maxValue for 0 <= i \< 3;
 * 	if 0 (standard value) is given, the maximum possible value will
 * 	be evalued from the given data (absolute maximum in given data * 256)
 * @param maxErrorPerValue the maximal error for the border polynoms to
 * 	find on one border point; the error on the interpolated polynom
 * 	for every border point in vecData will be equal or less than
 * 	maxErrorPerValue;
 * @return a list with the data for the tiles as external object elements
 * 	from the database with the identifier -70 or -71;
 * 	Beware you have to delete the returned cExtObject's.
 */
list< cExtObject * > cImageStructureConvertToTiles::convertToExtObjects(
		const set<cVectorPosition> & structurePoints,
		const cImageSearchData * pImageSearchData,
		const bool bIsAntialised,
		double maxValue,
		const double maxErrorPerValue ) const{
	
	DEBUG_OUT_L2(<<"cImageStructureConvertToTiles("<<this<<")::convertToExtObjects( pImageSearchData, maxValue="<<maxValue<<", maxErrorPerValue="<<maxErrorPerValue<<" ) started"<<endl<<flush);
	
	if ( maxValue < 0.0 ){
		//can't create spline with negativ maximum value
		DEBUG_OUT_EL2(<<"cImageStructureConvertToTiles("<<this<<")::convertToExtObjects() done: can't create spline with negativ maximum value"<<endl<<flush);
		return list< cExtObject * >();
	}//else
	if ( maxValue == 0.0 ){
		//evaluing maximum value
		for ( set<cVectorPosition>::const_iterator
				itrActualPoint = structurePoints.begin();
				itrActualPoint != structurePoints.end(); itrActualPoint++ ){
			//for all points in area
			maxValue = max( maxValue, abs( itrActualPoint->getValue( 1 ) ) );
			maxValue = max( maxValue, abs( itrActualPoint->getValue( 2 ) ) );
		}
		maxValue *= 256.0;
		DEBUG_OUT_L2(<<"maximum value (maxValue) evalued to: "<<maxValue<<endl<<flush);
	}
	//the weight parameters for the to generate polynom (factors)
	list< double > liWeightParameters;
	
	double dActualWeightValue = D_WEIGHT_FACTOR;
	for ( unsigned int uiActualParameterWeight = 1;
			uiActualParameterWeight < NUMBER_OF_SPLINE_PARAMETERS;
			uiActualParameterWeight++, dActualWeightValue *= D_WEIGHT_FACTOR ){
	
		liWeightParameters.push_front( dActualWeightValue );
	}
	//set parameter for the constant factor
	liWeightParameters.push_front( 0.0 );
	
	//evalue minimum and maximum borders of area in both directions
	/*The map with the borders of the areas.
	 * The elements are:
	 * 	- key: the coordinate of the line in dimension 1
	 * 	- value: the line for the key coordinate value @see cLine
	 */
	map< longFib, nImageStructureConvertToTiles::cLine > bordersDim1;
	map< longFib, nImageStructureConvertToTiles::cLine > bordersDim2;

	//evalue the borders for the points
	DEBUG_OUT_L2(<<"evalue the borders for the points"<<endl<<flush);
	map< longFib, nImageStructureConvertToTiles::cLine >::iterator
		itrActualLineDim1 = bordersDim1.begin();
	map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim2 = bordersDim2.begin();
	for ( set<cVectorPosition>::const_iterator
			itrActualPoint = structurePoints.begin();
			itrActualPoint != structurePoints.end(); itrActualPoint++ ){
		//for all points in area: add to minimum line parts
		//add actual point for dimension 1
		const longFib lActualDim1Value =
			roundToLongFib( itrActualPoint->getValue( 1 ) );
		const longFib lActualDim2Value =
			roundToLongFib( itrActualPoint->getValue( 2 ) );
		
		//find actual line in dimension 1
		//remember old itrActualLineDim1 and check if it could be used again
		if ( ( itrActualLineDim1 == bordersDim1.end() ) ||
				( itrActualLineDim1->first != lActualDim1Value ) ){
			//old line could not be used -> search for line
			itrActualLineDim1 = bordersDim1.find( lActualDim1Value );
		}
		//add point
		if ( itrActualLineDim1 != bordersDim1.end() ){
			//line found
			itrActualLineDim1->second.addPoint( lActualDim2Value );
		}else{//line not found -> create new line and add it
			nImageStructureConvertToTiles::cLine newLine( lActualDim1Value );
			newLine.addPoint( lActualDim2Value );
			bordersDim1.insert( make_pair( lActualDim1Value, newLine ) );
			itrActualLineDim1 = bordersDim1.end();
		}
		//add actual point for dimension 2
		//find actual line in dimension 2
		//remember old itrActualLineDim2 and check if it could be used again
		if ( itrActualLineDim2 == bordersDim2.end() ){
			//old line could not be used -> search for line
			itrActualLineDim2 = bordersDim2.find( lActualDim2Value );
			
		}else if ( itrActualLineDim2->first != lActualDim2Value ){
			itrActualLineDim2++;
			if ( ( itrActualLineDim2 == bordersDim2.end() ) ||
					( itrActualLineDim2->first != lActualDim2Value ) ){
				//old line or next to it line could not be used -> search for line
				itrActualLineDim2 = bordersDim2.find( lActualDim2Value );
			}
		}
		//add point
		if ( itrActualLineDim2 != bordersDim2.end() ){
			//line found
			itrActualLineDim2->second.addPoint( lActualDim1Value );
		}else{//line not found -> create new line and add it
			nImageStructureConvertToTiles::cLine newLine( lActualDim2Value );
			newLine.addPoint( lActualDim1Value );
			bordersDim2.insert( make_pair( lActualDim2Value, newLine ) );
			itrActualLineDim2 = bordersDim2.end();
		}
		
#ifdef DEBUG_ADDING_POINTS
		cout<<endl<<"Adding point to line parts ("<<lActualDim1Value<<", "<<lActualDim2Value<<")"<<endl<<flush;
		
		cout<<endl<<"New area for dimension 1:"<<endl;
		for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim1 = bordersDim1.begin();
				itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
			
			itrActualLineDim1->second.print( cout );
		}
		cout<<endl<<"New area for dimension 2:"<<endl;
		for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim2 = bordersDim2.begin();
				itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
			
			itrActualLineDim2->second.print( cout );
		}
		cout<<endl;
#endif //DEBUG_ADDING_POINTS
	}
	//for all line parts: set maximum to minimum
#ifdef DEBUG
	cout<<endl<<"Area for dimension 1:"<<endl;
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim1 = bordersDim1.begin();
			itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
		
		itrActualLineDim1->second.print( cout );
	}
	cout<<endl<<"Area for dimension 2:"<<endl;
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim2 = bordersDim2.begin();
			itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
		
		itrActualLineDim2->second.print( cout );
	}
	cout<<endl;
#endif //DEBUG
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
	//evalue dimensions of area (for cEvaluePositionListLimit)
	cDomainNaturalNumber domDimension1( bordersDim1.rbegin()->first + 10 );
	cDomainNaturalNumber domDimension2( bordersDim2.rbegin()->first + 10 );
	vector<cDomainSingle*> vecDomainsDim;
	vecDomainsDim.push_back( &domDimension1 );
	vecDomainsDim.push_back( &domDimension2 );
	
	cDomainVector vecDomainDimension( vecDomainsDim );
	DEBUG_OUT_L2(<<"evalue just in dimensions till max ("<<(bordersDim1.rbegin()->first + 10)<<", "<<(bordersDim2.rbegin()->first + 10)<<" )"<<endl<<flush);
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
	DEBUG_OUT_L2(<<"for all line parts: set maximum to minimum"<<endl<<flush);
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim1 = bordersDim1.begin();
			itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
		
		itrActualLineDim1->second.adaptAllMaxToMinValue();
	}
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim2 = bordersDim2.begin();
			itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
		
		itrActualLineDim2->second.adaptAllMaxToMinValue();
	}
	/* for every line part: check if the points neibours to it wher allready found:
	 * if yes add them to maximum line parts */
#ifdef DEBUG
	cout<<endl<<"Area for dimension 1:"<<endl;
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim1 = bordersDim1.begin();
			itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
		
		itrActualLineDim1->second.print( cout );
	}
	cout<<endl<<"Area for dimension 2:"<<endl;
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim2 = bordersDim2.begin();
			itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
		
		itrActualLineDim2->second.print( cout );
	}
	cout<<endl;
#endif //DEBUG
	DEBUG_OUT_L2(<<"for ever line part: check if the points neibours to it wher allready found"<<endl<<flush);
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim1 = bordersDim1.begin();
			itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
		
		itrActualLineDim1->second.enlargeMaxForSearchData(
			1, pImageSearchData, 0 - maxValue );
	}
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim2 = bordersDim2.begin();
			itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
		
		itrActualLineDim2->second.enlargeMaxForSearchData(
			2, pImageSearchData, 0 - maxValue );
	}
	
	//the minimum number of lines for an tile area to create
	unsigned long ulMinGoodStraightLineSize = min( min( bordersDim1.size(), bordersDim2.size() ) / 2 + 1,
		1024UL );
	
	/*parameter needed for the cPolynom::evalueSplineIterativFast() method
	-> set to possible maximum*/
	const double maxError = ( maxErrorPerValue == 0 )? 0 :
		maxErrorPerValue * structurePoints.size();
	
	list< cExtObject * > liFoundTiles;
	
	//while not whool area was found
	while ( ! bordersDim1.empty() ){
	
		/*evalue longesed straight coordinate line betwean min and max of two
		 *line part borders in dim 1*/
		
		//the list with straight border lines of the area in dimension 1 from the area top
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightBorderLinesDim1Top;
		/*the list with the straight border lines still to enlarge;
		the border lines with the smaaler areaForLine start point (first) at the front*/
		list< nImageStructureConvertToTiles::cStraightBorderLine * >
			liStraightBorderLinesToEnlarge;
		//the value of the last created straight border line
		double dLastBorderValue = bordersDim1.begin()->second.
			lineParts.front().second.maxY + 1.0;
		/*the value the following line should have (if not ther is a space
		 * betwean actual and next line)*/
		longFib lNextLineValue = bordersDim1.begin()->first;
		
#ifdef DEBUG
		cout<<endl<<"Area for dimension 1:"<<endl;
		for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim1 = bordersDim1.begin();
				itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
			
			itrActualLineDim1->second.print( cout );
		}
		cout<<endl<<"Area for dimension 2:"<<endl;
		for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim2 = bordersDim2.begin();
				itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
			
			itrActualLineDim2->second.print( cout );
		}
		cout<<endl;
#endif //DEBUG
		DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 left up betwean min and max of a border in dim 2 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
		for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim1 = bordersDim1.begin();
				itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
			
			DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
			/*from first line in dimension till min in other dimension is reached:
				- create new border line for min in other dimension
					if last created border line was for area bigger values in
					other dimension (else break)*/
			
			const nImageStructureConvertToTiles::cLine::tLineParts &
				actualLine = itrActualLineDim1->second.lineParts;
			
			if ( lNextLineValue != itrActualLineDim1->first ){
				//missing line in the dimension -> stop enlarging border lines
				liStraightBorderLinesToEnlarge.clear();
			}
			lNextLineValue = itrActualLineDim1->first + 1;
			
			//first to enlarge line, remember it and add new lines befor it
			list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
				itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
			
			nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
				itrActualLinePart = actualLine.begin();
			
			DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
			if ( ! actualLine.empty() ){
				//for first line part -> check if to create new border line for it
				if ( itrActualLinePart->second.minY < dLastBorderValue ){
					/*last created border line was for area bigger values in
						other dimension (or if no border line exists for the line
						part begin)*/
					liStraightBorderLinesDim1Top.push_back(
						nImageStructureConvertToTiles::cStraightBorderLine(
							itrActualLineDim1->first,
							make_pair( itrActualLinePart->second.minY,
								itrActualLinePart->second.maxY ) ) );
						
					liStraightBorderLinesToEnlarge.push_front(
						& liStraightBorderLinesDim1Top.back() );
					
					dLastBorderValue = itrActualLinePart->second.minY;
					DEBUG_OUT_L3(<<"new border line created for higher border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
				}
				if ( itrActualLinePart->first.minY < dLastBorderValue ){
					/*last created border line was for area bigger values in
						other dimension (or if no border line exists for the line
						part begin)*/
					liStraightBorderLinesDim1Top.push_back(
						nImageStructureConvertToTiles::cStraightBorderLine(
							itrActualLineDim1->first,
							make_pair( itrActualLinePart->first.maxY,
								itrActualLinePart->first.minY ) ) );
						
					liStraightBorderLinesToEnlarge.push_front(
						& liStraightBorderLinesDim1Top.back() );
					
					dLastBorderValue = itrActualLinePart->first.minY;
					DEBUG_OUT_L3(<<"new border line created for lower border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
				}
			}
			
			//enlarge border lines
			DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
			for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
				
				while ( itrActualToEnlargeBorderLine !=
						liStraightBorderLinesToEnlarge.end() ){
					
					const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
					const double & dLinePartBeginMax = itrActualLinePart->first.minY;
					DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
					{
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
									( dLinePartBeginMin <= dBorderLineMax ) ) || //all line part in border line
								( ( dLinePartBeginMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartBeginMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartBeginMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
					}
					
					const double & dLinePartEndMin = itrActualLinePart->second.minY;
					const double & dLinePartEndMax = itrActualLinePart->second.maxY;
					DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
					
					double & dBorderLineMin =
						(*itrActualToEnlargeBorderLine)->areaForLine.first;
					double & dBorderLineMax =
						(*itrActualToEnlargeBorderLine)->areaForLine.second;
				
					if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
								( dLinePartEndMin <= dBorderLineMax ) ) || //all line part in border line
							( ( dLinePartEndMin <= dBorderLineMin ) &&
								( dBorderLineMin <= dLinePartEndMax ) ) ||
							( ( dLinePartEndMin <= dBorderLineMax ) &&
								( dBorderLineMax <= dLinePartEndMax ) ) ){
						//enlarge border line
						DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
						((*itrActualToEnlargeBorderLine)->size) +=
							itrActualLinePart->second.minY - itrActualLinePart->first.minY;
						((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
						((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
						((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
							itrActualLineDim1->first;
						
						dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
						dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
						
						itrActualToEnlargeBorderLine++;
						continue;
					}//else
					
					if ( dLinePartEndMax < dBorderLineMin ){
						//border line after line part -> skip line part -> next line part
						break;
					}/*else next border line (border line befor or betwean
					min and min of line part)*/
					/*don't enlarge border line ->
					remove border line from to enlarge border lines*/
					DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
					
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
						itrActualToEnlargeBorderLine );
				}//end while not all border lines checked
				//if no border line to enlarge -> break
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//stop at this line
					DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
					break;
				}
			}//end for all remaining part lines
			//erase all remaining not enlarged straight border lines from enlarge list
			while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
				itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
						itrActualToEnlargeBorderLine );
			}
			
			if ( liStraightBorderLinesToEnlarge.empty() ){
				//if no border line to enlarged or crated -> break
				DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
				break;
			}
		}
		//remove border lines from to enlarge border lines
		DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
		liStraightBorderLinesToEnlarge.clear();
		DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
		liStraightBorderLinesDim1Top.sort();
		
		bool bFindMoreBorderLines = true;
		if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim1Top.front().size ){
			//good border line allready found
			bFindMoreBorderLines = false;
		}
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.begin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim1.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 right up betwean min and max of a border in dim 2 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim1 = bordersDim1.begin();
					itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till max in other dimension is reached:
					- create new border line for max in other dimension
						if last created border line was for area lower values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first + 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->first.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim1Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim1Top.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
					if ( dLastBorderValue < itrActualLinePart->second.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim1Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim1Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
						
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
							
							if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
										( dLinePartEndMin <= dBorderLineMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartEndMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartEndMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
								
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim1->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
									( dLinePartBeginMin <= dBorderLineMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartBeginMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartBeginMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartBeginMax ){
							//border line befor line part -> skip line part -> next line part
							break;
						}/*else next border line (border line after or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim1Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim1Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		//the list with straight border lines of the area in dimension 1 from bottom
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightBorderLinesDim1Bottom;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.rbegin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim1.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 left down betwean min and max of a border in dim 2 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim1 = bordersDim1.rbegin();
					itrActualLineDim1 != bordersDim1.rend(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first - 1;
			
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.minY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim1Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim1Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for higher border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
					if ( itrActualLinePart->first.minY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim1Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim1Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for lower border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
						
							if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
										( dLinePartBeginMin <= dBorderLineMax ) ) ||
									( ( dLinePartBeginMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartBeginMax ) ) ||
									( ( dLinePartBeginMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartBeginMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
							
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim1->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
									( dLinePartEndMin <= dBorderLineMax ) ) ||
								( ( dLinePartEndMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartEndMax ) ) ||
								( ( dLinePartEndMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartEndMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
							
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dLinePartEndMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}/*else next border line (border line befor or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}//end for all lines
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim1Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim1Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.rbegin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim1.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 right down betwean min and max of a border in dim 2 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim1 = bordersDim1.rbegin();
					itrActualLineDim1 != bordersDim1.rend(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till max in other dimension is reached:
					- create new border line for max in other dimension
						if last created border line was for area lower values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first - 1;
			
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->first.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim1Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim1Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
					if ( dLastBorderValue < itrActualLinePart->second.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the
							line part begin)*/
						liStraightBorderLinesDim1Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim1Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
					
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
						
							if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
										( dLinePartEndMin <= dBorderLineMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartEndMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartEndMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
								
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim1->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
									( dLinePartBeginMin <= dBorderLineMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartBeginMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartBeginMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartBeginMax ){
							//border line befor line part -> skip line part -> next line part
							break;
						}/*else next border line (border line after or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim1Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim1Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		//evalue longesed straight coordinate line betwean min and max of two line part borders in dim 2
		
		//the list with straight border lines of the area
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightBorderLinesDim2Top;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.begin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim2.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 left up betwean min and max of a border in dim 1 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim2 = bordersDim2.begin();
					itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first + 1;
			
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.minY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
					if ( itrActualLinePart->first.minY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Top.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
						
							if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
										( dLinePartBeginMin <= dBorderLineMax ) ) ||
									( ( dLinePartBeginMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartBeginMax ) ) ||
									( ( dLinePartBeginMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartBeginMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
							
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim2->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
									( dLinePartEndMin <= dBorderLineMax ) ) ||
								( ( dLinePartEndMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartEndMax ) ) ||
								( ( dLinePartEndMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartEndMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
							
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dLinePartEndMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}/*else next border line (border line befor or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim2Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim2Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.begin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim2.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 right up betwean min and max of a border in dim 1 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim2 = bordersDim2.begin();
					itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till max in other dimension is reached:
					- create new border line for max in other dimension
						if last created border line was for area lower values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first + 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->first.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Top.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
					if ( dLastBorderValue < itrActualLinePart->second.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
					
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
						
							if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
										( dLinePartEndMin <= dBorderLineMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartEndMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartEndMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
								
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim2->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
									( dLinePartBeginMin <= dBorderLineMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartBeginMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartBeginMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartBeginMax ){
							//border line befor line part -> skip line part -> next line part
							break;
						}/*else next border line (border line after or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim2Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim2Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		//the list with straight border lines of the area
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightBorderLinesDim2Bottom;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.rbegin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim2.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 left down betwean min and max of a border in dim 1 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim2 = bordersDim2.rbegin();
					itrActualLineDim2 != bordersDim2.rend(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first - 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.minY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
					if ( itrActualLinePart->first.minY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
						
							if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
										( dLinePartBeginMin <= dBorderLineMax ) ) ||
									( ( dLinePartBeginMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartBeginMax ) ) ||
									( ( dLinePartBeginMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartBeginMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
							
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim2->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
									( dLinePartEndMin <= dBorderLineMax ) ) ||
								( ( dLinePartEndMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartEndMax ) ) ||
								( ( dLinePartEndMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartEndMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
							
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dLinePartEndMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}/*else next border line (border line befor or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim2Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim2Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.rbegin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim2.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 right down betwean min and max of a border in dim 1 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim2 = bordersDim2.rbegin();
					itrActualLineDim2 != bordersDim2.rend(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till max in other dimension is reached:
					- create new border line for max in other dimension
						if last created border line was for area lower values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first - 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->first.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->first.minY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->first.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.minY<<" to "<<itrActualLinePart->first.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; first)"<<endl<<flush);
					}
					if ( dLastBorderValue < itrActualLinePart->second.minY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightBorderLinesDim2Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->second.minY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightBorderLinesDim2Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.minY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->second.minY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<"; second)"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartEndMin = itrActualLinePart->second.minY;
						const double & dLinePartEndMax = itrActualLinePart->second.maxY;
					
						DEBUG_OUT_L4(<<"enlarge border line? line part end from "<<dLinePartEndMin<<" to "<<dLinePartEndMax<<endl<<flush);
						{
							double & dBorderLineMin =
								(*itrActualToEnlargeBorderLine)->areaForLine.first;
							double & dBorderLineMax =
								(*itrActualToEnlargeBorderLine)->areaForLine.second;
						
							if ( ( ( dBorderLineMin <= dLinePartEndMin ) &&
										( dLinePartEndMin <= dBorderLineMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMin ) &&
										( dBorderLineMin <= dLinePartEndMax ) ) ||
									( ( dLinePartEndMin <= dBorderLineMax ) &&
										( dBorderLineMax <= dLinePartEndMax ) ) ){
								//enlarge border line
								DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartEndMin )<<" to "<<min( dBorderLineMax, dLinePartEndMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
								
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size) +=
									itrActualLinePart->second.minY - itrActualLinePart->first.minY;
								((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
								((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
									itrActualLineDim2->first;
								
								dBorderLineMin = max( dBorderLineMin, dLinePartEndMin );
								dBorderLineMax = min( dBorderLineMax, dLinePartEndMax );
								
								itrActualToEnlargeBorderLine++;
								continue;
							}//else
						}
						
						const double & dLinePartBeginMin = itrActualLinePart->first.maxY;
						const double & dLinePartBeginMax = itrActualLinePart->first.minY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartBeginMin<<" to "<<dLinePartBeginMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartBeginMin ) &&
									( dLinePartBeginMin <= dBorderLineMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartBeginMax ) ) ||
								( ( dLinePartBeginMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartBeginMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartBeginMin )<<" to "<<min( dBorderLineMax, dLinePartBeginMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartBeginMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartBeginMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartBeginMax ){
							//border line befor line part -> skip line part -> next line part
							break;
						}/*else next border line (border line after or betwean
						min and min of line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightBorderLinesDim2Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightBorderLinesDim2Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
	//evalue longesed straight coordinate line betwean max and max of two line part borders in dim 1
		//the list with straight border lines of the area
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightAreaLinesDim1Top;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.begin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim1.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 left up betwean max and max of a border in dim 2 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim1 = bordersDim1.begin();
					itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first + 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.maxY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim1Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim1Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dLinePartMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}/*else next border line (border line befor line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim1Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim1Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.begin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim1.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 right up betwean max and max of a border in dim 2 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim1 = bordersDim1.begin();
					itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till max in other dimension is reached:
					- create new border line for max in other dimension
						if last created border line was for area smaaler values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first + 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->second.maxY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim1Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim1Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartMin ){
							//border line befor line part -> skip line part -> next line part
							break;
						}//else next border line (border line after line part)
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim1Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim1Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
		//the list with straight border lines of the area
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightAreaLinesDim1Bottom;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.rbegin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim1.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 left down betwean max and max of a border in dim 2 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim1 = bordersDim1.rbegin();
					itrActualLineDim1 != bordersDim1.rend(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first - 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.maxY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim1Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim1Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dLinePartMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}/*else next border line (border line befor line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim1Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim1Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim1.rbegin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim1.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 1 right down betwean max and max of a border in dim 2 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim1 = bordersDim1.rbegin();
					itrActualLineDim1 != bordersDim1.rend(); itrActualLineDim1++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim1->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till min in other dimension is reached:
					- create new border line for max in other dimension
						if last created border line was for area of smaaler values
						in other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim1->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim1->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim1->first - 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->second.maxY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim1Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim1->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim1Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim1->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartMin ){
							//border line befor line part -> skip line part -> next line part
							break;
						}//else next border line (border line after line part)
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim1Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim1Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
		
		//the list with straight border lines of the area
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightAreaLinesDim2Top;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.begin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim2.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 left up betwean max and max of a border in dim 1 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim2 = bordersDim2.begin();
					itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first + 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.maxY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim2Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim2Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}
						
						if ( dLinePartMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}/*else next border line (border line befor line part)*/
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim2Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim2Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.begin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim2.begin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 right up betwean max and max of a border in dim 1 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim2 = bordersDim2.begin();
					itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from first line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area smaaler values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first + 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->second.maxY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim2Top.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim2Top.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartMin ){
							//border line befor line part -> skip line part -> next line part
							break;
						}//else next border line (border line after line part)
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim2Top.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim2Top.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
		//the list with straight border lines of the area
		list< nImageStructureConvertToTiles::cStraightBorderLine >
			liStraightAreaLinesDim2Bottom;
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.rbegin()->second.
				lineParts.front().second.maxY + 1.0;
			lNextLineValue = bordersDim2.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 left down betwean max and max of a border in dim 1 (first border value + 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim2 = bordersDim2.rbegin();
					itrActualLineDim2 != bordersDim2.rend(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first - 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualLinePart = actualLine.begin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( itrActualLinePart->second.maxY < dLastBorderValue ){
						/*last created border line was for area bigger values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim2Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim2Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.end(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dLinePartMax < dBorderLineMin ){
							//border line after line part -> skip line part -> next line part
							break;
						}//else next border line (border line befor line part)
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim2Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim2Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		
		if ( bFindMoreBorderLines ){
			
			dLastBorderValue = bordersDim2.rbegin()->second.
				lineParts.back().first.maxY - 1.0;
			lNextLineValue = bordersDim2.rbegin()->first;
			
			DEBUG_OUT_L2(<<"evalue longesed straight coordinate line of area in dim 2 right down betwean max and max of a border in dim 1 (first border value - 1="<<dLastBorderValue<<")"<<endl<<flush);
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::reverse_iterator
					itrActualLineDim2 = bordersDim2.rbegin();
					itrActualLineDim2 != bordersDim2.rend(); itrActualLineDim2++ ){
				
				DEBUG_OUT_L2(<<"evalue next area line on coordinate "<<itrActualLineDim2->first<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
				/*from last line in dimension till min in other dimension is reached:
					- create new border line for min in other dimension
						if last created border line was for area bigger values in
						other dimension (else break)*/
				
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLineDim2->second.lineParts;
				
				if ( lNextLineValue != itrActualLineDim2->first ){
					//missing line in the dimension -> stop enlarging border lines
					liStraightBorderLinesToEnlarge.clear();
				}
				lNextLineValue = itrActualLineDim2->first - 1;
				
				//first to enlarge line, remember it and add new lines befor it
				list< nImageStructureConvertToTiles::cStraightBorderLine * >::iterator
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.begin();
				
				nImageStructureConvertToTiles::cLine::tLineParts::const_reverse_iterator
					itrActualLinePart = actualLine.rbegin();
				
				DEBUG_OUT_L2(<<"for first line part -> check if to create new border lines for it"<<endl<<flush);
				if ( ! actualLine.empty() ){
					//for first line part -> check if to create new border line for it
					if ( dLastBorderValue < itrActualLinePart->second.maxY ){
						/*last created border line was for area smaaler values in
							other dimension (or if no border line exists for the line
							part begin)*/
						liStraightAreaLinesDim2Bottom.push_back(
							nImageStructureConvertToTiles::cStraightBorderLine(
								itrActualLineDim2->first,
								make_pair( itrActualLinePart->first.maxY,
									itrActualLinePart->second.maxY ) ) );
							
						liStraightBorderLinesToEnlarge.push_front(
							& liStraightAreaLinesDim2Bottom.back() );
						
						dLastBorderValue = itrActualLinePart->second.maxY;
						DEBUG_OUT_L3(<<"new border line created for border from "<<itrActualLinePart->first.maxY<<" to "<<itrActualLinePart->second.maxY<<" (dLastBorderValue="<<dLastBorderValue<<")"<<endl<<flush);
					}
				}
				
				//enlarge border lines
				DEBUG_OUT_L2(<<"enlarge remaining border lines"<<endl<<flush);
				for ( ; itrActualLinePart != actualLine.rend(); itrActualLinePart++ ){
					
					while ( itrActualToEnlargeBorderLine !=
							liStraightBorderLinesToEnlarge.end() ){
						
						const double & dLinePartMin = itrActualLinePart->first.maxY;
						const double & dLinePartMax = itrActualLinePart->second.maxY;
						DEBUG_OUT_L4(<<"enlarge border line? line part begin from "<<dLinePartMin<<" to "<<dLinePartMax<<endl<<flush);
						
						double & dBorderLineMin =
							(*itrActualToEnlargeBorderLine)->areaForLine.first;
						double & dBorderLineMax =
							(*itrActualToEnlargeBorderLine)->areaForLine.second;
					
						if ( ( ( dBorderLineMin <= dLinePartMin ) &&
									( dLinePartMin <= dBorderLineMax ) ) ||
								( ( dLinePartMin <= dBorderLineMin ) &&
									( dBorderLineMin <= dLinePartMax ) ) ||
								( ( dLinePartMin <= dBorderLineMax ) &&
									( dBorderLineMax <= dLinePartMax ) ) ){
							//enlarge border line
							DEBUG_OUT_L4(<<"enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<" (new from "<<max( dBorderLineMin, dLinePartMin )<<" to "<<min( dBorderLineMax, dLinePartMax )<<" size "<<((*itrActualToEnlargeBorderLine)->size)<<")"<<endl<<flush);
						
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size) +=
								itrActualLinePart->second.minY - itrActualLinePart->first.minY;
							((*itrActualToEnlargeBorderLine)->size)++;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->size)++;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
							((*itrActualToEnlargeBorderLine)->lLineEndPoint) =
								itrActualLineDim2->first;
							
							dBorderLineMin = max( dBorderLineMin, dLinePartMin );
							dBorderLineMax = min( dBorderLineMax, dLinePartMax );
							
							itrActualToEnlargeBorderLine++;
							continue;
						}//else
						
						if ( dBorderLineMax < dLinePartMin ){
							//border line befor line part -> skip line part -> next line part
							break;
						}//else next border line (border line after line part)
						/*don't enlarge border line ->
						remove border line from to enlarge border lines*/
						DEBUG_OUT_L3(<<"don't enlarge border line from "<<dBorderLineMin<<" to "<<dBorderLineMax<<", but end it"<<endl<<flush);
						
						itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
					}//end while not all border lines checked
					//if no border line to enlarge -> break
					if ( liStraightBorderLinesToEnlarge.empty() ){
						//stop at this line
						DEBUG_OUT_L2(<<"no border line to enlarge -> break evalue next area line part"<<endl<<flush);
						break;
					}
				}//end for all remaining part lines
				//erase all remaining not enlarged straight border lines from enlarge list
				while ( itrActualToEnlargeBorderLine != liStraightBorderLinesToEnlarge.end() ){
					itrActualToEnlargeBorderLine = liStraightBorderLinesToEnlarge.erase(
							itrActualToEnlargeBorderLine );
				}
				if ( liStraightBorderLinesToEnlarge.empty() ){
					//if no border line to enlarged or crated -> break
					DEBUG_OUT_L2(<<"no border line to enlarged or crated -> break evalue next area line"<<endl<<flush);
					break;
				}
			}
			//remove border lines from to enlarge border lines
			DEBUG_OUT_L2(<<"remove border lines from to enlarge border lines"<<endl<<flush);
			liStraightBorderLinesToEnlarge.clear();
			DEBUG_OUT_L2(<<"sort border lines for dimension"<<endl<<flush);
			liStraightAreaLinesDim2Bottom.sort();
			
			if ( ulMinGoodStraightLineSize <= liStraightAreaLinesDim2Bottom.front().size ){
				//good border line allready found
				bFindMoreBorderLines = false;
			}
		}
		
		//evalue which of the evalued straight lines is the best
		
		/*always prefer dim 1 over dim 2 and from min to max over from max to max
		order to prefer:
			liStraightBorderLinesDim1Top
			liStraightBorderLinesDim1Bottom
			liStraightBorderLinesDim2Top
			liStraightBorderLinesDim2Bottom
			
			liStraightAreaLinesDim1Top
			liStraightAreaLinesDim1Bottom
			liStraightAreaLinesDim2Top
			liStraightAreaLinesDim2Bottom
		*/
		nImageStructureConvertToTiles::cStraightBorderLine * pBestLineBorderLine = NULL;
		bool bStraightBorderLineInDim1 = true;
		
		if ( ! liStraightBorderLinesDim1Top.empty() ){
			
			DEBUG_OUT_L2(<<"setting best border line of dim 1 top with size: "<<liStraightBorderLinesDim1Top.front().size<<endl<<flush);
			pBestLineBorderLine = &liStraightBorderLinesDim1Top.front();
		}
		if ( ! liStraightBorderLinesDim1Bottom.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( pBestLineBorderLine->size < liStraightBorderLinesDim1Bottom.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best border line of dim 1 bottom with size: "<<liStraightBorderLinesDim1Bottom.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightBorderLinesDim1Bottom.front();
			}
		}
		//the next best line of dim 2 should be so much better than the actual found line
		const double dImproveFactorDim2 = 1.5;
		
		if ( ! liStraightBorderLinesDim2Top.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( ( pBestLineBorderLine->size * dImproveFactorDim2 ) <
						liStraightBorderLinesDim2Top.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best border line of dim 2 top with size: "<<liStraightBorderLinesDim2Top.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightBorderLinesDim2Top.front();
				bStraightBorderLineInDim1 = false;
			}
		}
		if ( ! liStraightBorderLinesDim2Bottom.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( ( pBestLineBorderLine->size * dImproveFactorDim2 ) <
						liStraightBorderLinesDim2Bottom.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best border line of dim 2 bottom with size: "<<liStraightBorderLinesDim2Bottom.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightBorderLinesDim2Bottom.front();
				bStraightBorderLineInDim1 = false;
			}
		}
		
		//the next best line from max to max should be so much better than the actual found line
		const double dImproveFactorMaxMax = 4.0;
		bool bStraightBorderLineFromMinToMax = true;
		
		if ( ! liStraightAreaLinesDim1Top.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( ( pBestLineBorderLine->size * dImproveFactorMaxMax )  <
						liStraightAreaLinesDim1Top.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best in area line of dim 1 top with size: "<<liStraightAreaLinesDim1Top.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightAreaLinesDim1Top.front();
				bStraightBorderLineInDim1 = true;
				bStraightBorderLineFromMinToMax = false;
			}
		}
		if ( ! liStraightAreaLinesDim1Bottom.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( ( pBestLineBorderLine->size * dImproveFactorMaxMax ) <
						liStraightAreaLinesDim1Bottom.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best in area line of dim 1 bottom with size: "<<liStraightAreaLinesDim1Bottom.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightAreaLinesDim1Bottom.front();
				bStraightBorderLineInDim1 = true;
				bStraightBorderLineFromMinToMax = false;
			}
		}
		
		if ( ! liStraightAreaLinesDim2Top.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( ( pBestLineBorderLine->size * dImproveFactorMaxMax * dImproveFactorDim2 ) <
						liStraightAreaLinesDim2Top.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best in area line of dim 2 top with size: "<<liStraightAreaLinesDim2Top.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightAreaLinesDim2Top.front();
				bStraightBorderLineInDim1 = false;
				bStraightBorderLineFromMinToMax = false;
			}
		}
		if ( ! liStraightAreaLinesDim2Bottom.empty() ){
			//check if better border line exists
			if ( ( pBestLineBorderLine == NULL ) ||
					( ( pBestLineBorderLine->size * dImproveFactorMaxMax * dImproveFactorDim2 ) <
						liStraightAreaLinesDim2Bottom.front().size ) ){
				
				DEBUG_OUT_L2(<<"setting best in area line of dim 2 bottom with size: "<<liStraightAreaLinesDim2Top.front().size<<endl<<flush);
				pBestLineBorderLine = &liStraightAreaLinesDim2Bottom.front();
				bStraightBorderLineInDim1 = false;
				bStraightBorderLineFromMinToMax = false;
			}
		}
		if ( pBestLineBorderLine == NULL ){
			
			DEBUG_OUT_EL2(<<"Error: no best line found"<<endl<<flush);
			break;
		}
		
		
		//for the best straight line evalue the other part lines side border (for the spline)
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
		vector< fib::algorithms::nD1::cDataPointRangeWithWeights< long, double > >
			vecSplineRanges;
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
		vector< fib::algorithms::nD1::cDataPointRange< long, double > >
			vecSplineRanges;
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
		
		//find other side for tile (border oposide the straight line border)
		//the borders in which to search for the other side
		map< longFib, nImageStructureConvertToTiles::cLine > &
			bordersDimToSearchIn = (bStraightBorderLineInDim1 ? bordersDim1 : bordersDim2);
		
		const long lStartPoint = min( pBestLineBorderLine->lLineStartPoint,
				pBestLineBorderLine->lLineEndPoint );
		long lEndPoint   = max( pBestLineBorderLine->lLineStartPoint,
				pBestLineBorderLine->lLineEndPoint );
		
		/*if bigger 0 more other borders of the line part to the right (higher
		 * values), else (lower 0) more other border to the left */
		long lGoodStraightBorderPoint;
		
		//if first other border points to the right it is positiv else negativ
		bool bFirstIsRightOtherBorder = false;
		
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
		/*if a rectangle should be used the other side to lGoodStraightBorderPoint,
		 else (use not a rectangle) -1*/
		long lRectangleOfOtherSide = -1;
		bool bUseRectangle = false;
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
		if ( bStraightBorderLineFromMinToMax ){
			
			const double dMinBorderArea = pBestLineBorderLine->areaForLine.first + 0.001;
			const double dMaxBorderArea = pBestLineBorderLine->areaForLine.second - 0.001;
			DEBUG_OUT_L2(<<"Creating straight line min max ("<<(bStraightBorderLineInDim1?"Dim1":"Dim2")<<") ( from "<<pBestLineBorderLine->areaForLine.first<<" ("<<dMinBorderArea<<") to "<<pBestLineBorderLine->areaForLine.second<<" ("<<dMaxBorderArea<<") and size "<<pBestLineBorderLine->size<<")"<<endl<<flush);
			
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
			//the minimal and maximal values for the other side
			double dMinOtherBorderArea = 0;
			double dMaxOtherBorderArea = 0;
			bUseRectangle = true;
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
			{//check first part line for border
				map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
					itrActualLine = bordersDimToSearchIn.find( lStartPoint );
				
				if ( itrActualLine != bordersDimToSearchIn.end() ){
					//if first part line for border found
					const nImageStructureConvertToTiles::cLine::tLineParts &
						actualLine = itrActualLine->second.lineParts;
					//find the line part for the straight line border point
					nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
						itrActualPartLine = actualLine.begin();
					for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
						
						if ( ( itrActualPartLine->first.maxY <= dMinBorderArea ) &&
								( dMaxBorderArea <= itrActualPartLine->first.minY ) ){
							//line part for border found
							bFirstIsRightOtherBorder = true;
							DEBUG_OUT_L2(<<"first border line to the right"<<endl<<flush);
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
							dMinOtherBorderArea = itrActualPartLine->second.minY;
							dMaxOtherBorderArea = itrActualPartLine->second.maxY;
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
							break;
						}//else
						if ( ( itrActualPartLine->second.minY <= dMinBorderArea ) &&
								( dMaxBorderArea <= itrActualPartLine->second.maxY ) ){
							//line part for border found
							bFirstIsRightOtherBorder = false;
							DEBUG_OUT_L2(<<"first border line to the left"<<endl<<flush);
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
							dMinOtherBorderArea = itrActualPartLine->first.maxY;
							dMaxOtherBorderArea = itrActualPartLine->first.minY;
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
							break;
						}//else check next part line
					}//end for find the line part for the straight line border point
				}//end if first part line for border found
			}//end check first part line for border
			
			if ( bFirstIsRightOtherBorder ){
				//if first border line to the right
				
				for ( long lActualPoint = lStartPoint;
						lActualPoint <= lEndPoint; lActualPoint++ ){
					
					map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
						itrActualLine = bordersDimToSearchIn.find( lActualPoint );
					
					if ( itrActualLine == bordersDimToSearchIn.end() ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line found"<<endl<<flush);
						break;
					}
					const nImageStructureConvertToTiles::cLine::tLineParts &
						actualLine = itrActualLine->second.lineParts;
					//find the line part for the straight line border point
					nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
						itrActualPartLine = actualLine.begin();
					bool bNoNextLineFound = true;
					
					for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
						
						if ( ( itrActualPartLine->first.maxY <= dMinBorderArea ) &&
								( dMaxBorderArea <= itrActualPartLine->first.minY ) ){
							//line part for border found
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							const double dMinY = itrActualPartLine->second.minY;
							const double dMaxY = itrActualPartLine->second.maxY;
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
									lActualPoint, dMinY, dMaxY, 1.0, 1.0 ) );
							
							if ( ( dMinY + 1.0 ) < dMaxY ){
								//the border width is greater 1
								vecSplineRanges.push_back(
									fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
										lActualPoint, dMinY , dMinY + 0.98,
										D_WEIGHT_INNER_POINT, 0.0 ) );
							}
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back( itrActualPartLine->second );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
							if ( bUseRectangle ){
								//evalue the minimal and maximal values for the other side
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
								dMinOtherBorderArea = max( dMinOtherBorderArea, dMinY );
								dMaxOtherBorderArea = min( dMaxOtherBorderArea, dMaxY );
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
								dMinOtherBorderArea = max( dMinOtherBorderArea,
									itrActualPartLine->second.minY );
								dMaxOtherBorderArea = min( dMaxOtherBorderArea,
									itrActualPartLine->second.maxY );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
								bUseRectangle &= ( dMinOtherBorderArea < dMaxOtherBorderArea );
							}
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
							bNoNextLineFound = false;
							
							DEBUG_OUT_L4(<<"Part line second point added on "<<lActualPoint<<" from ("<<itrActualPartLine->first.maxY<<", "<<itrActualPartLine->first.minY<<") to ("<<itrActualPartLine->second.minY<<", "<<itrActualPartLine->second.maxY<<")"<<endl<<flush);
							break;
						}
						if ( ( itrActualPartLine->second.minY <= dMinBorderArea ) &&
								( dMaxBorderArea <= itrActualPartLine->second.maxY ) ){
							//line part for border found
							
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							const double dMinY = itrActualPartLine->first.maxY;
							const double dMaxY = itrActualPartLine->first.minY;
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
									lActualPoint, dMinY, dMaxY, 1.0, 1.0 ) );
							
							if ( dMinY < ( dMaxY - 1.0 ) ){
								//the border width is greater 1
								vecSplineRanges.push_back(
									fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
										lActualPoint, (dMaxY - 0.98) , dMaxY,
										D_WEIGHT_INNER_POINT, 0.0 ) );
							}
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRange< long, double >(
									lActualPoint, itrActualPartLine->first.maxY,
									itrActualPartLine->first.minY ) );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
							bUseRectangle = false;
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
							bNoNextLineFound = false;
							
							DEBUG_OUT_L4(<<"Part line first point added on "<<lActualPoint<<" from ("<<itrActualPartLine->first.maxY<<", "<<itrActualPartLine->first.minY<<") to ("<<itrActualPartLine->second.minY<<", "<<itrActualPartLine->second.maxY<<")"<<endl<<flush);
							break;
						}
					}//end for find the line part for the straight line border point
					if ( bNoNextLineFound ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line (min to max) found, because no next line was found"<<endl<<flush);
						break;
					}
				}//end for all lines in area
			
				/* if first other border points to the right -> minimize area
					outside the to convert area (betwean min max or overlapt points)
					-> move straight border as far as possible to the right */
				lGoodStraightBorderPoint = roundToLongFib( dMaxBorderArea );
				DEBUG_OUT_L2(<<"taking max straight border line as good straight border line start point: "<<lGoodStraightBorderPoint<<endl<<flush);
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
				if ( bUseRectangle ){
					//use a rectangle external object
					DEBUG_OUT_L2(<<"use a rectangle external object from "<<dMinOtherBorderArea<<" till "<<dMaxOtherBorderArea<<endl<<flush);
					
					lRectangleOfOtherSide = roundToLongFib( dMinOtherBorderArea );
					DEBUG_OUT_L2(<<"taking min border line as the other border: "<<lRectangleOfOtherSide<<endl<<flush);
				}
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
			}else{//if first border line to the left
				
				for ( long lActualPoint = lStartPoint;
						lActualPoint <= lEndPoint; lActualPoint++ ){
					
					map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
						itrActualLine = bordersDimToSearchIn.find( lActualPoint );
					
					if ( itrActualLine == bordersDimToSearchIn.end() ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line found"<<endl<<flush);
						break;
					}
					const nImageStructureConvertToTiles::cLine::tLineParts &
						actualLine = itrActualLine->second.lineParts;
					//find the line part for the straight line border point
					nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
						itrActualPartLine = actualLine.begin();
					bool bNoNextLineFound = true;
					
					for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
						
						if ( ( itrActualPartLine->second.minY <= dMinBorderArea ) &&
								( dMaxBorderArea <= itrActualPartLine->second.maxY ) ){
							//line part for border found
							
							const double dMinY = itrActualPartLine->first.maxY;
							const double dMaxY = itrActualPartLine->first.minY;
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
									lActualPoint, dMinY, dMaxY, 1.0, 1.0 ) );
							
							if ( dMinY < ( dMaxY - 1.0 ) ){
								//the border width is greater 1
								vecSplineRanges.push_back(
									fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
										lActualPoint, (dMaxY - 0.98) , dMaxY,
										D_WEIGHT_INNER_POINT, 0.0 ) );
							}
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRange< long, double >(
									lActualPoint, dMinY, dMaxY ) );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
							if ( bUseRectangle ){
								//evalue the minimal and maximal values for the other side
								dMinOtherBorderArea = max( dMinOtherBorderArea, dMinY );
								dMaxOtherBorderArea = min( dMaxOtherBorderArea, dMaxY );
								bUseRectangle &= ( dMinOtherBorderArea < dMaxOtherBorderArea );
							}
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
							bNoNextLineFound = false;
							
							DEBUG_OUT_L4(<<"Part line first point added on "<<lActualPoint<<" from ("<<itrActualPartLine->first.maxY<<", "<<itrActualPartLine->first.minY<<") to ("<<itrActualPartLine->second.minY<<", "<<itrActualPartLine->second.maxY<<")"<<endl<<flush);
							
							break;
						}
						if ( ( itrActualPartLine->first.maxY <= dMinBorderArea ) &&
								( dMaxBorderArea <= itrActualPartLine->first.minY ) ){
							//line part for border found
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							const double dMinY = itrActualPartLine->second.minY;
							const double dMaxY = itrActualPartLine->second.maxY;
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
									lActualPoint, dMinY, dMaxY, 1.0, 1.0 ) );
							
							if ( ( dMinY + 1.0 ) < dMaxY ){
								//the border width is greater 1
								vecSplineRanges.push_back(
									fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
										lActualPoint, dMinY , dMinY + 0.98,
										D_WEIGHT_INNER_POINT, 0.0 ) );
							}
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back( itrActualPartLine->second );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
							bUseRectangle = false;
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
							bNoNextLineFound = false;
							
							DEBUG_OUT_L4(<<"Part line second point added on "<<lActualPoint<<" from ("<<itrActualPartLine->first.maxY<<", "<<itrActualPartLine->first.minY<<") to ("<<itrActualPartLine->second.minY<<", "<<itrActualPartLine->second.maxY<<")"<<endl<<flush);
							break;
						}
					}//end for find the line part for the straight line border point
					if ( bNoNextLineFound ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line (min to max) found, because no next line was found"<<endl<<flush);
						break;
					}
				}//end for all lines in area
			
				/* if first other border points to the left -> minimize area
					outside the to convert area (betwean min max or overlapt points)
					-> move straight border as far as possible to the left */
				lGoodStraightBorderPoint = roundToLongFib( dMinBorderArea );
				DEBUG_OUT_L2(<<"taking min straight border line as good straight border line start point: "<<lGoodStraightBorderPoint<<endl<<flush);
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
				if ( bUseRectangle ){
					//use a rectangle external object
					DEBUG_OUT_L2(<<"use a rectangle external object from "<<dMinOtherBorderArea<<" till "<<dMaxOtherBorderArea<<endl<<flush);
					
					lRectangleOfOtherSide = roundToLongFib( dMaxOtherBorderArea );
					DEBUG_OUT_L2(<<"taking max border line as the other border: "<<lRectangleOfOtherSide<<endl<<flush);
				}
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
			}//end if border left or right
			
		}else{//if max to max oposide border allways to the left (lower numbers)
			//check on which side of the straigt line the area should go
			double dStraightBorderMaxToMax;
			bool bAreaToTheLeft = true;
			const double dMinBorderArea = pBestLineBorderLine->areaForLine.first;
			const double dMaxBorderArea = pBestLineBorderLine->areaForLine.second;
			//enlarge check value because of rounding errors
			const double dMinBorderAreaUpper = dMinBorderArea + 0.001;
			const double dMaxBorderAreaLower = dMaxBorderArea - 0.001;
			const double dMaxBorderAreaUpper = dMaxBorderArea + 0.001;
			
			{//check on which side of the straight line border the area should lay
				map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
					itrActualLine = bordersDimToSearchIn.find( lStartPoint );
				if ( itrActualLine == bordersDimToSearchIn.end() ){
					//gap in line
					DEBUG_OUT_EL2(<<"Error: first line for best line (max to max) could not be found"<<endl<<flush);
					break;
				}
				const nImageStructureConvertToTiles::cLine::tLineParts &
					actualLine = itrActualLine->second.lineParts;
				//find the line part for the straight line border point
				nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
					itrActualPartLine = actualLine.begin();
				for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
					
					if ( ( itrActualPartLine->first.maxY <= dMinBorderAreaUpper ) &&
							( dMaxBorderAreaLower <= itrActualPartLine->second.maxY ) ){
						//line part for border found -> check upper minY value
						if ( dMaxBorderAreaUpper < itrActualPartLine->first.minY ){
							/* the min area of the line part of the first line
							 * begins after the straight line border to use
							 * -> create area for other (=right) side*/
							bAreaToTheLeft = false;
						}
						
						DEBUG_OUT_L2(<<"The max max area object will be created on the "<<(bAreaToTheLeft?"left":"right")<<" side of the straight line"<<endl<<flush);
						break;
					}//end if line part found
				}//end for find the line part for the straight line border point
			}
			
			if ( bAreaToTheLeft ){
				dStraightBorderMaxToMax = dMaxBorderArea;
				
				DEBUG_OUT_L2(<<"Creating straight line max max ("<<(bStraightBorderLineInDim1?"Dim1":"Dim2")<<" for position init: "<<std::fixed<<dMaxBorderArea<<"; for line from "<<pBestLineBorderLine->areaForLine.first<<" till "<<pBestLineBorderLine->areaForLine.second<<" and size "<<pBestLineBorderLine->size<<")"<<endl<<flush);
				
				for ( long lActualPoint = lStartPoint;
						lActualPoint <= lEndPoint; lActualPoint++ ){
					
					map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
						itrActualLine = bordersDimToSearchIn.find( lActualPoint );
					
					if ( itrActualLine == bordersDimToSearchIn.end() ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line (max to max) found"<<endl<<flush);
						break;
					}
					const nImageStructureConvertToTiles::cLine::tLineParts &
						actualLine = itrActualLine->second.lineParts;
					//find the line part for the straight line border point
					nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
						itrActualPartLine = actualLine.begin();
					bool bNoNextLineFound = true;
					for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
						
						if ( ( itrActualPartLine->first.maxY <= dMinBorderAreaUpper ) &&
								( dMaxBorderAreaLower <= itrActualPartLine->second.maxY ) ){
							//line part for border found -> add left line part border
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							const double dMinY = itrActualPartLine->first.maxY;
							const double dMaxY = itrActualPartLine->first.minY;
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
									lActualPoint, dMinY, dMaxY, 1.0, 1.0 ) );
							
							if ( dMinY < ( dMaxY - 1.0 ) ){
								//the border width is greater 1
								vecSplineRanges.push_back(
									fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
										lActualPoint, (dMaxY - 0.98) , dMaxY,
										D_WEIGHT_INNER_POINT, 0.0 ) );
							}
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRange< long, double >(
									lActualPoint,
									itrActualPartLine->first.maxY,
									itrActualPartLine->first.minY ) );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							/*go for the straight border as far as the min borders
							go for the other side, but maximal to the best straight
							border line maximum dMaxBorderArea*/
							const double dOtherSide = itrActualPartLine->second.minY;
							if ( dMaxBorderArea < dOtherSide ){
								dStraightBorderMaxToMax = dMaxBorderArea;
							}else{
								dStraightBorderMaxToMax = max(
									dStraightBorderMaxToMax, dOtherSide );
							}
							bNoNextLineFound = false;
							DEBUG_OUT_L4(<<"Part line first point added on "<<lActualPoint<<" from ("<<itrActualPartLine->first.maxY<<", "<<itrActualPartLine->first.minY<<") to ("<<itrActualPartLine->second.minY<<", "<<itrActualPartLine->second.maxY<<" and size "<<pBestLineBorderLine->size<<")"<<endl<<flush);

							break;
						}//end if part line found
					}//end for find the line part for the straight line border point
					if ( bNoNextLineFound ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line (max to max) found, because no next line was found"<<endl<<flush);
						break;
					}
				}//end for all lines in area
			}else{//create area on the right side
				
				dStraightBorderMaxToMax = dMinBorderArea;
				
				DEBUG_OUT_L2(<<"Creating straight line max max ("<<(bStraightBorderLineInDim1?"Dim1":"Dim2")<<" for position init: "<<std::fixed<<dMinBorderArea<<" for line from "<<pBestLineBorderLine->areaForLine.first<<" till "<<pBestLineBorderLine->areaForLine.second<<", with area on the right)"<<endl<<flush);
				
				for ( long lActualPoint = lStartPoint;
						lActualPoint <= lEndPoint; lActualPoint++ ){
					
					map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
						itrActualLine = bordersDimToSearchIn.find( lActualPoint );
					
					if ( itrActualLine == bordersDimToSearchIn.end() ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line (max to max) found"<<endl<<flush);
						break;
					}
					const nImageStructureConvertToTiles::cLine::tLineParts &
						actualLine = itrActualLine->second.lineParts;
					//find the line part for the straight line border point
					nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
						itrActualPartLine = actualLine.begin();
					bool bNoNextLineFound = true;
					for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
						
						if ( ( itrActualPartLine->first.maxY <= dMinBorderAreaUpper ) &&
								( dMaxBorderAreaLower <= itrActualPartLine->second.maxY ) ){
							//line part for border found -> add left line part border
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							const double dMinY = itrActualPartLine->second.minY;
							const double dMaxY = itrActualPartLine->second.maxY;
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
									lActualPoint, dMinY, dMaxY, 1.0, 1.0 ) );
							
							if ( dMaxY < ( dMinY + 1.0 ) ){
								//the border width is greater 1
								vecSplineRanges.push_back(
									fib::algorithms::nD1::cDataPointRangeWithWeights< long, double >(
										lActualPoint, dMinY , dMinY + 0.98,
										D_WEIGHT_INNER_POINT, 0.0 ) );
							}
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							vecSplineRanges.push_back(
								fib::algorithms::nD1::cDataPointRange< long, double >(
									lActualPoint,
									itrActualPartLine->second.minY,
									itrActualPartLine->second.maxY ) );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
							/*go for the straight border as far as the min borders
							go for the other side, but minimal to the best straight
							border line minimum dMinBorderArea*/
							const double dOtherSide = itrActualPartLine->first.minY;
							if ( dOtherSide < dMinBorderArea ){
								dStraightBorderMaxToMax = dMinBorderArea;
							}else{
								dStraightBorderMaxToMax = min(
									dStraightBorderMaxToMax, dOtherSide );
							}
							bNoNextLineFound = false;
							DEBUG_OUT_L4(<<"Part line first point added on "<<lActualPoint<<" from ("<<itrActualPartLine->first.maxY<<", "<<itrActualPartLine->first.minY<<") to ("<<itrActualPartLine->second.minY<<", "<<itrActualPartLine->second.maxY<<")"<<endl<<flush);
							break;
						}//end if part line found
					}//end for find the line part for the straight line border point
					if ( bNoNextLineFound ){
						//gap in line
						DEBUG_OUT_EL2(<<"Error: gap in best line (max to max) found, because no next line was found"<<endl<<flush);
						break;
					}
				}//end for all lines in area
			}
			
			lGoodStraightBorderPoint = roundToLongFib( dStraightBorderMaxToMax );
			DEBUG_OUT_EL2(<<"Creating straight line max max for position: "<<dStraightBorderMaxToMax<<endl<<flush);
		}
#ifdef DEBUG
		cout<<endl<<"Create polynom for spline vecSplineRanges: "<<std::fixed;
		for ( unsigned int uiActRange = 0; uiActRange < vecSplineRanges.size(); uiActRange++ ){
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
			cout<<"("<<vecSplineRanges[uiActRange].x<<";["<<
				vecSplineRanges[uiActRange].minY<<" ... "<<vecSplineRanges[uiActRange].maxY<<
				"] ( wS="<<vecSplineRanges[uiActRange].dWeightSolver<<
				" wE="<<vecSplineRanges[uiActRange].dWeightError<<") ); ";
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
			cout<<"("<<vecSplineRanges[uiActRange].x<<";["<<
				vecSplineRanges[uiActRange].minY<<" ... "<<vecSplineRanges[uiActRange].maxY<<"] ); ";
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
		}
		cout<<endl;
#endif //DEBUG
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		cEvaluePositionListLimit pointsInTile( 0, &vecDomainDimension,
				false, 256L * pBestLineBorderLine->size + 1024L,
				1024L * pBestLineBorderLine->size + 1024L );
#ifdef DEBUG
		cout<<endl<<"cEvaluePositionListLimit pointsInTile( 0, "<<
			"&vecDomainDimension, false, 256L * pBestLineBorderLine->size(="<<
			pBestLineBorderLine->size<<") ="<<(256L * pBestLineBorderLine->size + 1024L)<<
			", 1024L * pBestLineBorderLine->size + 1024L="<<
			(1024L * pBestLineBorderLine->size + 1024L)<<" );"<<endl;
#endif //DEBUG
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		cEvaluePositionList pointsInTile;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		cExtObject * pNewExtObject = NULL;
		
		if ( ( vecSplineRanges.size() == 1 ) ||
				( ( vecSplineRanges.size() == 2 ) &&
					( vecSplineRanges[ 0 ].x == vecSplineRanges[ 1 ].x ) ) ){
			/* if area contains just positions with one value for one coordinate
			 -> area is line*/
			//find line part for border
			const double dMinBorderArea = pBestLineBorderLine->areaForLine.first;
			//enlarge check value because of rounding errors
			const double dMinBorderAreaLower = dMinBorderArea - 0.001;
			const double dMinBorderAreaUpper = dMinBorderArea + 0.001;
			longFib lPartLineStartPoint = 0;
			longFib lPartLineEndPoint = 0;
			bool bPartLineFound = false;
			{
				map< longFib, nImageStructureConvertToTiles::cLine >::const_iterator
					itrActualLine = bordersDimToSearchIn.find( lStartPoint );
				if ( itrActualLine == bordersDimToSearchIn.end() ){
					DEBUG_OUT_EL2(<<"Error: First line for best straight line could not be found."<<endl<<flush);
				}else{//first line for best straight line found
					const nImageStructureConvertToTiles::cLine::tLineParts &
						actualLine = itrActualLine->second.lineParts;
					//find the line part for the straight line border point
					nImageStructureConvertToTiles::cLine::tLineParts::const_iterator
						itrActualPartLine = actualLine.begin();
					
					for (  ; itrActualPartLine != actualLine.end(); itrActualPartLine++ ){
						
						if ( ( bStraightBorderLineFromMinToMax && (
								( ( itrActualPartLine->second.minY <= dMinBorderAreaUpper ) &&
									( dMinBorderAreaLower <= itrActualPartLine->second.maxY ) ) ||
								( ( itrActualPartLine->first.maxY <= dMinBorderAreaUpper ) &&
									( dMinBorderAreaLower <= itrActualPartLine->first.minY ) ) )
								) || ( ( ! bStraightBorderLineFromMinToMax ) &&
									( ( itrActualPartLine->first.maxY <= dMinBorderAreaUpper ) &&
										( dMinBorderAreaLower <= itrActualPartLine->second.maxY ) ) ) ){
							//line part for border found -> check upper minY value
							lPartLineStartPoint = roundToLongFib( itrActualPartLine->first.minY );
							lPartLineEndPoint   = roundToLongFib( itrActualPartLine->second.minY );
							bPartLineFound = true;
							DEBUG_OUT_L2(<<"The only part line of the straight line on "<<lStartPoint<<" found it goes from "<<lPartLineStartPoint<<" to "<<lPartLineEndPoint<<endl<<flush);
							break;
						}
					}//for find the line part for the straight line border point
				}//end if first line for best straight line found
			}
			if ( ! bPartLineFound ){
				DEBUG_OUT_EL2(<<"Error: Line part of first line for best straight line could not be found -> stop evaluation to prevent infinite loops"<<endl<<flush);
				break;
			}
			
			if ( lPartLineStartPoint == lPartLineEndPoint ){
				//create point external object
				cVectorExtObject vecPointExtObjectInputValues( 2 );
				
				vecPointExtObjectInputValues.setValue( (bStraightBorderLineInDim1?1:2 ),
					lStartPoint );
				vecPointExtObjectInputValues.setValue( (bStraightBorderLineInDim1?2:1 ),
					lPartLineStartPoint );
				
				pNewExtObject = new cExtObject( -2, vecPointExtObjectInputValues );
			}else{//create line ( lPartLineStartPoint < lPartLineEndPoint )
				// use area elements if just one line wher found
				cVectorExtObject vecLineExtObjectInputValues( 3 );
				/* parameters for horizontal line (id -23) :
				* 	- position start point dimension 1 (x_1)
				* 	- position points in dimension 2 (y)
				* 	- position end point dimension 1 (x_2)
				* parameters for horizontal line (id -24) :
				* 	- position points in dimension 1 (x)
				* 	- position start point dimension 2 (y_1)
				* 	- position end point dimension 2 (y_2)
				*/
				vecLineExtObjectInputValues.setValue( (bStraightBorderLineInDim1?1:2 ),
					lStartPoint );
				vecLineExtObjectInputValues.setValue( (bStraightBorderLineInDim1?2:1 ),
					lPartLineStartPoint );
				vecLineExtObjectInputValues.setValue( 3, lPartLineEndPoint );
				//id -23 or -24
				pNewExtObject = new cExtObject(
					( bStraightBorderLineInDim1 ? -24 : -23 ), vecLineExtObjectInputValues );
			}
			bUseRectangle = false;
			//ignore antialising
#ifdef DEBUG
			cout<<endl<<"Generated external line object:"<<endl;
			pNewExtObject->storeXml( cout );
			cout<<endl;
#endif //DEBUG
			//evalue points in tile
			pNewExtObject->evalueObjectSimple( pointsInTile );
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
		}else  if ( ! bUseRectangle ){//evalue tile
#else //FEATURE_USE_RECTANGLE_EXT_OBJECT
		}else{//evalue tile
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
			//evalue tile spline
			cPolynom< long, double > splineForBorder;
			const unsigned long ulNumberOfPointsInSpline =
				splineForBorder.evalueSplineIterativFast(
					vecSplineRanges, NUMBER_OF_SPLINE_PARAMETERS,
					maxValue, maxError, maxErrorPerValue, liWeightParameters );
			
#ifdef DEBUG
			cout<<endl<<"Found spline for "<<ulNumberOfPointsInSpline<<" data points: "<<fixed;
			splineForBorder.print( cout );
			cout<<endl;
#endif //DEBUG
			if ( ulNumberOfPointsInSpline == 0 ){
				DEBUG_OUT_EL2(<<"Error: spline for next tile not found (no lines in spline)"<<endl<<flush);
				break;
			}
			
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
		//check if a quadrangle could be used for data points in the found spline
		if ( ulNumberOfPointsInSpline < vecSplineRanges.size() ){
			/*not all points in polynom
			 -> check if points in polynom till ulNumberOfPointsInSpline are straight line*/
			unsigned int ulLastPointForStraightOtherBorderLine = 0;
			double dMinOtherBorderArea = vecSplineRanges[ 0 ].minY;
			double dMaxOtherBorderArea = vecSplineRanges[ 0 ].maxY;
			double dMinOtherBorderAreaTmp = dMinOtherBorderArea;
			double dMaxOtherBorderAreaTmp = dMaxOtherBorderArea;
			for (
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
					vector< fib::algorithms::nD1::cDataPointRangeWithWeights< long, double > >::const_iterator
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
					vector< fib::algorithms::nD1::cDataPointRange< long, double > >::const_iterator
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
						itrActualDataPoint = vecSplineRanges.begin();
					itrActualDataPoint != vecSplineRanges.end();
					itrActualDataPoint++, ulLastPointForStraightOtherBorderLine++ ){
				
				dMinOtherBorderAreaTmp = max( dMinOtherBorderArea, itrActualDataPoint->minY );
				dMaxOtherBorderAreaTmp = min( dMaxOtherBorderArea, itrActualDataPoint->maxY );
				if ( dMaxOtherBorderAreaTmp < dMinOtherBorderAreaTmp ){
					//no straight line can be used instead of polynom, with this point
					break;
				}
				dMinOtherBorderArea = dMinOtherBorderAreaTmp;
				dMaxOtherBorderArea = dMaxOtherBorderAreaTmp;
			}//end for all range points for spline
			DEBUG_OUT_L2(<<"check if to use rectangle object for the area, min range spline data points "<<dMinOtherBorderArea<<" max "<<dMaxOtherBorderArea<<endl<<flush);
			if ( ( ulNumberOfPointsInSpline * 0.7 ) <=
					ulLastPointForStraightOtherBorderLine ){
				//use a rectangle object for the area
				DEBUG_OUT_L2(<<"Use a rectangle object for the area, because "<<ulLastPointForStraightOtherBorderLine<<" data points for the spline border are on straight line"<<endl<<flush);
				bUseRectangle = true;
				lEndPoint = roundToLongFib(
					vecSplineRanges[ ulLastPointForStraightOtherBorderLine ].x );
				
				if ( bFirstIsRightOtherBorder ){
					lRectangleOfOtherSide = roundToLongFib( dMinOtherBorderArea );
				}else{
					lRectangleOfOtherSide = roundToLongFib( dMaxOtherBorderArea );
				}
			}
		}//end check if a quadrangle could be used
		
		if ( ! bUseRectangle ){
			//do not use a rectangle instead of a spline tile
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
				
				//evalue the end point of the tile / spline
				const long lEndPointOfInTile = roundToLongFib(
					vecSplineRanges[ ulNumberOfPointsInSpline - 1 ].x );
				
				
				//reduce the number of bits per value
				if ( bReduceBitsForParameter ){
#ifdef DEBUG
					cout<<"reducing bit for parameters"<<endl;
#endif //DEBUG
#ifdef FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
					vector< fib::algorithms::nD1::cDataPointRange< long, double > >
						vecPossibleSplineRanges;
					//select all ranges wich are error relevant
					for ( unsigned long uiActualPoint = 0;
							uiActualPoint < ulNumberOfPointsInSpline; uiActualPoint++ ){
						if ( 0.5 < vecSplineRanges[ uiActualPoint ].dWeightError ){
							//point is error relevant
							vecPossibleSplineRanges.push_back(
								cDataPointRange< long, double >( vecSplineRanges[ uiActualPoint ] ) );
						}
					}
					splineForBorder.reduceBits( vecPossibleSplineRanges,
						maxValue, maxError, maxErrorPerValue );
#else //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
					splineForBorder.reduceBits( vecSplineRanges,
						maxValue, maxError, maxErrorPerValue );
#endif //FEATURE_C_IMAGE_STRUCTURE_CONVERT_TO_TILES_USE_INNER_LINE
#ifdef DEBUG
					cout<<"Found spline for "<<ulNumberOfPointsInSpline<<" data points: ";
					splineForBorder.print( cout );
					cout<<endl;
#endif //DEBUG
				}
				
				//create the tile
				cVectorExtObject vecTileExtObjectInputValues( 3 + NUMBER_OF_SPLINE_PARAMETERS );
				/* set tile parameters:
					* inVar1 : position start point dimension 1 (x_s)
					* inVar2 : position start point dimension 2 (y_s)
					* inVar3 : position end point dimension 1 (x_e)
					* inVar4 : parameter a_0 of the line function f
					* inVar5 : parameter a_1 of the line function f
					* inVar6 : parameter a_2 of the line function f
					* ...
				*/
				//position start point
				
				//first 3 parameters for straight border line
				vecTileExtObjectInputValues.setValue( (bStraightBorderLineInDim1 ?1:2 ),
					lStartPoint );
				//set value for the straight border
				vecTileExtObjectInputValues.setValue( (bStraightBorderLineInDim1 ?2:1 ),
					lGoodStraightBorderPoint );
				
				//position end point
				vecTileExtObjectInputValues.setValue( 3, lEndPointOfInTile );
				
				//set spline parameter parameters
				for ( unsigned int uiActualSplineParameter = 0;
						uiActualSplineParameter < NUMBER_OF_SPLINE_PARAMETERS;
						uiActualSplineParameter++ ){
					
					if ( uiActualSplineParameter < splineForBorder.vecFactors.size()  ){
						//set tile spline factors
						vecTileExtObjectInputValues.setValue(
							uiActualSplineParameter + 4,
							splineForBorder.vecFactors[ uiActualSplineParameter ] );
					}
				}
				
				pNewExtObject = new cExtObject(
					( bStraightBorderLineInDim1 ? IDENTIFIER_SPLINE_OBJECT_XY :
						IDENTIFIER_SPLINE_OBJECT_YX ), vecTileExtObjectInputValues );
				
#ifdef DEBUG
				cout<<endl<<"Generated external object:"<<endl;
				pNewExtObject->storeXml( cout );
				cout<<endl;
#endif //DEBUG
				
				//remove points in tile from minimum borders
				//evalue points in tile
				pNewExtObject->evalueObjectSimple( pointsInTile );
				
				if ( bIsAntialised ){
					//change values for antialising
					pNewExtObject->setIdentifier( bStraightBorderLineInDim1 ?
						IDENTIFIER_SPLINE_OBJECT_AA_XY : IDENTIFIER_SPLINE_OBJECT_AA_YX );
					
					//create subobject with point and transparecy property
					cVectorPosition vecPosition( 2 );
					cPoint * pPoint = new cPoint( &vecPosition );
					//create the subobject for the external object element
					pNewExtObject->setNumberOfSubobjects( 1 );
					pNewExtObject->setNumberOfOutputVariables( 1, 3 );
					
					//set the position of the point to the external object output variables
					pPoint->getPosition()->setVariable( 1,
						pNewExtObject->getOutputVariable( 1, 1 ) );
					pPoint->getPosition()->setVariable( 2,
						pNewExtObject->getOutputVariable( 1, 2 ) );
					//create the transparency property
					cVectorProperty vecTransparency( cTypeProperty::TRANSPARENCY );
					cProperty * pProperty = new cProperty( vecTransparency, pPoint );
					pProperty->getProperty()->setVariable( 1,
						pNewExtObject->getOutputVariable( 1, 3 ) );
					
					//set the created property and point as the first subobject of the external object
					pNewExtObject->setSubobject( 1, pProperty );
#ifdef DEBUG
					cout<<endl<<"Modified antialised external object:"<<endl;
					pNewExtObject->storeXml( cout );
					cout<<endl;
#endif //DEBUG
				}//end if antialised
#ifdef FEATURE_USE_RECTANGLE_EXT_OBJECT
			}//end if create tile external object
		}//end if create external subobjects
		if ( ( pNewExtObject == NULL ) && bUseRectangle ){
			DEBUG_OUT_L2(<<"Use the rectangle object for the area"<<endl<<flush);
			
			cVectorExtObject vecRectangleExtObjectInputValues( 4 );
			/* position of the start point in dimension 1 (x_s)
			 * position of the start point in dimension 2 (y_s)
			 * position of the end point in dimension 1 (x_e)
			 * position of the end point in dimension 2 (y_e)
			 */
			vecRectangleExtObjectInputValues.setValue(
				(bStraightBorderLineInDim1? 1 : 2 ), lStartPoint );
			vecRectangleExtObjectInputValues.setValue(
				(bStraightBorderLineInDim1? 3 : 4 ), lEndPoint );
			vecRectangleExtObjectInputValues.setValue(
				(bStraightBorderLineInDim1? 2 : 1 ),
				min( lRectangleOfOtherSide, lGoodStraightBorderPoint ) );
			vecRectangleExtObjectInputValues.setValue(
				(bStraightBorderLineInDim1? 4 : 3 ),
				max( lRectangleOfOtherSide, lGoodStraightBorderPoint ) );
			
			pNewExtObject = new cExtObject( -40, vecRectangleExtObjectInputValues );
			
			pNewExtObject->evalueObjectSimple( pointsInTile );
#ifdef DEBUG
			cout<<endl<<"Generated external rectangle object:"<<endl;
			pNewExtObject->storeXml( cout );
			cout<<endl;
#endif //DEBUG
		}
#else //FEATURE_USE_RECTANGLE_EXT_OBJECT
		}//end if create external subobjects
#endif //FEATURE_USE_RECTANGLE_EXT_OBJECT
		
#ifdef DEBUG
		cout<<"Points in external object (tile):"<<fixed<<endl;
		pointsInTile.printPositionsData( pointsInTile.liEvaluedPositionData, cout );
#endif //DEBUG
#ifdef DEBUG_OUTPUT_GENERATED_AREA_DATA
		static unsigned long ulOutputDebugIteration = 0;
		ulOutputDebugIteration++;
		
		cout<<endl<<"Storing points of generated Fib object number: "<<ulOutputDebugIteration<<endl;
		cVectorProperty vecBorderColor( cTypeProperty::COLOR_RGB );
		vecBorderColor.setValue( 3, 255 );
		
		vecBorderColor.setValue( 2, ulOutputDebugIteration % 256 );
		vecBorderColor.setValue( 1, ( ulOutputDebugIteration / 256 ) % 256 );
		
#ifdef DEBUG_OUTPUT_GENERATED_AREA_DATA_FILE
		cImageAreaSameColor structureArea( vecBorderColor );
		
		set<cVectorPosition> setStructurePoints;
		
		const list< pair< cVectorPosition, list< cVectorProperty > > > &
			liEvaluedData = pointsInTile.liEvaluedPositionData;
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::const_iterator
				itrPoint = liEvaluedData.begin();
				itrPoint != liEvaluedData.end(); itrPoint++ ){
			
			setStructurePoints.insert( itrPoint->first );
		}
		structureArea.setStructurePoints( setStructurePoints );
		
		ofstream ofFileStructurAreaData( DEBUG_OUTPUT_GENERATED_AREA_DATA_FILE, ios_base::app );
		structureArea.storeXml( ofFileStructurAreaData );
		ofFileStructurAreaData.close();
#endif //DEBUG_OUTPUT_GENERATED_AREA_DATA_FILE
		
#endif //DEBUG_OUTPUT_GENERATED_AREA_DATA
		
		if ( pNewExtObject == NULL ){
			DEBUG_OUT_EL2(<<endl<<"Error: No external object generated -> stop evaluation to prevent infinite loop"<<endl<<endl<<flush);
			break;
		}
		if ( pointsInTile.liEvaluedPositionData.empty() ){
			DEBUG_OUT_EL2(<<"Error: no points evalued for the tile -> no change -> stop evaluation (beware infinit loop)"<<endl<<flush);
#ifdef DEBUG
			if ( pNewExtObject ){
				pNewExtObject->evalueObjectSimple( pointsInTile );
			}
#endif //DEBUG
			break;
		}
		DEBUG_OUT_L2(<<"Erasing found (=tile) points"<<endl<<flush);
		map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim1 = bordersDim1.begin();
		map< longFib, nImageStructureConvertToTiles::cLine >::iterator
				itrActualLineDim2 = bordersDim2.begin();
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		unsigned long ulNumberOfAreaPointsInTile = 0;
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		bool bPointsRemoved = false;
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		for ( list< pair< cVectorPosition, list< cVectorProperty > > >::iterator
				itrActualPoint = pointsInTile.liEvaluedPositionData.begin();
				itrActualPoint != pointsInTile.liEvaluedPositionData.end();
				itrActualPoint++ ){
			
			cVectorPosition & actualPoint = itrActualPoint->first;
			const longFib lDim1Coordinate =
				roundToLongFib( actualPoint.getValue( 1 ) );
			const longFib lDim2Coordinate =
				roundToLongFib( actualPoint.getValue( 2 ) );
			
			//remove evalued points in tile from bordersDim1 and bordersDim2
			//remember old itrActualLineDim1 and check if it could be used again
			if ( ( itrActualLineDim1 == bordersDim1.end() ) ||
					( itrActualLineDim1->first != lDim1Coordinate ) ){
				//last line not for same coordinate
				itrActualLineDim1 = bordersDim1.find( lDim1Coordinate );
			}
			if ( itrActualLineDim1 != bordersDim1.end() ){
				//line part for point in first dimension found -> remove point
				nImageStructureConvertToTiles::cLine & lineDim1 =
					itrActualLineDim1->second;
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
				if ( lineDim1.removePoint( lDim2Coordinate ) ){
					ulNumberOfAreaPointsInTile++;
				}
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
				bPointsRemoved |= lineDim1.removePoint( lDim2Coordinate );
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
				if ( lineDim1.lineParts.empty() ){
					//if line contains no part lines -> remove it
					bordersDim1.erase( lDim1Coordinate );
					itrActualLineDim1 = bordersDim1.end();
				}
			}//else Error: should not happen
#ifdef DEBUG
			else{
				cout<<"Deleting point from line parts ("<<lDim1Coordinate<<", "<<lDim2Coordinate<<") could not find point in dimension 1"<<endl<<flush;
			}
#endif //DEBUG_DELETING_POINTS
			//remember old itrActualLineDim2 and check if it could be used again
			if ( ( itrActualLineDim2 == bordersDim2.end() ) ||
					( itrActualLineDim2->first != lDim2Coordinate ) ){
				//last line not for same coordinate
				itrActualLineDim2 = bordersDim2.find( lDim2Coordinate );
			}
			
			if ( itrActualLineDim2 != bordersDim2.end() ){
				//line part for point in second dimension found -> remove point
				nImageStructureConvertToTiles::cLine & lineDim2 =
					itrActualLineDim2->second;
				lineDim2.removePoint( lDim1Coordinate );
				if ( lineDim2.lineParts.empty() ){
					//if line contains no part lines -> remove it
					bordersDim2.erase( lDim2Coordinate );
					itrActualLineDim2 = bordersDim2.end();
				}
			}//else Error: should not happen
#ifdef DEBUG
			else{
				cout<<"Deleting point from line parts ("<<lDim1Coordinate<<", "<<lDim2Coordinate<<") could not find point in dimension 2"<<endl<<flush;
			}
#endif //DEBUG_DELETING_POINTS
			
#ifdef DEBUG_DELETING_POINTS
			cout<<endl<<"Deleting point from line parts ("<<lDim1Coordinate<<", "<<lDim2Coordinate<<")"<<endl<<flush;
			
			cout<<endl<<"New area for dimension 1:"<<endl;
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim1 = bordersDim1.begin();
					itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
				
				itrActualLineDim1->second.print( cout );
			}
			cout<<endl<<"New area for dimension 2:"<<endl;
			for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
					itrActualLineDim2 = bordersDim2.begin();
					itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
				
				itrActualLineDim2->second.print( cout );
			}
			cout<<endl;
#endif //DEBUG_DELETING_POINTS
			
		}//end remove all points from tile
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		if ( ulNumberOfAreaPointsInTile == 0 ){
			//no points deleted from area (should not occure)
			pNewExtObject->deleteObject();
			
			DEBUG_OUT_EL2(<<endl<<"Error: No points removed -> stop evaluation to prevent infinite loops"<<endl<<endl<<flush);
			bordersDim1.clear();
			break;
		}//else
		DEBUG_OUT_L2(<<endl<<" points removed: "<<ulNumberOfAreaPointsInTile<<endl<<endl<<flush);
		
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		if ( ! bPointsRemoved ){
			//no points deleted from area (should not occure)
			pNewExtObject->deleteObject();
			
			DEBUG_OUT_EL2(<<endl<<"Error: No points removed -> stop evaluation to prevent infinite loops"<<endl<<endl<<flush);
			bordersDim1.clear();
			break;
		}
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
	
		liFoundTiles.push_back( pNewExtObject );
		
#ifdef FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		if ( ulNumberOfAreaPointsInTile < ulMinGoodStraightLineSize ){
		/*if lines of found tile are less than ulMinGoodStraightLineSize
		 -> new number of lines is betwean number of lines in found tile and ulMinGoodStraightLineSize*/
			ulMinGoodStraightLineSize = ( ulMinGoodStraightLineSize + ulNumberOfAreaPointsInTile ) / 2 + 1;
		}else{/*if lines of found tile is equal ulMinGoodStraightLineSize
		 -> new number is the twice of ulMinGoodStraightLineSize*/
			ulMinGoodStraightLineSize *= dImproveFactorDim2;
		}
#else //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		if ( ulNumberOfLinesInTile < ulMinGoodStraightLineSize ){
		/*if lines of found tile are less than ulMinGoodStraightLineSize
		 -> new number of lines is betwean number of lines in found tile and ulMinGoodStraightLineSize*/
			ulMinGoodStraightLineSize = ( ulMinGoodStraightLineSize + ulNumberOfLinesInTile ) / 2 + 1;
		}else{/*if lines of found tile is equal ulMinGoodStraightLineSize
		 -> new number is the twice of ulMinGoodStraightLineSize*/
			ulMinGoodStraightLineSize *= dImproveFactorDim2;
		}
#endif //FEATURE_STRAIGHT_LINE_SIZE_IS_AREA_SIZE
		
	}//end while points in area to convert
	
	DEBUG_OUT_L2(<<"cImageStructureConvertToTiles("<<this<<")::convertToExtObjects( pImageSearchData, maxValue="<<maxValue<<", maxErrorPerValue="<<maxErrorPerValue<<", maxError="<<maxError<<" ) done"<<endl<<flush);
	
#ifdef DEBUG
	cout<<"creating external objects:"<<endl;
	for ( list< cExtObject * >::const_iterator itrTile = liFoundTiles.begin();
			itrTile != liFoundTiles.end(); itrTile++ ){
		
		(*itrTile)->storeXml( cout );
	}
	cout<<endl;
	cout<<endl<<"Last area for dimension 1:"<<endl;
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim1 = bordersDim1.begin();
			itrActualLineDim1 != bordersDim1.end(); itrActualLineDim1++ ){
		
		itrActualLineDim1->second.print( cout );
	}
	cout<<endl<<"Last area for dimension 2:"<<endl;
	for ( map< longFib, nImageStructureConvertToTiles::cLine >::iterator
			itrActualLineDim2 = bordersDim2.begin();
			itrActualLineDim2 != bordersDim2.end(); itrActualLineDim2++ ){
		
		itrActualLineDim2->second.print( cout );
	}
	cout<<endl;
#endif //DEBUG
	return liFoundTiles;
}












