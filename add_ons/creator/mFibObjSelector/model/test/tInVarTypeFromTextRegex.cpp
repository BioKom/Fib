
//TODO check

/**
 * @file tInVarTypeFromTextRegex
 * file name: tInVarTypeFromTextRegex.cpp
 * @author Betti Oesterholz
 * @date 07.04.2014
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This test is for testing the regular expressions of regex.
 *
 * Copyright (C) @c GPL3 2014 Betti Oesterholz
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
 * This test is for testing the regular expressions of regex.
 * The expressions are for extracting the input variables (inVar) types
 * form Fib objects optional parts.
 * @see cFibObjectInfo::getInVarTypeFromText()
 *
 * Call: tReg
 *
 *	Compile with:
 * 	g++ -Wall -g -std=c++11 -o tReg tInVarTypeFromTextRegex.cpp
 *
 */
/*
History:
07.04.2014  Oesterholz  created
*/


#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <ctime>
#include <cmath>
#include <regex>


using namespace std;



int main(int argc, char* argv[]){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	//check maximum CPU -load
	cout<<endl<<"Testing regex functions"<<endl;
	cout<<endl<<"======================="<<endl;
	
	cout<<"C++ version: \""<<__cplusplus<<"\""<<endl<<endl;

	//test if pattern matches
	list< pair< string, string > > liPatternTests;
	string szTestPattern;
	
	const string patPosition = "(((((position)|(location))|((locale)|(locality)))|(((place)|(site))|((spot)|(point))))|(pixle))";
	const string patDimension = "(((dimension)|(dim))|(direction))";
	const string parOne = "(((1)|(one))|((1\\.)|(first)))";
	const string parTwo = "(((2)|(two))|((2\\.)|(second)))";
	const string parThree = "(((3)|(three))|((3\\.)|(third)))";
	const string parFour = "(((4)|(four))|((4\\.)|(fourth)))";
	
	const string patStart = "(((1\\.)|(start))|((first)|"+ parOne +"))";
	
	const string patDim1 = "(((" + patDimension + " +" + parOne + ")|(" +
		parOne + " +" + patDimension + "))|(x))";
	const string patDim2 = "(((" + patDimension + " +" + parTwo + ")|(" +
		parTwo + " +" + patDimension + "))|(y))";
	
	const string patWidth = "((((width)|(breadth))|((compass)|(diameter)))|(((measure)|(span))|((thickness)|(wideness))))";
	
	const string patLine = "(((((line)|(lines))|((border)|(borderline)))|(((boundary)|(bound))|((edge)|( fringe))))|(((rank)|(rim))|(verge)))";
	
	const string patStartPosition = "((" + patStart + " +" + patPosition + ")|(" +
		patPosition + " +" + patStart +"))";
	
	const string patEndPosition = "(((((end)|(ending))|(last)) +" + patPosition + ")|(" +
		patPosition + " +(((end)|(ending))|(last))))";
	

	
	
	/*TODO for debug:
	szTestPattern = ".*position .*(((1\\.)|(start))|(first)) point .*dimension ((1)|(first)).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the first point p_1 in dimension 1 (x_1)") );
	*/
	
	
	//POS_DIM_1
	szTestPattern = ".*" + patPosition + " .*" + patStartPosition +" .*" + patDim1 +".*";
	
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the first point p_1 in dimension 1 (x_1)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the 1. point p_1 in dimension 1 (x_1)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the start point in dimension one") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the start point for x") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"site of the first point p_1 in first dimension (x_1)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the position in the first (x) direction / dimension of the start point x_s") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the position in the first (x) direction / dimension of the start point x_s") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the stickman start point (lower end of first (right) lower leg) in dimension 1 (x_lrle)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the pixle in the x direction of the start pixle x_s") );
	
	//POS_DIM_2
	szTestPattern = ".*" + patPosition + " .*" + patStartPosition +" .*" + patDim2 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the first point in dimension 2") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the 1. point p_1 in dimension 2 (y_1)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the start point in dimension two") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the start point for y") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"site of the first point p_1 in y direction ") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the position in the second (y) direction / dimension of the start point y_s") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the stickman start point (lower end of first (right) lower leg) in dimension 2 (y_lrle)") );
	
	
	//POS_END_DIM_1
	szTestPattern = ".*" + patPosition + " .*" + patEndPosition +" .*" + patDim1 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position end point dimension  1 (x_2)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"locality end point dimension one ") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"locality end point 1 dim ") );
	
	//POS_END_DIM_2
	szTestPattern = ".*" + patPosition + " .*" + patEndPosition +" .*" + patDim2 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position end point dimension 2 (y_2)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position end  point for the dimension 2 (y_2)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"locality ending point dimension two ") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"locality last point in the 2.   dim ") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"locality last point in the y direction ") );
	
	
	//LINE_WIDTH
	szTestPattern = ".*((" + patWidth + " .*" + patLine +")|("
		+ patLine + " .*" + patWidth +")).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the width of the line in points") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"line width") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"thickness of the borderline") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"wideness of verge") );
	
	//POS_POINT_3_DIM_1
	szTestPattern = ".*" + patPosition + " .*((" + parThree + " +" + patPosition + ")|(" +
		patPosition + " +" + parThree +")) .*" + patDim1 +".*";
	
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the 3. point in dimension 1 (x_3)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the third point p_3 in dimension 1 (x_3)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the third  site in x") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"site of the point 3 in first dimension (x_3)") );
/*TODO use when gcc 4.9 (no just cas sensitiv)
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the point Three in first  dimension ") );*/
	
	//POS_POINT_3_DIM_2
	szTestPattern = ".*" + patPosition + " .*((" + parThree + " +" + patPosition + ")|(" +
		patPosition + " +" + parThree +")) .*" + patDim2 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the 3. point in dimension 2 (y_3)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the point 3 p_3 in dim 2 (y_3)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the third point in dimension two") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the point  3 for y") );
