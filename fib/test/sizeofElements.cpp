/**
 * @file sizeofElements
 * file name: sizeofElements.cpp
 * @author Betti Oesterholz
 * @date 03.08.2010
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This programm evalues the size of the different fib -datatyps.
 *
 * Copyright (C) @c GPL3 2010 Betti Oesterholz
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
 * This programm evalues the size of the different fib -datatyps.
 *
 */
/*
History:
03.08.2010  Oesterholz  created
*/

#include "version.h"

#include "cPoint.h"
#include "cRoot.h"
#include "cList.h"
#include "cArea.h"
#include "cProperty.h"
#include "cFunction.h"
#include "cComment.h"

#include "cFunctionValue.h"
#include "cFunctionVariable.h"
#include "cFunctionAbs.h"
#include "cFunctionSin.h"
#include "cFunctionLog.h"
#include "cFunctionArcsin.h"
#include "cFunctionAdd.h"
#include "cFunctionSub.h"
#include "cFunctionMult.h"
#include "cFunctionDiv.h"
#include "cFunctionExp.h"
#include "cFunctionMin.h"
#include "cFunctionMax.h"


#include "cDomainNaturalNumberBit.h"
#include "cDomainVector.h"
#include "cTypeVariable.h"
#include "cTypeInVar.h"

#include "cFibVariable.h"
#include "cVectorProperty.h"
#include "cVectorPosition.h"

#include "cEvaluePositionList.h"
#include "cEvalueFibElementList.h"


#include "tinyxml.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <ostream>
#include <ctime>

#include "tCompareBits.inc"

#ifndef DIR_OUTPUT
	#define DIR_OUTPUT "test_output/"
#endif



using namespace fib;
using namespace std;



int main(int argc, char* argv[]){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	srand( time( NULL ) );
	
	cout<<endl<<"This programm evalues the size of the different fib -datatyps"<<endl;
	cout<<      "============================================================="<<endl;
	
	cout<<"BEWARE: The memory for inclass containers won't be counted correct."<<endl<<endl;

	
	//cPoint
	cout<<"cPoint type: "<< sizeof( cPoint ) <<" Byte"<<endl;
	
	cPoint point1;
	cout<<"cPoint size empty: "<< sizeof( point1) <<" Byte" <<endl;
	
	//cFibVector
	cVectorPosition vecPositionD0( 0 );
	cout<<"size \"cVectorPosition vecPositionD0( 0 )\": "<< sizeof( vecPositionD0) <<" Byte" <<endl;
	
	cVectorPosition vecPositionD2( 2 );
	cout<<"size \"cVectorPosition vecPositionD2( 2 )\": "<< sizeof( vecPositionD2) <<" Byte" <<endl;
	
	cVectorPosition vecPositionD3( 3 );
	cout<<"size \"cVectorPosition vecPositionD3( 3 )\": "<< sizeof( vecPositionD3) <<" Byte" <<endl;
	
	vecPositionD3.setValue( 1, 2 );
	cout<<"vecPositionD3.setValue( 1, 2 );"<<endl;
	cout<<"size \"vecPositionD3\": "<< sizeof( vecPositionD3) <<" Byte" <<endl;
	vecPositionD3.setValue( 2, 2.5 );
	cout<<"vecPositionD3.setValue( 2, 2.5 );"<<endl;
	cout<<"size \"vecPositionD3\": "<< sizeof( vecPositionD3) <<" Byte" <<endl;
	
	cFibVariable variable1( NULL );
	cout<<"cFibVariable variable1( NULL );"<<endl;
	cout<<"size \"variable1\": "<< sizeof( variable1) <<" Byte" <<endl;
	vecPositionD3.setVariable( 1, &variable1 );
	cout<<"vecPositionD3.setVariable( 1, &variable1 );"<<endl;
	cout<<"size \"vecPositionD3\": "<< sizeof( vecPositionD3) <<" Byte" <<endl;
	cout<<"size \"variable1\": "<< sizeof( variable1) <<" Byte" <<endl;
	
	
	//TODO
	
	//cProperty
	
	//cList
	
	//cRoot
	
	//cArea
	
	//cFunctuion
	
	
	//cUnderFunction










	return iReturn;
}






