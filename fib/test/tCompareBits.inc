/**
 * @file tCompareBits
 * file name: tCompareBits.inc
 * @author Betti Oesterholz
 * @date 01.11.2009
 * @mail webmaster@BioKom.info
 *
 * System: C++
 *
 * This includefile contains functions for comparing bits and byts.
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
 * This includefile contains functions for comparing bits and byts.
 *
 */
/*
History:
01.11.2009  Oesterholz  created
27.12.2009  Oesterholz  function compareDoubleFib() for comparing doubles added
13.01.2011  Oesterholz  compareDouble() used
*/


#ifndef T_COMPARE_BITS
#define T_COMPARE_BITS

#include <iostream>
#include <fstream>
#include <ostream>
#include <istream>
#include <iomanip>

#include "fibDatatyps.h"


/**
 * This functions compares the byts stored in the file with the giben byts
 * in the char array pcByts.
 *
 * @param szFileName the name of the file, wher the byts to compare with
 * 	pcByts are stored
 * @param pcByts the byts to compare with the byts in the file
 * @param uiNumberofByts the number of byts to compare
 * @return the number of errors occured in the test
 */
int compareBytsWithFile( const char * szFileName, const char * pcByts,
		const unsigned int uiNumberOfByts ){

	int iReturn = 0;//returnvalue of the test; the number of occured Errors
	
	cout<<endl<<"Comparing the given byts with the byts in the file: "<<endl;
	
	//load the byts from the file
	unsigned int uiBytsLoaded = 0;
	ifstream * file = new ifstream( szFileName , ios_base::in | ios_base::binary );
	
	if ( (file == NULL) || ( ! file->is_open()) ){
		cerr<<"Error: Could not open the file "<< szFileName << " . "<<endl;
		iReturn++;
		return iReturn;
	}
	
	char pcLoadedByts[ uiNumberOfByts + 8 ];
	
	while ( ! file->eof() && ! file->fail() && ( uiBytsLoaded < (uiNumberOfByts + 8) ) ){
		
		file->get( pcLoadedByts[ uiBytsLoaded ] );
		uiBytsLoaded++;
	}
	//check loaded
	if ( ! file->eof() ){
		cerr<<"Error: Still more data to load, but "<< uiBytsLoaded <<
			" byts loaded when yust "<< uiNumberOfByts <<
			" byts to compare with . "<<endl;
		iReturn++;
	}else{
		uiBytsLoaded--;//don't count last byte on eof
	}
	if ( file->bad() ){//TODO why file->fail() gives back false
		cerr<<"Error: Error while loading data. "<<endl;
		iReturn++;
	}
	delete file;
	
	if ( uiBytsLoaded != uiNumberOfByts ){
		cerr<<"Error: Number of byts not equal, "<< uiBytsLoaded <<
			" byts loaded when yust "<< uiNumberOfByts <<
			" byts to compare with . "<<endl;
		iReturn++;
	}

	//print both
	cout<<hex;
	unsigned short usLineLenght = 32;
	for ( unsigned int uiActualPosition = 0;
			( uiActualPosition < uiNumberOfByts ) ||
			( uiActualPosition < uiBytsLoaded );
			uiActualPosition += usLineLenght ){
		
		cout<<"Original : ";
		for ( unsigned short usLinePosition = 0;
				usLinePosition < usLineLenght; usLinePosition++ ){
			
			if ( (uiActualPosition + usLinePosition) < uiNumberOfByts ){
				cout<<"0x"<<setfill('0')<<setw(2)<<
				(unsigned short)((unsigned char)pcByts[ uiActualPosition + usLinePosition ]) <<";";
			}else{//no more chars to print
				break;
			}
		}
			
		cout<<endl<<"File     : ";
		for ( unsigned short usLinePosition = 0;
				usLinePosition < usLineLenght; usLinePosition++ ){
			
			if ( (uiActualPosition + usLinePosition) < uiBytsLoaded ){
				cout<<"0x"<<setfill('0')<<setw(2)<<
				(unsigned short)((unsigned char)pcLoadedByts[ uiActualPosition + usLinePosition ]) <<";";
			}else{//no more chars to print
				break;
			}
		}
		cout<<endl;
	}
	cout<<dec;
	
	//compare the byts
	for ( unsigned int uiActualPosition = 0;
			( uiActualPosition < uiNumberOfByts ) ||
			( uiActualPosition < uiBytsLoaded );
			uiActualPosition++ ){
		
		if ( ( uiActualPosition < uiNumberOfByts ) && ( uiBytsLoaded <= uiActualPosition ) ){
			
			cerr<<"Error: The "<< uiActualPosition <<" byte could not be loaded. "<<endl;
			iReturn++;
			break;//can't compare more byts
		}else if ( ( uiNumberOfByts <= uiActualPosition ) && ( uiActualPosition < uiBytsLoaded ) ){
			cerr<<"Error: The "<< uiActualPosition <<" byte could be loaded, but isn't ther to compare. "<<endl;
			iReturn++;
			break;//can't compare more byts
		}else{//compare the two byts
			if (  pcByts[ uiActualPosition ] != pcLoadedByts[ uiActualPosition ] ){
				cerr<<"Error: The "<< uiActualPosition <<"'th byte in the file is "<<
					hex << "0x"<<setfill('0')<<setw(2)<<
					(unsigned short)((unsigned char)pcLoadedByts[ uiActualPosition ]) << " but should be "<<
					"0x"<<setfill('0')<<setw(2)<<
					(unsigned short)((unsigned char)pcByts[ uiActualPosition ]) <<" "<<dec<<endl;
				iReturn++;
			}
		}
	}
	cout<<dec;
	
	return iReturn;
}


/**
 * This functions compares two double fib numbers.
 * Realy small differences will be ignored.
 *
 * @param dValue1 the first number to compare
 * @param dValue2 the second number to compare
 * @return true if the first number is equal to the second, else false
 */
bool compareDoubleFib( const doubleFib & dValue1, const doubleFib & dValue2 ){
	
	return fib::compareDouble( dValue1, dValue2 );
}





//T_COMPARE_BITS
#endif