/*TODO use when gcc 4.9 (no just cas sensitiv)
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"site of the site 3 p_1 in Y direction ") );*/

	//POS_POINT_4_DIM_1
	szTestPattern = ".*" + patPosition + " .*((" + parFour + " +" + patPosition + ")|(" +
		patPosition + " +" + parFour +")) .*" + patDim1 +".*";
	
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the 4. point in dimension 1 (x_4)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the fourth point p_4 in dimension 1 (x_4)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the fourth  site in x") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"site of the point four in first dimension (x_3)") );
	
	//POS_POINT_4_DIM_2
	szTestPattern = ".*" + patPosition + " .*((" + parFour + " +" + patPosition + ")|(" +
		patPosition + " +" + parFour +")) .*" + patDim2 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the 4. point in dimension 2 (y_4)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the point 4 p_4 in dim 2 (y_4)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the fourth point in dimension two") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the point  4 for y") );

	
	//SIZE_RADIUS
	const string patRadius = "((radius)|(diameter))";
	
	szTestPattern = ".*" + patRadius + ".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"size of the radius r") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"radius") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"radius size") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the  diameter of the objects") );
	
	//SIZE_RADIUS_DIM_1
	szTestPattern = ".*((" + patRadius + ".* " + patDim1 +")|(" +
		patDim1 + ".* " + patRadius +")).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"size of the radius r in dimension 1") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"direction 1 radius") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"radius size in x") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the  diameter of the objects in the first dimension") );
	
	//SIZE_RADIUS_DIM_2
	szTestPattern = ".*((" + patRadius + ".* " + patDim2 +")|(" +
		patDim2 + ".* " + patRadius +")).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"size of the radius r in dimension 2") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"direction 2 radius") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"radius size in y") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the  diameter of the objects in the second dimension") );
	
	
	//ANGLE
	szTestPattern = ".*((angle)|(chevron)).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the clockwise angle alpha (in radian) betwean the y dimension axis (angle 0 is up from the start point)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"angle") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"angle betwean x and y") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"angle alpha of body to the dimension 2 axis (or y-axis, because most stickman will be vertical or parallel to the y-axis) in clockwise direction, the feet start points are on the bottom of the body (and, for the angle, on the virtual dimension 2 (y) axis)") );
	
	//SIZE (remove inVars later in fors for SIZE_DIM_1 and SIZE_DIM_2)
	const string patSize = "((((size)|(distance))|((extent)|(bigness)))|(((length)|(span))|((stretch)|(width))))";
	
	szTestPattern = ".*" + patSize + ".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the distance (in points) betwean the start and end point l") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"size") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the  extent of  the object") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"length") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"object span") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"stretch") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"size s of stickman (top of the head to feet bottom, if legs are straight)") );
	
	//SIZE_DIM_1
	szTestPattern = ".*((" + patSize + ".* " + patDim1 +")|(" + patDim1 + ".* " + patSize +")).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the distance (in points) betwean the start and end point l in x direction") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"dim 1 size") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the  extent of  the object in 1. direction") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"length dim one") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"object span in direction one") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"stretch x dirction") );
	
	//SIZE_DIM_2
	szTestPattern = ".*((" + patSize + ".* " + patDim2 +")|(" + patDim2 + ".* " + patSize +")).*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the distance (in points) betwean the start and end point l in y direction") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"dim 2 size") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"the  extent of  the object in 2. direction") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"length dim two") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"object span in direction second") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"stretch y dirction") );
	
	
	/*remember inVar for position of all points in one dimension and
	 add later all free other sides for dimension as type for inVar
	 ( inVar v for dim 1: other inVars for POS_DIM_2, POS_POINT_2_DIM_1,
	 POS_POINT_3_DIM_1, POS_POINT_3_DIM_2 and POS_END_DIM_2
	 -> add type for inVar v: POS_DIM_1 and POS_END_DIM_1)*/
	//POS_POINT_ALL_DIM_1
	szTestPattern = ".*" + patPosition + " .*" + patPosition +"s .*" + patDim1 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position points in dimension 1 (x)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position points in  x dimension") );
	
	//POS_POINT_ALL_DIM_2
	szTestPattern = ".*" + patPosition + " .*" + patPosition +"s .*" + patDim2 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position points in dimension 2 (y)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position points in 2  dimension") );

	/*the first free inVar POS_* type will be set to the middle point
	 *inVar (of same dimension)*/
	const string parMiddle = "(((middle)|(center))|((mid)|(midpoint)))";
	
	//POS_POINT_MIDDLE_DIM_1 middle dim 1
	szTestPattern = ".*" + parMiddle + " .*" + patDim1 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the middle point in dimension 1 (x)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the middle point in dimension 1 (x_c)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the mid  site in x") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"site of the object center in first dimension") );
	
	//POS_POINT_MIDDLE_DIM_2 middle dim 2
	szTestPattern = ".*" + parMiddle + " .*" + patDim2 +".*";
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"position of the middle point in dimension 2 (y)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"location of the midpoint in dimension (y)") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"center dimension two") );
	liPatternTests.push_back( pair< string, string >( szTestPattern,
		"place for the circle  center for y") );
	

	unsigned int uiActualMatch = 1;
	string szLastPattern = "";
	unsigned int uiActualPattern = 0;
	unsigned int uiErrors = 0;
	/*where the errors occured:
		first: pattern number
		second: string number*/
	list< pair< unsigned int, unsigned int > > liErrors;
	for ( typename list< pair< string, string > >::const_iterator
			itrPattern = liPatternTests.begin();
			itrPattern != liPatternTests.end();
			++itrPattern, ++uiActualMatch ) {
		
		const regex regexSearchPattern( itrPattern->first,
			regex_constants::ECMAScript | regex_constants::icase );
		
		/*std::cout << "expressiont " <<
			( ( regexSearchPattern.flags() & regex_constants::icase ) ==
				regex_constants::icase ? "is":"is not")<<" case insensitive."<<endl;*/
		
		if ( szLastPattern != itrPattern->first ) {
			uiActualPattern++;
			szLastPattern = itrPattern->first;
			cout<<endl<<"Using pattern "<<uiActualPattern<<" : \""<<
				itrPattern->first<<"\""<<endl;
		}
		
		if ( regex_match( itrPattern->second, regexSearchPattern ) ) {
			cout << uiActualMatch<<". string \""<<itrPattern->second<<"\""<<endl;
		} else {
			cerr << "Error: "<<uiActualMatch<<". string \""<<itrPattern->second<<"\""<<endl
				<<"  not matched by patter \""<<itrPattern->first<<"\"\n";
			uiErrors++;
			liErrors.push_back( pair< unsigned int, unsigned int >(
				uiActualPattern, uiActualMatch ) );
		}
	}//end for all pattern
	
	if ( uiErrors == 0 ) {
		cout<<endl<<"Everything OK"<<endl;
	} else {
		cerr<<endl<<"Count of errors: "<<uiErrors<<"   errors in:"<<endl;
		for ( list< pair< unsigned int, unsigned int > >::const_iterator
				itrError = liErrors.begin(); itrError != liErrors.end();
				++itrError ) {
			cerr<<"   pattern: "<<(itrError->first)<<
				"   string: "<<(itrError->second)<<endl;
		}
	}
	return iReturn;
}

























